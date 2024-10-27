#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
	int row1[4];
	int row2[4];
	int row3[4];
	int row4[4];
	int empty;
}board;

typedef struct {
	int locations[16];
	int count;
}locate;

int randomNumber(int min_num, int max_num);
locate locateEmpty(board gameBoard);
board slide(board gameBoard, char direction);
board combine(board gameBoard, char direction, int mode);
board generateNumber(board gameBoard);

int isMoveLeft = 1;
int isInvalid = 0;

int main(void){
	board gameBoard = {{0}, {0}, {0}, {0}, 16};
	char input;
	int game = 1;
	gameBoard = generateNumber(gameBoard);
	while(game){
		isMoveLeft = 1;
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row1[0], gameBoard.row1[1], gameBoard.row1[2], gameBoard.row1[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row2[0], gameBoard.row2[1], gameBoard.row2[2], gameBoard.row2[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row3[0], gameBoard.row3[1], gameBoard.row3[2], gameBoard.row3[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row4[0], gameBoard.row4[1], gameBoard.row4[2], gameBoard.row4[3]);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("Enter your move, Down(D/d), Up(U/u), Left(L/l), Right(R/r): ");
		scanf(" %c", &input);
		
		gameBoard = slide(gameBoard, input);
		if(isInvalid) continue;
		gameBoard = combine(gameBoard, input, 1);
		gameBoard = slide(gameBoard, input);
		
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row1[0], gameBoard.row1[1], gameBoard.row1[2], gameBoard.row1[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row2[0], gameBoard.row2[1], gameBoard.row2[2], gameBoard.row2[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row3[0], gameBoard.row3[1], gameBoard.row3[2], gameBoard.row3[3]);
		printf("%-5d%-5d%-5d%-5d\n", gameBoard.row4[0], gameBoard.row4[1], gameBoard.row4[2], gameBoard.row4[3]);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
		Sleep(500); // 1 second delay
		
		gameBoard = generateNumber(gameBoard);
		
		gameBoard = combine(gameBoard, input, 0);
		if(gameBoard.empty == 0 && !(isMoveLeft)) game = 0;
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Game Over!");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int randomNumber(int min_num, int max_num){
	int result = 0, low_num = 0, hi_num = 0;
	if (min_num < max_num){
	    low_num = min_num;
		hi_num = max_num + 1; // include max_num in output
    }
	else{
	    low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
	}
    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

locate locateEmpty(board gameBoard){
	locate empty = {{0}, 0};
	int i;
	for(i = 0; i < 4; i++){
		if(gameBoard.row1[i] == 0) empty.locations[empty.count++] = i;
	}
	for(i = 0; i < 4; i++){
		if(gameBoard.row2[i] == 0) empty.locations[empty.count++] = i + 4;
	}
	for(i = 0; i < 4; i++){
		if(gameBoard.row3[i] == 0) empty.locations[empty.count++] = i + 8;
	}
	for(i = 0; i < 4; i++){
		if(gameBoard.row4[i] == 0) empty.locations[empty.count++] = i + 12;
	}
//	printf("\n\n---------------------------------------------\ngameBoard.empty: %d count: %d locations array: ", gameBoard.empty, empty.count);
//	for(i = 0; i < 15; i++) printf("%d ", empty.locations[i]);
	
	return empty;
}

board generateNumber(board gameBoard){
	if(gameBoard.empty == 16){
		int num1 = randomNumber(0, 15), num2 = randomNumber(0, 15), value1 = randomNumber(1, 10) == 7 ? 4 : 2, value2 = randomNumber(1, 10) == 7 ? 4 : 2;
		while(num1 == num2){
			num2 = randomNumber(0, 15);
		}
		switch(num1/4){
			case 0:
				gameBoard.row1[num1] = value1;
				break;
			case 1:
				gameBoard.row2[num1 % 4] = value1;
				break;
			case 2:
				gameBoard.row3[num1 % 4] = value1;
				break;
			case 3:
				gameBoard.row4[num1 % 4] = value1;
				break;
		}
		switch(num2/4){
			case 0:
				gameBoard.row1[num2] = value2;
				break;
			case 1:
				gameBoard.row2[num2 % 4] = value2;
				break;
			case 2:
				gameBoard.row3[num2 % 4] = value2;
				break;
			case 3:
				gameBoard.row4[num2 % 4] = value2;
				break;
		}
		gameBoard.empty -= 2;
	}
	else{
		locate empty = locateEmpty(gameBoard);
		int num1 = randomNumber(0, empty.count - 1 > 0 ? empty.count - 1 : 0), value1 = randomNumber(1, 10) == 7 ? 4 : 2;
//		printf("\n\n---------------------------------------------\nnum1: %d ", num1);
		num1 = empty.locations[num1];
//		printf("Secilen Konum: %d Atanacak Rakam: %d", num1, value1);
		switch(num1/4){
			case 0:
				gameBoard.row1[num1] = value1;
				break;
			case 1:
				gameBoard.row2[num1 % 4] = value1;
				break;
			case 2:
				gameBoard.row3[num1 % 4] = value1;
				break;
			case 3:
				gameBoard.row4[num1 % 4] = value1;
				break;
		}
		gameBoard.empty -= 1;
	}
	return gameBoard;
}

board slide(board gameBoard, char direction){
	isInvalid = 0;
	int worked, num;
	
//                    Creating 2D array

	int game[4][4], i, j;
	for(i = 0; i < 4; i++) game[0][i] = gameBoard.row1[i];
	for(i = 0; i < 4; i++) game[1][i] = gameBoard.row2[i];
	for(i = 0; i < 4; i++) game[2][i] = gameBoard.row3[i];
	for(i = 0; i < 4; i++) game[3][i] = gameBoard.row4[i];
	
//           Getting the empty and filled locations
    locate empty = locateEmpty(gameBoard);
    locate filled = {{0}, 0};
    for(i = 0; i < 16; i++){
    	for(j = 0; j < empty.count; j++){
    		num = 0;
    		if(i == empty.locations[j]){
    			num = 1;
    			break;
			}
		}
		if(num == 0) filled.locations[filled.count++] = i;
	}

	switch(direction){
		case 'U':
		case 'u':
			while(1){
				worked = 0;
				for(i = 0; i < filled.count; i++){
//					printf("\n\n---------------------------------------------\nfilled.count: %d filled.locations: ", filled.count);
//					for(j = 0; j < filled.count; j++) printf("%d ", filled.locations[j]);
					if(filled.locations[i] / 4 != 0){
						if(game[filled.locations[i] / 4 - 1][filled.locations[i] % 4] == 0){
//							printf("\nChanged location: %d", filled.locations[i]);
							game[filled.locations[i] / 4 - 1][filled.locations[i] % 4] = game[filled.locations[i] / 4][filled.locations[i] % 4];
							game[filled.locations[i] / 4][filled.locations[i] % 4] = 0;
							filled.locations[i] -= 4;
							worked++;
						}
					}
				}
				if(worked > 0) continue;
				else break;
			}
			
			break;
		case 'D':
		case 'd':
			while(1){
				worked = 0;
				for(i = 0; i < filled.count; i++){
//					printf("\n\n---------------------------------------------\nfilled.count: %d filled.locations: ", filled.count);
//					for(j = 0; j < filled.count; j++) printf("%d ", filled.locations[j]);
					if(filled.locations[i] / 4 != 3){
						if(game[filled.locations[i] / 4 + 1][filled.locations[i] % 4] == 0){
//							printf("\nChanged location: %d", filled.locations[i]);
							game[filled.locations[i] / 4 + 1][filled.locations[i] % 4] = game[filled.locations[i] / 4][filled.locations[i] % 4];
							game[filled.locations[i] / 4][filled.locations[i] % 4] = 0;
							filled.locations[i] += 4;
							worked++;
						}
					}
				}
				if(worked > 0) continue;
				else break;
			}
			break;
		case 'L':
		case 'l':
			while(1){
				worked = 0;
				for(i = 0; i < filled.count; i++){
//					printf("\n\n---------------------------------------------\nfilled.count: %d filled.locations: ", filled.count);
//					for(j = 0; j < filled.count; j++) printf("%d ", filled.locations[j]);
					if(filled.locations[i] % 4 != 0){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4 - 1] == 0){
//							printf("\nChanged location: %d", filled.locations[i]);
							game[filled.locations[i] / 4][filled.locations[i] % 4 - 1] = game[filled.locations[i] / 4][filled.locations[i] % 4];
							game[filled.locations[i] / 4][filled.locations[i] % 4] = 0;
							filled.locations[i] -= 1;
							worked++;
						}
					}
				}
				if(worked > 0) continue;
				else break;
			}
			break;
		case 'R':
		case 'r':
			while(1){
				worked = 0;
				for(i = 0; i < filled.count; i++){
//					printf("\n\n---------------------------------------------\nfilled.count: %d filled.locations: ", filled.count);
//					for(j = 0; j < filled.count; j++) printf("%d ", filled.locations[j]);
					if(filled.locations[i] % 4 != 3){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4 + 1] == 0){
//							printf("\nChanged location: %d", filled.locations[i]);
							game[filled.locations[i] / 4][filled.locations[i] % 4 + 1] = game[filled.locations[i] / 4][filled.locations[i] % 4];
							game[filled.locations[i] / 4][filled.locations[i] % 4] = 0;
							filled.locations[i] += 1;
							worked++;
						}
					}
				}
				if(worked > 0) continue;
				else break;
			}
			break;
		default:
			isInvalid = 1;
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("That move is invalid, please enter a valid move!");
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			Sleep(500); // 1 second delay
			return gameBoard;
	}
	
	for(i = 0; i < 4; i++) gameBoard.row1[i] = game[0][i];
	for(i = 0; i < 4; i++) gameBoard.row2[i] = game[1][i];
	for(i = 0; i < 4; i++) gameBoard.row3[i] = game[2][i];
	for(i = 0; i < 4; i++) gameBoard.row4[i] = game[3][i];
	
	return gameBoard;
}

board combine(board gameBoard, char direction, int mode){
	
//                    Creating 2D array

	int game[4][4], i, j, num;
	for(i = 0; i < 4; i++) game[0][i] = gameBoard.row1[i];
	for(i = 0; i < 4; i++) game[1][i] = gameBoard.row2[i];
	for(i = 0; i < 4; i++) game[2][i] = gameBoard.row3[i];
	for(i = 0; i < 4; i++) game[3][i] = gameBoard.row4[i];
	
//           Getting the empty and filled locations
    locate empty = locateEmpty(gameBoard);
    locate filled = {{0}, 0};
    for(i = 0; i < 16; i++){
    	for(j = 0; j < empty.count; j++){
    		num = 0;
    		if(i == empty.locations[j]){
    			num = 1;
    			break;
			}
		}
		if(num == 0) filled.locations[filled.count++] = i;
	}
	
	if(!(mode)){
		for(i = 0; i < filled.count; i++){
		    if(filled.locations[i] / 4 != 3){
		        if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4 + 1][filled.locations[i] % 4]){
		            return gameBoard;
		        }
		    }
		}
		for(i = filled.count - 1; i >= 0; i--){
		    if(filled.locations[i] / 4 != 0){
		        if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4 - 1][filled.locations[i] % 4]){
		            return gameBoard;
		        }
		    }
		}
		for(i = 0; i < filled.count; i++){
		    if(filled.locations[i] % 4 != 3){
		        if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4][filled.locations[i] % 4 + 1]){
		            return gameBoard;
		        }
		    }
		}
		for(i = filled.count - 1; i >= 0; i--){
		    if(filled.locations[i] % 4 != 0){
		        if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4][filled.locations[i] % 4 - 1]){
		            return gameBoard;
		        }
		    }
		}
		isMoveLeft = 0;
		return gameBoard;
	}
	else{
		switch(direction){
			case 'U':
			case 'u':
				for(i = 0; i < filled.count; i++){
					if(filled.locations[i] / 4 != 3){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4 + 1][filled.locations[i] % 4]){
							game[filled.locations[i] / 4][filled.locations[i] % 4] *= 2;
							game[filled.locations[i] / 4 + 1][filled.locations[i] % 4] = 0;
						}
					}
				}
				break;
			case 'D':
			case 'd':
				for(i = filled.count - 1; i >= 0; i--){
					if(filled.locations[i] / 4 != 0){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4 - 1][filled.locations[i] % 4]){
							game[filled.locations[i] / 4][filled.locations[i] % 4] *= 2;
							game[filled.locations[i] / 4 - 1][filled.locations[i] % 4] = 0;
						}
					}
				}
				break;
			case 'L':
			case 'l':
				for(i = 0; i < filled.count; i++){
					if(filled.locations[i] % 4 != 3){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4][filled.locations[i] % 4 + 1]){
							game[filled.locations[i] / 4][filled.locations[i] % 4] *= 2;
							game[filled.locations[i] / 4][filled.locations[i] % 4 + 1] = 0;
						}
					}
				}
				break;
			case 'R':
			case 'r':
				for(i = filled.count - 1; i >= 0; i--){
					if(filled.locations[i] % 4 != 0){
						if(game[filled.locations[i] / 4][filled.locations[i] % 4] == game[filled.locations[i] / 4][filled.locations[i] % 4 - 1]){
							game[filled.locations[i] / 4][filled.locations[i] % 4] *= 2;
							game[filled.locations[i] / 4][filled.locations[i] % 4 - 1] = 0;
						}
					}
				}
				break;
		}
		
		for(i = 0; i < 4; i++) gameBoard.row1[i] = game[0][i];
		for(i = 0; i < 4; i++) gameBoard.row2[i] = game[1][i];
		for(i = 0; i < 4; i++) gameBoard.row3[i] = game[2][i];
		for(i = 0; i < 4; i++) gameBoard.row4[i] = game[3][i];
		
		return gameBoard;
	}
	
}






