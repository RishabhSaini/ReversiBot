#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Comp move and user move
//user move is entering data
//comp move is out algo

void printBoard(char board[][28], int n);
void availMoves(char board[][28], int n, char colour);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][28], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void playturn(char board[][28], int n);
void flipmove(int row, int column, char color, int deltaRow, int deltaCol, int n, char board[][28]);

void userMove(char comp, char board[][28], int n);
void compMove(char board[][28], int n, char comp);
bool end(char board[][28], int n);
int noColor(char board[][28], int n, char colour);
int noAvailMoves(char board[][28], int n, char colour);
int counter(int row, int column, char color, int deltaRow, int deltaCol, int n, char board[][28]);
void gamePlay(char comp, char board[][28], int n);
bool legalMove(int row, int col, char colour, char board[][28], int n );
int betterMatrix(int n, int k, int l, int max2row, int max2col, int a);
int stable(int n, int k, int l);


int main(){

	int n; //Size of the board
	char comp; //Computer black or white

	printf("Enter the board dimension: ");
	scanf("%d",&n);

	printf("Computer plays (B/W): ");
	scanf(" %c",&comp);

	char grid[28][28];
	printBoard(grid, n);

	gamePlay(comp, grid, n);

	return 0;
}

void gamePlay(char comp, char board[][28], int n){

	if(comp == 'B'){
		while(end(board, n) == false){
			compMove(board, n, comp);
			userMove(comp, board, n);
		}
	}
	else{
		while(end(board, n) == false){
			userMove(comp, board, n);
			compMove(board, n, comp);
		}
	}

	//Find the winner
	if(noColor(board,n,'W') > noColor(board,n,'B')){
		printf("W player wins.\n");
	}
	if(noColor(board,n,'B') > noColor(board,n,'W')){
		printf("B player wins.\n");
	}
	if(noColor(board,n,'W') == noColor(board,n,'B')){
		printf("Its a tie.\n");
	}
}

//Flawed
bool legalMove(int row, int col, char colour, char board[][28], int n ){
	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	if(board[row][col]=='U'){
		int legaldir = 0;
		for(int k =-1; k<=1; k++){
			for(int l=-1; l<=1; l++){
				if(k==0 && l==0){
					continue;
				}
				else{
					if(checkLegalInDirection(board, n, row, col, colour, k, l)){
						return true;
					}
				}
			}
		}
		if(legaldir == 0){
			return false;
		}
	}
	else{return false;}
}

