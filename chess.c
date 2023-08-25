#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ♔ ♕ ♖ ♗ ♘ ♙

/* ┌ └ ┐ ┘

├ ┤ ┬ ┴
 
─ │ ┼
 
 might need these...
 
 ╟ ╢ ╧ ╤
 
*/
void showBoard (int board[8][8]) {

    printf("\n\n╔═╤═╤═╤═╤═╤═╤═╤═╗\n");
    for (int i = 0; i < 8; i++) {
        printf("║"); 
        bool flag = true;

        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 0) {
                if ((i + j) % 2 == 0) {
                    printf(" ");
                } else {
                    printf("▒");
                 
                }
           
//            printf(""); 
            } else if (board[i][j] == 1) {
                printf("♔");
             } else if (board[i][j] == 2) {
                printf("♕");
            } else if (board[i][j] == 3) {
                printf("♗");
            } else if (board[i][j] == 4) {
                printf("♘");
            } else if (board[i][j] == 5) {
                printf("♖");
            } else if (board[i][j] == 6) {
                printf("♙");
            }
        flag = false;
        if (!flag) {
                printf("|"); 
        }
        }
        printf("\n");

        if (i < 7) {
            printf("║─┼─┼─┼─┼─┼─┼─┼─║\n") ;
        }
    }
        printf("╚═╧═╧═╧═╧═╧═╧═╧═╝\n");

}


bool isValidMove (char* input, int board[8][8]) {
	int y1 = input[0] - 48;
	int x1 = input[1] - 48;
	int y2 = input[3] - 48;
	int x2 = input[4] - 48;
	
	// out of bounds check
	if (x1 > 7 || x1 < 0) {
		return false;
	} else if (y1 > 7 || y1 < 0) {
		return false;
	} else if (x2 > 7 || x2 < 0) {
		return false;
	} else if (y2 > 7 || y2 < 0) {
		return false;
	}
	
	// piece move checks 
	int* validMoves[2];
	int xcheck = x1; // x1
	int ycheck = y1; // y1
	int piecesInWay = 0;
	switch (board[x1][y1]) {
		case 0: // moving a blank spot is never valid
			return false;
		case 1: // King
			if (abs(x1 - x2) <= 1 && abs(y1-y2) <= 1) {
			return true;
		}
		case 2: // Queen
		//printf("Queen Selected\n");
			while (true) {
				xcheck += (x1 > x2)? -1 : 1;
				ycheck += (y1 > y2)? -1 : 1;
				if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
					break;
				}
				if (board[xcheck][ycheck] != 0) {
					piecesInWay += 1;
				} 
				if (piecesInWay == 2) {
					break;
				}
				if (xcheck == x2 && ycheck == y2) {
					return true;
				}
			}
			xcheck = x1;
			ycheck = y1;
			piecesInWay = 0;		
			while (true) {
				//printf("Calculating Rook Movement at %d, %d\n", ycheck, xcheck);
				if (y1 == y2) {
					//printf("Horzontal!\n");
					xcheck += (x1 > x2)? -1 : 1;
				} else if (x1 == x2) {
					//printf("Vertical!\n");
					ycheck += (y1 > y2)? -1 : 1;
				} 
				//printf("Now checking %d, %d\n", ycheck, xcheck);
			
				if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
					//printf("Out of bounds!\n");
					break;
				}
				if (board[xcheck][ycheck] != 0) {
					//printf("Hit Piece: %d\n", board[xcheck][ycheck]);
					piecesInWay += 1;
				} 	
				if (piecesInWay == 2) {
					//printf("Hit Second Piece: %d\n", board[xcheck][ycheck]);
					break;
				}	
				if (xcheck == x2 && ycheck == y2) {
					return true;
				}
			}	
			break;
		case 3 : // Bishop
			while (true) {
			xcheck += (x1 > x2)? -1 : 1;
			ycheck += (y1 > y2)? -1 : 1;
		 	if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				break;
			}
			if (board[xcheck][ycheck] != 0) {
				piecesInWay += 1;
			} 
			if (piecesInWay == 2) {
				break;
			}
			if (xcheck == x2 && ycheck == y2) {
				return true;
			}
		}
		case 4 : // Knight
			if (abs(x1 - x2) == 1) {
			if (abs(y2 - y1) == 2) {
				return true;
			}
		} else if (abs(x1 - x2) == 2) {
			if (abs(y2 - y1) == 1) {
				return true;
			}
		}
		case 5 : // Rook
			while (true) {
			if (y1 == y2) {
				xcheck += (x1 > x2)? -1 : 1;
			} else if (x1 == x2) {
				ycheck += (y1 > y2)? -1 : 1;
			} else {
				return false;
			}
			
		 	if (xcheck < 0 || ycheck < 0 || xcheck > 7 || ycheck > 7) {
				break;
			}
			if (board[xcheck][ycheck] != 0) {
				piecesInWay += 1;
			} 
			if (piecesInWay == 2) {
				break;
			}
			if (xcheck == x2 && ycheck == y2) {
				return true;
			}
		}
		case 6 : // Pawn
		//printf("Pawn Selected\n");
		//printf("Moving in column %d \n", y1);
		//printf("y1-y2=%d\n", x1-x2);
		if (x1 - x2 == 1 && y1 == y2) { // forward one
			printf("Detected forward move by 1\n");
			if (board[x2][y2] == 0) {
				return true;
			}
		} else if (x1 - x2 == 2 && y1 == y2) { // forward two
//			printf("Detected forward move by 2\n");
			if (board[x2][y2] == 0 && board[x2+1][y2] == 0 && x1 == 6) {
				return true;
			}
		} else if (abs(y1 - y2) == 1 && x1-x2 == 1) { // capture left or right
			//printf("Detected Capture\n");
			if (board[x2][y2] != 0) {
				return true;
			}
		}
	
	}
	/*
	if (!memberOf(validMoves, end_x, end_y)) {
		return false;
	}
	*/
	return true;
}

