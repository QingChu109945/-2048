#include "function.h"

using namespace std;

void SetWindows()
{
    system("mode con cols=60 lines=30");
    system("color 1f");
    system("title 2048    Powered By Liwenhua");
}

void setcolor(int color)
{
    HANDLE hc=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc,0|color);
}

int relatedcolor(int number)
{
    switch (number)
    {
        case 2:
            return 127;
        case 4:
            return 143;
        case 8:
            return 239;
        case 16:
            return 175;
        case 32:
            return 174;
        case 64:
            return 191;
        case 128:
            return 159;
        case 256:
            return 223;
        case 512:
            return 222;
        case 1024:
            return 207;
        case 2048:
            return 206;
        default:
            return 12;
    }    
}   

bool WelCome()
{
    system("cls");
    Position(23,10);
    cout <<"WELCOME TO 2048";
    //启动面板
    int startposx = 20 , startposy = 16;
    bool state=1;
    Position(1,startposy+4);
    cout <<"Tips:\n\n  Press Shift To Confirm Your Choice...";
    Position(1,startposy);
    cout << setw(26) <<" "<<"Start"<< endl;
    cout << setw(26)<<" "<<"Exit";
    //Show the choice button;
    Position(startposx,startposy);Choice;
    
    choiceprocess:
        if (keydown) {Position(startposx-1,startposy);cout<<"  ";Position(startposx,startposy+1);Choice;state=0;};
        if (keyup  ) {Position(startposx-1,startposy+1);cout<<"  ";Position(startposx,startposy);Choice;state=1;};
        if (keyenter) return state;
    goto choiceprocess;
} 

void lose(int score)
{
    Position(16,24);
    cout <<"You Lost! And Your Score Is "<<score;
    cout <<"\n\nPress Shift To Exit...";
    system("pause>nul");
    loop:
        if (keyenter) {exit(0);}
    goto loop;
}     

void Position(int x, int y)
{
    COORD pos = { x - 1, y - 1 };
    HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Out, pos);
}

void DrawTable(int pos[5][5],int x,int y)
{
    for (int i=1 ; i<=4 ; i++)
        for (int j=1 ; j<=4 ; j++)
            if (!(pos[i][j]==0))
            {
                setcolor(relatedcolor(pos[i][j]));
                Position(x+(i-1)*8+2,y+j*3-1);
                if (pos[i][j]<100)
                {cout <<left<<"  "<<setw(4)<<pos[i][j];}
                else if (pos[i][j]<10000)
                {cout <<left<<" "<<setw(5)<<pos[i][j];}
                Position(x+(i-1)*8+2,y+j*3);
                cout <<left<<setw(6)<<" ";
            }       
}   

void ClearTable(int x,int y)
{
    for (int i=1 ; i<=4 ; i++)
        for (int j=1 ; j<=4 ; j++)
        {
                Position(x+(i-1)*8+2,y+j*3-1);
                setcolor(31);
                cout <<setw(6)<<" ";
                Position(x+(i-1)*8+2,y+j*3);
                cout <<setw(6)<<" ";
        }
}   

void FrameWork(int x,int y)
{
    for (int i=1;i<=y;i++) cout <<endl;
    for (int i=1;i<=5;i++)
    {
        for (int k=1;k<=x-1;k++) {cout<<" ";}
        if (i==1)
        {
            cout<<"╔═══╦═══╦═══╦═══╗\n";
            for (int a=1;a<=2;a++) {
            for (int k=1;k<=x-1;k++) {cout<<" ";}
            for (int j=1;j<=5;j++) cout <<left<<setw(8)<<"║";
            cout <<endl; }
        }    
        if (i>=2&&i<=4)
        {
            cout<<"╠═══╬═══╬═══╬═══╣\n";
            for (int a=1;a<=2;a++) {
            for (int k=1;k<=x-1;k++) {cout<<" ";}
            for (int j=1;j<=5;j++) cout <<left<<setw(8)<<"║";
            cout <<endl;}
        }    
        if (i==5)
        {
            cout<<"╚═══╩═══╩═══╩═══╝";
        }  
    }     
}   