//implement this: if 2 legal moves have same score then choose according to weighted matrix
void userMove(char comp, char board[][28], int n){
	char input[2];

	//Color of user
	int playerColor=comp;
	int intoppColor;
	if(playerColor==66){
		intoppColor = 87;
	}
	else{
		intoppColor = 66;
	}
	char user = intoppColor;


	if(noAvailMoves(board,n,user) == 0){
		if(end(board, n) == false){
			printf("%c player has no valid move.\n",user);
		}
	}
	else{
		printf("Enter move for colour %c (RowCol): ",user);
		scanf("%s",input);

		int row = input[0]-96;
		int column = input[1]-95;

		//Check for invalid move
		int legalDir = 0;

		for(int i =-1; i<=1; i++){
			for(int j=-1; j<=1; j++){
				if(i==0 && j==0){
					continue;
				}
				else{
					if(checkLegalInDirection(board, n, row, column, user, i, j)){
						legalDir++;
						flipmove(row, column, user, i, j, n, board); //Make the flip					
					}
				}
			}
		}
		
		//Print board
		for(int i=0; i<=n; i++){
			for(int j=0; j<=n+1; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
	}	
}

//Most flips is best move
void compMove(char board[][28], int n, char comp){

	/*

	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	//i and j are corrected
	int maxScore = 0;
	int maxRow;
	int maxCol;

	if(noAvailMoves(board,n,comp) == 0){
		if(end(board, n) == false){
			printf("%c player has no valid move.\n",comp);
		}
	}

	else{
		for(int i=rstart; i<=rfinish;i++){
			for(int j=cstart; j<=cfinish; j++){
				if(board[i][j]=='U'){ 
					int score = 0;
					for(int k =-1; k<=1; k++){
						for(int l=-1; l<=1; l++){
							if(k==0 && l==0){
								continue;
							}
							else{
								if(checkLegalInDirection(board, n, i, j, comp, k, l)){
									int dirscore = counter(i, j, comp, k, l, n, board);
									score+=dirscore;
								}
							}
						}
					}
					if(score>maxScore){
						maxScore = score;
						maxRow = i;
						maxCol = j;
					}
				}
				else{continue;}			
			}
		}

		for(int i =-1; i<=1; i++){
			for(int j=-1; j<=1; j++){
				if(i==0 && j==0){
					continue;
				}
				else{
					if(checkLegalInDirection(board, n, maxRow, maxCol, comp, i, j)){
						flipmove(maxRow, maxCol, comp, i, j, n, board); //Make the flip					
					}
				}
			}
		}

		char charrow= maxRow+96;
		char charcol= maxCol+95;

		printf("Computer places %c at %c%c.",comp,charrow,charcol);
		printf("\n");

		//Print the board
		for(int i=0; i<=n; i++){
			for(int j=0; j<=n+1; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
	}

	*/

	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	//Color of user
	int playerColor=comp;
	int intoppColor;
	if(playerColor==66){
		intoppColor = 87;
	}
	else{
		intoppColor = 66;
	}
	char user = intoppColor;

	int maxRow;
	int maxCol;

	if(noAvailMoves(board,n,comp) == 0){
		if(end(board, n) == false){
			printf("%c player has no valid move.\n",comp);
		}
	}
	else{

		int max2Row;
		int max2Col;

		int minScore = 1000;

		for(int i=rstart; i<=rfinish;i++){
			for(int j=cstart; j<=cfinish; j++){
				if(legalMove(i, j, comp, board, n)){
					//creating temp board
					char tmpboard[28][28];
					for(int k=0; k<28; k++){
						for(int l=0; l<28; l++){
							tmpboard[k][l] = board[k][l];
						}
					}

					//making the one ahead flip
					for(int k=-1; k<=1; k++){
						for(int l=-1; l<=1; l++){
							if(k==0 && l==0){
								continue;
							}
							else{
								if(checkLegalInDirection(tmpboard, n, k, l, comp, i, j)){
									flipmove(i, j, comp, k, l, n, tmpboard);
								}
							}
						}
					}

					///*

					//playing the smarter move and then playing the comp move	

					int moveExists = 0;					

					if(noAvailMoves(tmpboard,n,user) != 0){
						//playing smarter move

						

						
						//Done playing smarter

						//Making one more ahead flip from comp
						int min2Score = 100;
						
						for(int k=rstart; k<=rfinish; k++){
							for(int l=cstart; l<=cfinish; l++){
								if(legalMove(k, l, comp, board, n)){ //should be for tmpboard not board
									//create temp2 board
									char tmp2board[28][28];
									for(int m=0; m<28; m++){
										for(int o=0; o<28; o++){
											tmp2board[m][o] = tmpboard[m][o];
										}
									}

									for(int m=-1; m<=1; m++){
										for(int o=-1; o<=1; o++){
											if(m==0 && o==0){
												continue;
											}
											else{
												if(checkLegalInDirection(tmp2board, n, m, o, comp, k, l))
												{
													flipmove(k, l, comp, m, o, n, tmp2board);
												}
											}
										}
									}

									/*
									printf("tmp2board\n");
									for(int m=0; m<=n; m++){
										for(int o=0; o<=n+1; o++){
											printf("%c",tmp2board[m][o]);
										}
										printf("\n");
									}
									*/
									int next2movesComp = noAvailMoves(tmp2board,n,comp);
									int next2movesUser = noAvailMoves(tmp2board,n,user);
									int stability = stable(n, k, l);
									int weight = betterMatrix(n, k, l, max2Row, max2Col, 1);
									int score2 = -2*next2movesComp + next2movesUser - 3*stability - weight;
									//printf(" Score2 is:%d \n",score2);
									

									if(score2<min2Score){
										min2Score = score2;
										max2Row = k;
										max2Col = l;
										/*
										//try remove later
										char crow = max2Row + 96;
										char ccol = max2Col + 95;
										printf("min2Score: %d, row: %c, col: %c \n",min2Score, crow, ccol);
										//
										*/
										moveExists = 1;
									}

									if(score2 == min2Score){
										if(betterMatrix(n, k, l, max2Row, max2Col, 0) != 1){
											max2Row = k;
											max2Col = l;
										}
									}
								}
							}
						}
					}

					//*/

					if(moveExists == 0){
						int nextmovesComp = noAvailMoves(tmpboard,n,comp);
						int nextmovesUser = noAvailMoves(tmpboard,n,user);
						int stability = stable(n,i,j);
						int score = -2*nextmovesComp + nextmovesUser - 3*stability;
						if(score<minScore){
							minScore = score;
							//printf("minScore: %d",minScore);
							max2Row = i;
							max2Col = j;
						}
					}											
				}
			}
		}

		//Doing the flipping
		for(int i =-1; i<=1; i++){
			for(int j=-1; j<=1; j++){
				if(i==0 && j==0){
					continue;
				}
				else{
					if(checkLegalInDirection(board, n, max2Row, max2Col, comp, i, j)){
						flipmove(max2Row, max2Col, comp, i, j, n, board); //Make the flip
					}
				}
			}
		}

		char charrow= max2Row+96;
		char charcol= max2Col+95;

		printf("Computer places %c at %c%c.",comp,charrow,charcol);
		printf("\n");

		//Print board
		for(int i=0; i<=n; i++){
			for(int j=0; j<=n+1; j++){
				printf("%c",board[i][j]);
			}
			printf("\n");
		}
	}
}

int stable(int n, int k, int l){
	if(n==8){
		int stableMat[9][10] ={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							   {0, 0, 4,-3, 2, 2, 2, 2,-3, 4},
							   {0, 0,-3,-4,-1,-1,-1,-1,-4,-3},
							   {0, 0, 2,-1, 1, 0, 0, 1,-1, 2},
							   {0, 0, 2,-1, 0, 1, 1, 0,-1, 2},
							   {0, 0, 2,-1, 0, 1, 1, 0,-1, 2},
							   {0, 0, 2,-1, 1, 0, 0, 1,-1, 2},
							   {0, 0,-3,-4,-1,-1,-1,-1,-4,-3},
							   {0, 0, 4,-3, 2, 2, 2, 2,-3, 4}};
		return stableMat[k][l];
	}
	else{
		return 0;
	}

}

int betterMatrix(int n, int k, int l, int max2row, int max2col, int a){
	int weight[9][10] =	  		  {{0,0, 0 , 0  , 0 , 0, 0,  0,   0,   0},
								   {0,0,100, -10, 11, 6, 6, 11, -10, 100},
								   {0,0,-10, -20,  1, 2, 2,  1, -20, -10},
								   {0,0, 10,   1,  5, 4, 4,  5,   1,  10},
								   {0,0,  6,   2,  4, 2, 2,  4,   2,   6},
								   {0,0,  6,   2,  4, 2, 2,  4,   2,   6},
								   {0,0, 10,   1,  5, 4, 4,  5,   1,  10},
								   {0,0,-10, -20,  1, 2, 2,  1, -20, -10},
								   {0,0,100, -10, 11, 6, 6, 11, -10, 100}};

	if( a == 1){ //gives weighted matrix values
		return weight[k][l]; 

	}

	if( a== 0){
		if(n == 8){ //compares to see which pair of value is better
			if(weight[k][l] > weight[max2row][max2col]){
				return 2; //change the max to k and l
			}
			else{
				return 1; //keep the max same
			}
		}
	}
}

//Game ends if the board has not unoccupied left, chance is skipped for both the players, user does invalid move
bool end(char board[][28], int n){
	if((noAvailMoves(board,n,'W')==0 && noAvailMoves(board,n,'B')==0) || noColor(board,n,'W') + noColor(board,n,'B') == n*n){
		return true;
	}
	else{return false;}
}

int noColor(char board[][28], int n, char colour){

	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	int noWhite = 0;
	int noBlack = 0;

	for(int i=rstart; i<=rfinish; i++){
		for(int j=cstart; j<=cfinish; j++){
			if(board[i][j]=='W'){
				noWhite++;
			}
			if(board[i][j]=='B'){
				noBlack++;
			}
		}
	}

	if(colour == 'W'){
		return noWhite;
	}
	else{return noBlack;}
}

int noAvailMoves(char board[][28], int n, char colour){
	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	int numAvail = 0;

	//i and j are corrected

	for(int i=rstart; i<=rfinish;i++){
		for(int j=cstart; j<=cfinish; j++){
			if(board[i][j]=='U'){
				if(checkLegalInDirection(board, n, i, j, colour, -1, -1)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, -1, 0)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, -1, 1)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, 0, -1)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, 0, 1)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, 1, -1)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, 1, 0)){
					numAvail++;
				}

				if(checkLegalInDirection(board, n, i, j, colour, 1, 1)){
					numAvail++;
				}
			}
			else{continue;}
		}
	}

	return numAvail;
}

