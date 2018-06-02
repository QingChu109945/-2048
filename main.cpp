#include "function.h"

using namespace std;

int main(int argc, char *argv[])
{
  SetWindows();
  if ( !WelCome() ) {exit(0);};//Show the welcome information
  system("cls");
  int value[5][5]={0};//store each value of the table
  
  //Draw the table
  FrameWork(pianx,piany);
  //Random create a value
  srand(time(0));
  value[rand()%4+1][rand()%4+1]=(rand()%2+1)*2;
  DrawTable(value,pianx,piany);
  
//The body of the program
  bool keypress=0;
  char whichkey;
  int score=0;
  
  loop:
      
  //case the input
      if (keyleft) {whichkey='l';keypress=1;}
      else if (keyright) {whichkey='r';keypress=1;}
      else if (keyup) {whichkey='u';keypress=1;}
      else if (keydown) {whichkey='d';keypress=1;}
      else {keypress=0;}
  //end case
  
      if (keypress)
      {
      //change the value
          Change(value,whichkey,score);
      //refresh the number display
          ClearTable(pianx,piany);
          DrawTable(value,pianx,piany);  
      //show score
          Position(pianx+2,piany-2);
          setcolor(31);
          cout<<"Your Score:"<<score;
      } 
      system("pause>nul");
      
  goto loop;
}