void Change(int pos[5][5],char dir,int& score)
{
    bool ischange=0;
    switch (dir)
    {
        case 'u':
        //让可以加的数字相加 
            for (int i=1;i<=4;i++)
                for (int j=2;j<=4;j++)
                    for (int k=j-1;k>=1;k--)
                    {
                        if (pos[i][k]==pos[i][j]) {score+=2*pos[i][k];pos[i][k]*=2;pos[i][j]=0;ischange=1;break;}
                        if (pos[i][k]!=0) break;
                    }  
        //对齐，将全部数字移动到最上层；   
            for (int i=1;i<=4;i++)
                for (int j=1;j<=3;j++)
                    if (pos[i][j]==0) 
                    {
                        for (int k=j+1;k<=4;k++)
                        {
                            if (pos[i][k]!=0) ischange=1;
                            pos[i][j]=pos[i][k];
                            pos[i][k]=0;
                            if (pos[i][j]!=0) break;
                        }
                    }                
        //产生新的数字
        if (ischange)
        {
            for (;;) 
            {
                int randnum=rand()%4+1;
                if (pos[randnum][4]==0) {pos[randnum][4]=((rand()%2)+1)*2;break;}
            } 
        } else {if (check(pos)) lose(score);}              
            break;
            
        case 'd':
            
            for (int i=1;i<=4;i++)
                for (int j=3;j>=1;j--)
                    for (int k=j+1;k<=4;k++)
                    {
                        if (pos[i][k]==pos[i][j]) {score+=2*pos[i][k];pos[i][k]*=2;pos[i][j]=0;ischange=1;break;}
                        if (pos[i][k]!=0) break;
                    }    
 
            for (int i=1;i<=4;i++)
                for (int j=4;j>=2;j--)
                    if (pos[i][j]==0) {
                    for (int k=j-1;k>=1;k--)
                    {
                        if (pos[i][k]!=0) ischange=1;
                        pos[i][j]=pos[i][k];
                        pos[i][k]=0;
                        if (pos[i][j]!=0) break;
                    }   }
         if (ischange)
         {  
            for (;;) 
            {
                int randnum=rand()%4+1;
                if (pos[randnum][1]==0) {pos[randnum][1]=((rand()%2)+1)*2;break;}
            } 
        } else {if (check(pos)) lose(score);}
            break;
            
        case 'l':
            
            for (int i=1;i<=4;i++)
                for (int j=2;j<=4;j++)
                    for (int k=j-1;k>=1;k--)
                    {
                        if (pos[k][i]==pos[j][i]) {score+=2*pos[k][i];pos[k][i]*=2;pos[j][i]=0;ischange=1;break;}
                        if (pos[k][i]!=0) break;
                    }
            
            for (int i=1;i<=4;i++)
                for (int j=1;j<=3;j++)
                    if (pos[j][i]==0) {
                    for (int k=j+1;k<=4;k++)
                    {
                        if (pos[i][k]!=0) ischange=1;
                        pos[j][i]=pos[k][i];
                        pos[k][i]=0;
                        if (pos[j][i]!=0) break;
                    }    }
            
         if (ischange)
         {
            for (;;) 
            {
                int randnum=rand()%4+1;
                if (pos[4][randnum]==0) {pos[4][randnum]=((rand()%2)+1)*2;break;}
            } 
         } else {if (check(pos)) lose(score);}
            break;
            
        case 'r':
            for (int i=1;i<=4;i++)
                for (int j=3;j>=1;j--)
                    for (int k=j+1;k<=4;k++)
                    {
                        if (pos[k][i]==pos[j][i]) {score+=2*pos[k][i];pos[k][i]*=2;pos[j][i]=0;ischange=1;break;}
                        if (pos[k][i]!=0) break;
                    }    
            for (int i=1;i<=4;i++)
                for (int j=4;j>=2;j--)
                    if (pos[j][i]==0) {
                    for (int k=j-1;k>=1;k--)
                    {
                        if (pos[i][k]!=0) ischange=1;
                        pos[j][i]=pos[k][i];
                        pos[k][i]=0;
                        if (pos[j][i]!=0) break;
                    }    }
            
         if (ischange)
         {
            for (;;) 
            {
                int randnum=rand()%4+1;
                if (pos[1][randnum]==0) {pos[1][randnum]=((rand()%2)+1)*2;break;}
            } 
        } else {if (check(pos)) lose(score);}
            break;
    }    
}   

bool check(int pos[5][5])
{
    for (int i=1;i<=4;i++)
        for (int j=1;j<=4;j++)
        {
            if (pos[i][j]==0) return 0;
            if (j<=3) 
            {
                if ((pos[j][i]==pos[j+1][i])||(pos[i][j]==pos[i][j+1])) return 0;
            }
        } 
     return 1;   
}    