int counter(int row, int column, char colour, int deltaRow, int deltaCol, int n, char board[][28]){
	int changerow=row;
	int changecol=column;
	int oppinline= 0;

	//Color sorting (opposite color)
	int playerColor=colour;
	int intoppColor;
	if(playerColor==66){
		intoppColor = 87;
	}
	else{
		intoppColor = 66;
	}
	char oppColor = intoppColor;
	//

	while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
		changerow+=deltaRow;
		changecol+=deltaCol;
		if(board[changerow][changecol]==oppColor){
			oppinline+=1;
			continue;
		}
		else{break;}
	}
	return oppinline;
}

void flipmove(int row, int column, char color, int deltaRow, int deltaCol, int n, char board[][28]){

	//Color sorting (opposite color)
	int playerColor=color;
	int intoppColor;
	if(playerColor==66){
		intoppColor = 87;
	}
	else{
		intoppColor = 66;
	}
	char oppColor = intoppColor;
	//

	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	int changerow=row;
	int changecol=column;
	changerow+=deltaRow;
	changecol+=deltaCol;

	for(int i=rstart; i<rfinish; i++){
		for(int j=cstart; j<=cfinish; j++){
			//Flip the rest
			board[row][column]=color;
			while(board[changerow][changecol]==oppColor && positionInBounds(n, changerow, changecol)){
				board[changerow][changecol]=color;
				changerow+=deltaRow;
				changecol+=deltaCol;
			}
		}
	}
}