void makeMove (char* input, int board[8][8]) {
	int start_y = input[0] - 48;
	int start_x = input[1] - 48;
	int end_y = input[3] - 48;
	int end_x = input[4] - 48;
	
	board[end_x][end_y] = board[start_x][start_y];
	board[start_x][start_y] = 0;
}

int main () {
	printf("Welcome to Terminal Chess!\n");
	printf("Initializing Board...\n")	;

	int board [8][8] = { {5, 4, 3, 2, 1, 3, 4, 5}
			   , {6, 6, 6, 6, 6, 6, 6, 6}
			   , {0, 0, 0, 0, 0, 0, 0, 0}
			   , {0, 0, 0, 0, 0, 0, 0, 0}
		           , {0, 0, 0, 0, 0, 0, 0, 0} 
		           , {0, 0, 0, 0, 0, 0, 0, 0}
		           , {6, 6, 6, 6, 6, 6, 6, 6}
			   , {5, 4, 3, 2, 1, 3, 4, 5}
				             } ;
  char buf[100];
  bool whitesMove = true;
	printf("Board Initialized!\n") ;
	
 	showBoard(board);

  printf("Enter `q` to quit at any time.\n");
  printf("Moves are entered as co-ordinate pairs, such as \"13-33\" \n");
  do {
    bool flag = false; 
    showBoard(board);
    do {
	if (flag) {
		printf("Move Invalid! Try again!");
	}
    	if (whitesMove) {
      		printf("White to move.\n");
    	} else {
      		printf("Black to move.\n");
    	}
    	printf("♔ >> ");
	scanf("%s", buf);
	flag = true;

    } while (!isValidMove(buf, board) && ( buf[0] != 'q' && buf[0] != 'Q')); 
    makeMove(buf, board);
    whitesMove = !whitesMove;
    }while( buf[0] != 'q' && buf[0] != 'Q');
    printf("Terminating...\n") ;
}
