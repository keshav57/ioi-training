#include "grader.h"
#include "cluedo.h"

void Solve(){
   int guess[3] = {1,1,1};
   int i;

   i = Theory(guess[0],guess[1],guess[2]);

   while(i){
	   ++guess[i-1];
	   i = Theory(guess[0],guess[1],guess[2]);
   }
}