void playturn(char board[][28], int n){
	char input[3];
	printf("Enter a move:\n");
	scanf("%s",input);

	char color = input[0];
	int row = input[1]-96;
	int column = input[2]-95;

	if(checkLegalInDirection(board, n, row, column, color, -1, -1) || checkLegalInDirection(board, n, row, column, color, -1, 0) || checkLegalInDirection(board, n, row, column, color, -1, 1) || checkLegalInDirection(board, n, row, column, color, 0, -1) || checkLegalInDirection(board, n, row, column, color, 0, 1) || checkLegalInDirection(board, n, row, column, color, 1, -1) || checkLegalInDirection(board, n, row, column, color, 1, 0) || checkLegalInDirection(board, n, row, column, color, 1, 1)){
		printf("Valid move.\n");

		if(checkLegalInDirection(board, n, row, column, color, -1, -1)){
			flipmove(row, column, color, -1, -1, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, -1, 0)){
			flipmove(row, column, color, -1, 0, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, -1, 1)){
			flipmove(row, column, color, -1, 1, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, 0, -1)){
			flipmove(row, column, color, 0, -1, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, 0, 1)){
			flipmove(row, column, color, 0, 1, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, 1, -1)){
			flipmove(row, column, color, 1, -1, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, 1, 0)){
			flipmove(row, column, color, 1, 0, n, board);
		}

		if(checkLegalInDirection(board, n, row, column, color, 1, 1)){
			flipmove(row, column, color, 1, 1, n, board);
		}
	}

	else{
		printf("Invalid move.\n");
	}

	for(int i=0; i<=n; i++){
		for(int j=0; j<=n+1; j++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}

//Pass corrected row and column here
bool checkLegalInDirection(char board[][28], int n, int row, int col, char colour, int deltaRow, int deltaCol){
	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish

	//B = 66 W = 87

	//Down left
	if(deltaRow==1 && deltaCol==-1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Down middle
	if(deltaRow==1 && deltaCol==0){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Down right
	if(deltaRow==1 && deltaCol==1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Middle Left
	if(deltaRow==0 && deltaCol==-1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Middle Right
	if(deltaRow==0 && deltaCol==1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Top Left
	if(deltaRow==-1 && deltaCol==-1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	//Top Middle
	if(deltaRow==-1 && deltaCol==0){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}

	/*
	*/

	//Top Right
	if(deltaRow==-1 && deltaCol==1){
		int changerow=row;
		int changecol=col;
		int oppinline= 0;

		//Color sorting (opposite color)
		int playerColor=colour;
		int intoppColor;
		if(playerColor==66){
			intoppColor = 87;
		}
		else{
			intoppColor = 66;
		}
		char oppColor = intoppColor;
		//

		while(positionInBounds(n,changerow+deltaRow,changecol+deltaCol)){
			changerow+=deltaRow;
			changecol+=deltaCol;
			if(board[changerow][changecol]==oppColor){
				oppinline+=1;
				continue;
			}
			else{break;}
		}
		if(oppinline==0) {
			return false;
		}
		if(board[changerow][changecol]==colour){
			return true;
		}
		else{return false;}
	}
}

//Pass corrected row and column here
bool positionInBounds(int n, int row, int col){
	int rstart=1; //row start
	int cstart=2; //column start
	int rfinish=n; //row finish
	int cfinish=n+1; //column finish
	if(row >= rstart && row<=rfinish && col>=cstart && col<=cfinish){
		return true;
	}
	else{
		return false;
	}
}

void printBoard(char board[28][28], int n){
	board[0][0]=' ';

	for(int i=0; i<=n; i++){
		board[i][1]=' ';
	}
	// a= 97
	//z =122

	{ //Row a to z
		int intcount = 2;
		int alphacount =97;
		while(intcount<=27){
			char alpha = alphacount;
			board[0][intcount]=alpha;
			alphacount++;
			intcount++;
		}
	}

	{ //Column a to z
		int intcount = 1;
		int alphacount =97;
		while(intcount<=26){
			char alpha = alphacount;
			board[intcount][0]=alpha;
			alphacount++;
			intcount++;
		}
	}

	//Making all blocks U
	for(int i=1; i<=n+1; i++){
		for(int j=2; j<=n+1; j++){
			board[i][j]='U';
		}
	}

	//Making the intial game setup
	board[(n/2)][(n/2)+1]='W';
	board[(n/2)][(n/2)+2]='B';
	board[(n/2)+1][(n/2)+1]='B';
	board[(n/2)+1][(n/2)+2]='W';

	//Printing the board
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n+1; j++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}
