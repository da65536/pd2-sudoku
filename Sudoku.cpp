#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
using namespace std;

void Sudoku::transform(){
    readIn();
    change();
    printOut();
}

void Sudoku::change(){
    srand(time(NULL));
    changeNum(rand() % 9 + 1, rand()% 9 + 1);
    changeRow(rand() % 3, rand() % 3);
    changeCol(rand() % 3, rand() % 3);
    rotate(rand() % 101);
    flip(rand() % 2);

}

void Sudoku::giveQuestion(){
    
    int zero_num = 0;
	int zeroposition;
    int i,j = 0;
	
   int origin[81] = {1,5,7,4,8,9,6,2,3,6,8,9,5,2,3,1,7,4,3,2,4,7,6,1,9,5,8,2,6,5,8,3,7,4,9,1,7,3,1,9,4,5,2,8,6,9,4,8,6,1,2,5,3,7,8,7,2,1,5,6,3,4,9,4,1,3,2,9,8,7,6,5,5,9,6,3,7,4,8,1,2};		     

    srand(time(NULL));

    for(i = 0; i < 81; i++){
	   question[i] = origin[i];
	}
    while(zero_num < 27){
	   zero_num = rand() % 81;
    }
    while(j < zero_num){
	   zeroposition = rand() % 81;
	   
	   if(question[zeroposition] != 0){
	      question[zeroposition] = 0;
	      j++;
	   }
	   else
	      continue;	
	}
}

void Sudoku::readIn(){
    int i;
    for(i = 0; i < 81; i++) 
	cin>>read[i];
   
}

void Sudoku::printOut(){
	int i;
	for(i = 0; i < 81; i++){
		printf("%d",read[i]);
		if((i+1)%9 != 0)
			printf("%c",' ');
		else
			printf("\n");
	}



}

void Sudoku::changeNum(int a, int b){

    int i;

	for(i = 0; i < 81; i++){
	   temp[i] = 0;
	}

	for(i = 0; i < 81; i++){
	   if(read[i] == a){
	      read[i] = b;
		  temp[i] = b;
	   }
	   if(read[i] == b && temp[i] != b){
	      read[i] = a;
	   }
	}
}

void Sudoku::changeRow(int a, int b){

    int  i, j, first, second, space;
	first = a*3;
    second = b*3;

    for(i = 0; i < 9; i++){
	   for(j = 0; j < 3; j++){
	      space = read[first +j];
		  read[first + j] = read[second + j];
	      read[second + j] = space;	   
	   } 
	   first = first + 9;
	   second = second + 9;
	}
}

void Sudoku::changeCol(int a, int b){

    int i, j, first, second, space;
	first = a*27;
	second = b*27;

    for(i = 0; i < 3; i++){
	   for(j = 0; j < 9; j++){
	      space = read[first+j];
		  read[first+j] = read[second+j];
		  read[second+j] = space;
	   }
	   first = first + 9;
	   second = second + 9;
	}
}

void Sudoku::rotate(int n){
     int degree, i, j, new_num, first, num;
     degree = n % 4;

	 if(degree == 0)
	  ;

	 for(i = 0; i < 81; i++){
	    temp[i] = 0;
	 }

     if(degree == 1){
	    new_num = 0;
		first = 72;
	    for(i = 0; i < 9; i++){
		   num = first;
		   for(j = 0; j < 9; j++){
		      temp[new_num + j] = read[num];
			  num -= 9;
		   }
           new_num += 9;
		   first++;
		}
		for(i = 0; i < 81; i++){
		   read[i] = temp[i];
		}
	 }

     if(degree == 2){
	    for(i = 0; i < 81; i++){
		   temp[80-i] = read[i];		
		}
	    for(i = 0; i < 81; i++){
		   read[i] = temp[i];
		}
	 }

	 if(degree == 3){
	    new_num = 0;
	    first = 8;
	    for(i = 0; i < 9; i++){
	       num = first;
	       for(j = 0; j < 9; j++){
		      temp[new_num + j] = read[num];
              num += 9;		  
		   }
	       new_num ++;
		   first--;
	    }
	    for(i = 0; i < 81; i++){
	       read[i] = temp[i];
	    }
	  }
}

void Sudoku::flip(int n){
    int i, j, first, new_num ,num;

	for(i = 0; i < 81; i++){
	   temp[i] = 0;
	}

    if(n == 0){
	   new_num = 0;
	   first = 8;
	   for(i = 0; i < 9; i++){
		  num = first;
	      for(j = 0; j < 9; j++){
		     temp[new_num + j] = read[num];
		     num--;  
		  }
	      new_num = new_num + 9;
		  first = first + 9;
	   }
	   for(i = 0; i < 81; i++){
	      read[i] = temp[i];
	   }
	}
	if(n == 1){
	   new_num = 0;
	   first = 72;
	   for(i = 0; i < 9; i++){
	      num = first;
		  for(j = 0; j < 9; j++){
		     temp[new_num + j] = read[num];
			 num++;
		  }
		  new_num = new_num + 9;
		  first = first - 9;
	   }
	   for(i = 0; i < 81; i++){
	      read[i] = temp[i];  
	   }
	}
}



void Sudoku::solve(){
    int i,j,k, sum;
    int probability[81][10];
    int box[81];
    for(i = 0; i < 81; i++){
		probability[i][0] = 0;
	    for(j = 1; j < 10; j++){
	      probability[i][j] = 1;
	    }   
	}   

    for(i = 0; i < 81; i++){
	
	    if(read[i] = 0){
		   continue;
		}
	    
	    if(i = 0){
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[10][k] = 0;		
		    probability[11][k] = 0;
		    probability[19][k] = 0;
		    probability[20][k] = 0;
		}
	    if(i = 1){	
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[9][k] = 0;		
		    probability[11][k] = 0;
		    probability[18][k] = 0;
		    probability[20][k] = 0;
			
		}
	    if(i = 2){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[9][k] = 0;		
		    probability[10][k] = 0;
		    probability[18][k] = 0;
		    probability[19][k] = 0;

		}
	    if(i = 3){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[13][k] = 0;		
		    probability[14][k] = 0;
		    probability[22][k] = 0;
		    probability[23][k] = 0;
		}
	    if(i = 4){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[12][k] = 0;		
		    probability[14][k] = 0;
		    probability[21][k] = 0;
		    probability[23][k] = 0;
		}
	    if(i = 5){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[12][k] = 0;		
		    probability[13][k] = 0;
		    probability[21][k] = 0;
		    probability[22][k] = 0;
		}
	    if(i = 6){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[16][k] = 0;		
		    probability[17][k] = 0;
		    probability[25][k] = 0;
		    probability[26][k] = 0;
		}
	    if(i = 7){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[15][k] = 0;		
		    probability[17][k] = 0;
		    probability[24][k] = 0;
		    probability[26][k] = 0;
		}
	    if(i = 8){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[15][k] = 0;		
		    probability[16][k] = 0;
		    probability[24][k] = 0;
		    probability[25][k] = 0;
		}
	    if(i = 9){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[1][k] = 0;		
		    probability[2][k] = 0;
		    probability[19][k] = 0;
		    probability[20][k] = 0;
		}
	    if(i = 10){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[0][k] = 0;		
		    probability[2][k] = 0;
		    probability[18][k] = 0;
		    probability[20][k] = 0;
		}
	    if(i = 11){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[0][k] = 0;		
		    probability[1][k] = 0;
		    probability[18][k] = 0;
		    probability[19][k] = 0;
		}
	    if(i = 12){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[4][k] = 0;		
		    probability[5][k] = 0;
		    probability[22][k] = 0;
		    probability[23][k] = 0;
		}
	    if(i = 13){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[3][k] = 0;		
		    probability[5][k] = 0;
		    probability[21][k] = 0;
		    probability[23][k] = 0;
		}
	    if(i = 14){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[3][k] = 0;		
		    probability[4][k] = 0;
		    probability[21][k] = 0;
		    probability[22][k] = 0;
		}
	    if(i = 15){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[7][k] = 0;		
		    probability[8][k] = 0;
		    probability[25][k] = 0;
		    probability[26][k] = 0;
		}
	    if(i = 16){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[6][k] = 0;		
		    probability[8][k] = 0;
		    probability[24][k] = 0;
		    probability[26][k] = 0;
		}
	    if(i = 17){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 9; j < 18; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[6][k] = 0;		
		    probability[7][k] = 0;
		    probability[24][k] = 0;
		    probability[25][k] = 0;
		}
	    if(i = 18){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[1][k] = 0;		
		    probability[2][k] = 0;
		    probability[10][k] = 0;
		    probability[11][k] = 0;
		}
	    if(i = 19){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[0][k] = 0;		
		    probability[1][k] = 0;
		    probability[9][k] = 0;
		    probability[11][k] = 0;
		}
	    if(i = 20){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[0][k] = 0;		
		    probability[1][k] = 0;
		    probability[9][k] = 0;
		    probability[10][k] = 0;
		}
	    if(i = 21){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[4][k] = 0;		
		    probability[5][k] = 0;
		    probability[13][k] = 0;
		    probability[14][k] = 0;
		}
	    if(i = 22){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[3][k] = 0;		
		    probability[5][k] = 0;
		    probability[12][k] = 0;
		    probability[14][k] = 0;
		}
	    if(i = 23){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[3][k] = 0;		
		    probability[4][k] = 0;
		    probability[12][k] = 0;
		    probability[13][k] = 0;
		}
	    if(i = 24){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[7][k] = 0;		
		    probability[8][k] = 0;
		    probability[16][k] = 0;
		    probability[17][k] = 0;
		}
	    if(i = 25){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[6][k] = 0;		
		    probability[8][k] = 0;
		    probability[15][k] = 0;
		    probability[17][k] = 0;
		}
	    if(i = 26){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 18; j < 27; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[6][k] = 0;		
		    probability[7][k] = 0;
		    probability[15][k] = 0;
		    probability[16][k] = 0;
		}
	    if(i = 27){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[37][k] = 0;		
		    probability[38][k] = 0;
		    probability[46][k] = 0;
		    probability[47][k] = 0;
		}
	    if(i = 28){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[36][k] = 0;		
		    probability[38][k] = 0;
		    probability[45][k] = 0;
		    probability[47][k] = 0;
		}
	    if(i = 29){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[36][k] = 0;		
		    probability[37][k] = 0;
		    probability[45][k] = 0;
		    probability[46][k] = 0;
		}
	    if(i = 30){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[40][k] = 0;		
		    probability[41][k] = 0;
		    probability[49][k] = 0;
		    probability[50][k] = 0;
		}
	    if(i = 31){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[39][k] = 0;		
		    probability[41][k] = 0;
		    probability[48][k] = 0;
		    probability[50][k] = 0;
		}
	    if(i = 32){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[39][k] = 0;		
		    probability[40][k] = 0;
		    probability[48][k] = 0;
		    probability[49][k] = 0;
		}
	    if(i = 33){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[43][k] = 0;		
		    probability[44][k] = 0;
		    probability[52][k] = 0;
		    probability[53][k] = 0;
		}
	    if(i = 34){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[42][k] = 0;		
		    probability[44][k] = 0;
		    probability[51][k] = 0;
		    probability[53][k] = 0;
		}
	    if(i = 35){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 27; j < 36; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[42][k] = 0;		
		    probability[43][k] = 0;
		    probability[51][k] = 0;
		    probability[52][k] = 0;
		}
	    if(i = 36){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[28][k] = 0;		
		    probability[29][k] = 0;
		    probability[46][k] = 0;
		    probability[47][k] = 0;
		}
	    if(i = 37){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[27][k] = 0;		
		    probability[29][k] = 0;
		    probability[45][k] = 0;
		    probability[47][k] = 0;
		}
	    if(i = 38){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[27][k] = 0;		
		    probability[28][k] = 0;
		    probability[45][k] = 0;
		    probability[46][k] = 0;
		}
	    if(i = 39){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[31][k] = 0;		
		    probability[32][k] = 0;
		    probability[49][k] = 0;
		    probability[50][k] = 0;
		}
	    if(i = 40){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[30][k] = 0;		
		    probability[32][k] = 0;
		    probability[48][k] = 0;
		    probability[50][k] = 0;
		}
	    if(i = 41){
		k = read[i];
		for(j = 0; j < 10; j++){
			if( j != k){
			   probability[i][j] = 0;
			}
		}
		for(j = 36; j < 45; j++){
			if(j != i){
				probability[j][k] = 0;
			}
		}
		for(j = 0; j < 9; j++){
			if((5 + j*9) != i){
				probability[(5 + j*9)][k] = 0;
			}
		}
		probability[30][k] = 0;		
		probability[31][k] = 0;
		probability[48][k] = 0;
		probability[49][k] = 0;
		
		}
	    if(i = 42){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[34][k] = 0;		
		    probability[35][k] = 0;
		    probability[52][k] = 0;
		    probability[53][k] = 0;
		}
	    if(i = 43){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[33][k] = 0;		
		    probability[35][k] = 0;
		    probability[51][k] = 0;
		    probability[53][k] = 0;
		}
	    if(i = 44){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 36; j < 45; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[33][k] = 0;		
		    probability[34][k] = 0;
		    probability[51][k] = 0;
		    probability[52][k] = 0;
		}
	    if(i = 45){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[28][k] = 0;		
		    probability[29][k] = 0;
		    probability[37][k] = 0;
		    probability[38][k] = 0;
		}
	    if(i = 46){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[27][k] = 0;		
		    probability[29][k] = 0;
		    probability[36][k] = 0;
		    probability[38][k] = 0;
		}
	    if(i = 47){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[27][k] = 0;		
		    probability[26][k] = 0;
		    probability[36][k] = 0;
		    probability[37][k] = 0;
		}
	    if(i = 48){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[31][k] = 0;		
		    probability[32][k] = 0;
		    probability[40][k] = 0;
		    probability[41][k] = 0;
		}
	    if(i = 49){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[30][k] = 0;		
		    probability[32][k] = 0;
		    probability[39][k] = 0;
		    probability[41][k] = 0;
		}
	    if(i = 50){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[30][k] = 0;		
		    probability[31][k] = 0;
		    probability[39][k] = 0;
		    probability[40][k] = 0;
		}
	    if(i = 51){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[34][k] = 0;		
		    probability[35][k] = 0;
		    probability[43][k] = 0;
		    probability[44][k] = 0;
		}
	    if(i = 52){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[33][k] = 0;		
		    probability[35][k] = 0;
		    probability[42][k] = 0;
		    probability[44][k] = 0;
		}
	    if(i = 53){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 45; j < 54; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[33][k] = 0;		
		    probability[34][k] = 0;
		    probability[42][k] = 0;
		    probability[43][k] = 0;
		}
	    if(i = 54){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[64][k] = 0;		
		    probability[65][k] = 0;
		    probability[73][k] = 0;
		    probability[74][k] = 0;
		}
	    if(i = 55){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[63][k] = 0;		
		    probability[65][k] = 0;
		    probability[72][k] = 0;
		    probability[74][k] = 0;
		}
	    if(i = 56){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[63][k] = 0;		
		    probability[64][k] = 0;
		    probability[72][k] = 0;
		    probability[73][k] = 0;
		}
	    if(i = 57){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[67][k] = 0;		
		    probability[68][k] = 0;
		    probability[76][k] = 0;
		    probability[77][k] = 0;
		}
	    if(i = 58){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[66][k] = 0;		
		    probability[68][k] = 0;
		    probability[75][k] = 0;
		    probability[77][k] = 0;
		}
	    if(i = 59){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[66][k] = 0;		
		    probability[67][k] = 0;
		    probability[75][k] = 0;
		    probability[76][k] = 0;
		}
	    if(i = 60){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[70][k] = 0;		
		    probability[71][k] = 0;
		    probability[79][k] = 0;
		    probability[80][k] = 0;
		}
	    if(i = 61){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[69][k] = 0;		
		    probability[71][k] = 0;
		    probability[78][k] = 0;
		    probability[80][k] = 0;
		}
	    if(i = 62){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 54; j < 63; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[69][k] = 0;		
		    probability[70][k] = 0;
		    probability[78][k] = 0;
		    probability[79][k] = 0;
		}
	    if(i = 63){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[55][k] = 0;		
		    probability[56][k] = 0;
		    probability[73][k] = 0;
		    probability[74][k] = 0;
		}
	    if(i = 64){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[54][k] = 0;		
		    probability[56][k] = 0;
		    probability[72][k] = 0;
		    probability[74][k] = 0;
		}
	    if(i = 65){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[54][k] = 0;		
		    probability[55][k] = 0;
		    probability[72][k] = 0;
		    probability[73][k] = 0;
		}
	    if(i = 66){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[58][k] = 0;		
		    probability[59][k] = 0;
		    probability[76][k] = 0;
		    probability[77][k] = 0;
		}
	    if(i = 67){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[57][k] = 0;		
		    probability[59][k] = 0;
		    probability[75][k] = 0;
		    probability[77][k] = 0;
		}
	    if(i = 68){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[57][k] = 0;		
		    probability[58][k] = 0;
		    probability[75][k] = 0;
		    probability[76][k] = 0;
		}
	    if(i = 69){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[61][k] = 0;		
		    probability[62][k] = 0;
		    probability[79][k] = 0;
		    probability[80][k] = 0;
		}
	    if(i = 70){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[60][k] = 0;		
		    probability[62][k] = 0;
		    probability[78][k] = 0;
		    probability[80][k] = 0;
		}
	    if(i = 71){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 63; j < 72; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[62][k] = 0;		
		    probability[63][k] = 0;
		    probability[77][k] = 0;
		    probability[78][k] = 0;
		}
	    if(i = 72){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((0 + j*9) != i){
				    probability[(0 + j*9)][k] = 0;
				}
			}
		    probability[55][k] = 0;		
		    probability[56][k] = 0;
		    probability[64][k] = 0;
		    probability[65][k] = 0;
		}
	    if(i = 73){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((1 + j*9) != i){
				    probability[(1 + j*9)][k] = 0;
				}
			}
		    probability[54][k] = 0;		
		    probability[56][k] = 0;
		    probability[63][k] = 0;
		    probability[65][k] = 0;
		}
	    if(i = 74){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((2 + j*9) != i){
				    probability[(2 + j*9)][k] = 0;
				}
			}
		    probability[54][k] = 0;		
		    probability[55][k] = 0;
		    probability[63][k] = 0;
		    probability[64][k] = 0;
		}
	    if(i = 75){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((3 + j*9) != i){
				    probability[(3 + j*9)][k] = 0;
				}
			}
		    probability[58][k] = 0;		
		    probability[59][k] = 0;
		    probability[67][k] = 0;
		    probability[68][k] = 0;
		}
	    if(i = 76){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((4 + j*9) != i){
				    probability[(4 + j*9)][k] = 0;
				}
			}
		    probability[57][k] = 0;		
		    probability[59][k] = 0;
		    probability[66][k] = 0;
		    probability[68][k] = 0;
		}
	    if(i = 77){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((5 + j*9) != i){
				    probability[(5 + j*9)][k] = 0;
				}
			}
		    probability[57][k] = 0;		
		    probability[58][k] = 0;
		    probability[66][k] = 0;
		    probability[67][k] = 0;
		}
	    if(i = 78){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((6 + j*9) != i){
				    probability[(6 + j*9)][k] = 0;
				}
			}
		    probability[61][k] = 0;		
		    probability[62][k] = 0;
		    probability[70][k] = 0;
		    probability[71][k] = 0;
		}
	    if(i = 79){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((7 + j*9) != i){
				    probability[(7 + j*9)][k] = 0;
				}
			}
		    probability[60][k] = 0;		
		    probability[62][k] = 0;
		    probability[69][k] = 0;
		    probability[71][k] = 0;
		}
	    if(i = 80){
		
		    k = read[i];
		    for(j = 0; j < 10; j++){
			    if( j != k){
				   probability[i][j] = 0;
				}
			}
		    for(j = 72; j < 81; j++){
			    if(j != i){
				    probability[j][k] = 0;
				}
			}
		    for(j = 0; j < 9; j++){
			    if((8 + j*9) != i){
				    probability[(8 + j*9)][k] = 0;
				}
			}
		    probability[60][k] = 0;		
		    probability[61][k] = 0;
		    probability[69][k] = 0;
		    probability[70][k] = 0;
		}
	
	}

	for(i = 0; i < 81; i++){
		box[i] = 0;
	}
    for(i = 0; i < 81; i++){
	    for(j = 1; j < 10; j++){
		    if(probability[i][j] = 1){
				box[i]++;
			}
		}
	}
    for(i = 0; i < 81; i++){
		if(box[i] == 0){
			printf("0\n");
			break;
		}
		if(box[i] > 1){
			printf("2\n");
			break;
		}
		if(box[i] == 1){
		    sum++;
		}
	}

	if(sum == 81){
		for(i = 0; i < 81; i++){
			for(j = 1; j < 10; j++){
				if(probability[i][j] == 1){
					ans[i] = j;
				}
			}
		}
	
		printf("1\n");
		for(i = 0; i < 81; i++){
			printf("%d",ans[i]);
			if((i+1)%9 != 9)
				printf("%c",' ');
			else
				printf("\n");
		}
	}

}






