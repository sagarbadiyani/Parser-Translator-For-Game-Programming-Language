#include "interface.h"

coordinate generateRandomIndex(){
    coordinate arr[16];
	int cx = 0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(gameBoard[i][j] == 0){
				coordinate p;
				p.ff = i;
				p.ss = j;
				arr[cx] = p;
				cx++;
			}
		}
	}
    coordinate dead;
    dead.ff = -1;
    dead.ss = -1;
    if(cx == 0) return dead;

	int ind = rand() % cx;
	return arr[ind];
}

void init(){
    srand(time(0));
    coordinate p = generateRandomIndex();
    int x = rand()%5;
	if(x == 4) gameBoard[p.ff][p.ss] = 4;
	else gameBoard[p.ff][p.ss] = 2;

    printf("2048> Hi, I am the 2048-game Engine.\n");
    printf("2048> The start state is:\n");
    printGameBoard();
    printf("2048> Please type a command.\n");
    boardState();
    printf("----> ");
	
	// p = generateRandomIndex();
	// x = rand()%5;
	// if(x == 4) gameBoard[p.ff][p.ss] = 4;
	// else gameBoard[p.ff][p.ss] = 2;

    // printGameBoard();
}

void printGameBoard(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(gameBoard[i][j]) printf("%d\t", gameBoard[i][j]);
			else printf("-\t");
		}
		printf("\n");
	}
    // printf("------------------------------------------------------------------------------------------------------------\n");
}

void generateTile(){
	coordinate p = generateRandomIndex();
    if(p.ff == -1){
        printf("The Board is Full.\n");
        fprintf(stderr, "-1\n");
        return;
    }
	int x = rand()%5;
	if(x == 4) gameBoard[p.ff][p.ss] = 4;
	else gameBoard[p.ff][p.ss] = 2;
}


void transpose(){
    int tempgameBoard[4][4];
    Names tempnames[4][4];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempgameBoard[i][j] = gameBoard[i][j];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempnames[i][j] = names[i][j];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameBoard[i][j] = tempgameBoard[j][i];
            names[i][j] = tempnames[j][i];
        }
    }
}

void mirrorX(){
    int tempgameBoard[4][4];
    Names tempnames[4][4];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempgameBoard[i][j] = gameBoard[i][j];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempnames[i][j] = names[i][j];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameBoard[i][j] = tempgameBoard[3-i][j];
            names[i][j] = tempnames[3-i][j]; 
        }
    }
}

void mirrorY(){
    int tempgameBoard[4][4];
    Names tempnames[4][4];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempgameBoard[i][j] = gameBoard[i][j];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) tempnames[i][j] = names[i][j];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameBoard[i][j] = tempgameBoard[i][3-j];
            names[i][j] = tempnames[i][3-j]; 
        }
    }
}

void rotateMatrix(int direction){
    if(direction == 1){
        transpose();
        mirrorX();
    }

    else if(direction == 2){
        mirrorY();
    }

    else if(direction == 3){
        transpose();
        mirrorY();
    }
    else return;
}

void unrotate(int direction){
    if(direction == 1){
        mirrorX();
        transpose();
    }

    else if(direction == 2){
        mirrorY();
    }

    else if(direction == 3){
        mirrorY();
        transpose();
    }
    else return;
}


Names mergeNames(Names a, Names b, int operation){
    if(operation == 1){
        Names temp_null;
        temp_null.count = 0;
        memset(temp_null.vars, 0, sizeof(temp_null.vars));
        return temp_null;
    }

    int cx = a.count;
    int dx = b.count;
    int i = 0;
    while(i<dx){
        strcpy(a.vars[cx+i], b.vars[i]);
        i++;
    }
    a.count += b.count;
    return a;
}

int mergeVal(int a, int b, int operation){
    if(operation == 0) return 2*a;
    else if(operation == 1) return 0;
    else if(operation == 2) return a * a;
    else return 1;
}

void move(int operation){
    Names temp_null;
    temp_null.count = 0;
    memset(temp_null.vars, 0, sizeof(temp_null.vars));

    int tempgameBoard[4][4];
    Names tempnames[4][4];
    memset(tempgameBoard, 0, sizeof(tempgameBoard));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            // tempnames[i][j].count = 0;
            // for(int k=0;k<100;k++) {
            //     memset(tempnames[i][j].vars[k],0,sizeof(tempnames[i][j].vars[k]));
            // }
            tempnames[i][j] = temp_null;
        }
    }
    

    for(int i=0;i<4;i++){
        int cx = 0;
        for(int j=0;j<4;j++){
            if(gameBoard[i][j] != 0){
                tempgameBoard[i][cx] = gameBoard[i][j];
                tempnames[i][cx] = names[i][j];
                cx++;
            }
        }

        if(cx == 2){
            if(tempgameBoard[i][0] == tempgameBoard[i][1]){
                tempnames[i][0] = mergeNames(tempnames[i][0], tempnames[i][1], operation);
                tempgameBoard[i][0] = mergeVal(tempgameBoard[i][0], tempgameBoard[i][1], operation);
                tempgameBoard[i][1] = 0;
                tempnames[i][1] = temp_null;
                // printf("_________Count: %d________\n", temp_null->count);
            }
        }

        else if(cx == 3){
            if(tempgameBoard[i][0] == tempgameBoard[i][1]){
                tempnames[i][0] = mergeNames(tempnames[i][0], tempnames[i][1], operation);
                tempgameBoard[i][0] = mergeVal(tempgameBoard[i][0], tempgameBoard[i][1], operation);
                tempgameBoard[i][1] = tempgameBoard[i][2];
                tempnames[i][1] = tempnames[i][2];
                tempgameBoard[i][2] = 0;
                tempnames[i][2] = temp_null;
            }
            else if(tempgameBoard[i][1] == tempgameBoard[i][2]){
                tempnames[i][1] = mergeNames(tempnames[i][1], tempnames[i][2], operation);
                tempgameBoard[i][1] = mergeVal(tempgameBoard[i][1], tempgameBoard[i][2], operation);
                tempgameBoard[i][2] = 0;
                tempnames[i][2] = temp_null;
            }
        }

        else if(cx == 4){
            if(tempgameBoard[i][0] == tempgameBoard[i][1]){
                if(tempgameBoard[i][2] == tempgameBoard[i][3]){
                    tempnames[i][0] = mergeNames(tempnames[i][0], tempnames[i][1], operation);
                    tempgameBoard[i][0] = mergeVal(tempgameBoard[i][0], tempgameBoard[i][1], operation);

                    tempnames[i][2] = mergeNames(tempnames[i][2], tempnames[i][3], operation);
                    tempgameBoard[i][2] = mergeVal(tempgameBoard[i][2], tempgameBoard[i][3], operation);

                    tempnames[i][1] = tempnames[i][2];
                    tempgameBoard[i][1] = tempgameBoard[i][2];

                    tempgameBoard[i][2] = 0;
                    tempgameBoard[i][3] = 0;
                    tempnames[i][2] = temp_null;
                    tempnames[i][3] = temp_null;
                }
                else{
                    tempnames[i][0] = mergeNames(tempnames[i][0], tempnames[i][1], operation);
                    tempgameBoard[i][0] = mergeVal(tempgameBoard[i][0], tempgameBoard[i][1], operation);

                    tempgameBoard[i][1] = tempgameBoard[i][2];
                    tempgameBoard[i][2] = tempgameBoard[i][3];
                    tempgameBoard[i][3] = 0;

                    tempnames[i][1] = tempnames[i][2];
                    tempnames[i][2] = tempnames[i][3];
                    tempnames[i][3] = temp_null;
                }
            }
            else if(tempgameBoard[i][1] == tempgameBoard[i][2]){
                tempnames[i][1] = mergeNames(tempnames[i][1], tempnames[i][2], operation);
                tempgameBoard[i][1] = mergeVal(tempgameBoard[i][1], tempgameBoard[i][2], operation);
                tempgameBoard[i][2] = tempgameBoard[i][3];
                tempnames[i][2] = tempnames[i][3];
                tempgameBoard[i][3] = 0;
                tempnames[i][3] = temp_null;
            }
            else if(tempgameBoard[i][2] == tempgameBoard[i][3]){
                tempnames[i][2] = mergeNames(tempnames[i][2], tempnames[i][3], operation);
                tempgameBoard[i][2] = mergeVal(tempgameBoard[i][2], tempgameBoard[i][3], operation);
                tempgameBoard[i][3] = 0;
                tempnames[i][3] = temp_null;
            }
        }

        for(int j=0;j<4;j++){
            gameBoard[i][j] = tempgameBoard[i][j];
            names[i][j] = tempnames[i][j];
        }
    }


}

void action(int direction, int operation){
    //LEFT-0 UP-1 RIGHT-2 DOWN-3
    //ADD-0 SUB-1 MUL-2 DIV-3
    rotateMatrix(direction);
    move(operation);
    unrotate(direction);
    generateTile();
    // printGameBoard();

    if(direction == 0) printf("2048> Thanks, left move done, random tile added.\n");
    else if(direction == 1) printf("2048> Thanks, up move done, random tile added.\n");
    else if(direction == 2) printf("2048> Thanks, right move done, random tile added.\n");
    else printf("2048> Thanks, down move done, random tile added.\n");

    printf("2048> The current state is:\n");
    printGameBoard();
    printf("2048> Please type a command.\n----> ");
    boardState();
}

void assignName(int x, int y, char *str){
    if(x<0 || x>3 || y<0 || y>3){
        fprintf(stderr, "-1\n");
        printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
        printf("----> ");
        return;
    }
    if(gameBoard[x][y] == 0){
        fprintf(stderr, "-1\n");
        printf("2048> Can't Assign Value to a Zero Tile.\n");
        printf("----> ");
        return;
    }
    if( (strcmp(str, "ADD") == 0) || (strcmp(str, "SUBTRACT") == 0) || (strcmp(str, "MULTIPLY") == 0) || (strcmp(str, "DIVIDE") == 0) || (strcmp(str, "UP") == 0) || (strcmp(str, "DOWN") == 0) || (strcmp(str, "LEFT") == 0) || (strcmp(str, "RIGHT") == 0) || (strcmp(str, "ASSIGN") == 0) || (strcmp(str, "TO") == 0) || (strcmp(str, "VAR") == 0) || (strcmp(str, "IS") == 0) ||(strcmp(str, "VALUE") == 0) ||(strcmp(str, "IN") == 0) ){
        fprintf(stderr, "-1\n");
        printf("No, a keyword cannot be a variable name.\n");
        printf("----> ");
        return;
    }
    int b = 0;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            int cx = names[i][j].count;
            for(int k=0;k<cx;k++){
                if(strncmp(names[i][j].vars[k], str, strlen(str)) == 0){
                    b = 1;
                    break;
                }
            }
        }
    }

    if(b == 1){
        fprintf(stderr, "-1\n");
        printf("2048> A tile with that name already exists.\n");
        printf("----> ");
        return;
    }

    int cx = names[x][y].count;
    strcpy(names[x][y].vars[cx], str);
    names[x][y].count++;

    printf("2048> Thanks, naming done.\n2048> Please type a command.\n----> ");
    boardState();
}

void printNames(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(names[i][j].count > 0){
                // printf("i:%d j:%d | ",i,j);
                // printf("count = %d ", names[i][j].count);
                // for(int k=0;k<names[i][j].count;k++) printf("%s\t",names[i][j].vars[k]);
                // printf("\n"); 
            }
        }
    }
}

void assignVal(int x, int y, int z){
    if(x<0 || x>3 || y<0 || y>3){
        fprintf(stderr, "-1\n");
        printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
        printf("----> ");
        return;
    }
    gameBoard[x][y] = z;
    if(z == 0){
        Names temp_null;
        temp_null.count = 0;
        memset(temp_null.vars, 0, sizeof(temp_null.vars));
        names[x][y] = temp_null;
    }
    printf("2048> Thanks, assignment done.\n");
    printf("2048> The current state is:\n");
    printGameBoard();
    printf("2048> Please type a command.\n----> ");
    boardState();
}

void queryTile(int x, int y){
    if(x<0 || x>3 || y<0 || y>3){
        fprintf(stderr, "-1\n");
        printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
        printf("----> ");
        return;
    }
    printf("2048> The tile at %d,%d is: %d\n",x+1,y+1,gameBoard[x][y]);
    printf("----> ");
    boardState();
}

void boardState(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==3 && j==3) fprintf(stderr, "%d",gameBoard[i][j]);
            else fprintf(stderr, "%d ",gameBoard[i][j]);
        }
    }
    int cx = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(names[i][j].count > 0) cx++;
        }
    }

    if(cx == 0){
        fprintf(stderr, "\n");
        return;
    }

    fprintf(stderr, " ");

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(names[i][j].count > 0){
                fprintf(stderr,"%d,%d",i+1,j+1);
                for(int k=0;k<names[i][j].count;k++){
                    if(k == (names[i][j].count - 1)) fprintf(stderr,"%s ",names[i][j].vars[k]);
                    else fprintf(stderr,"%s,",names[i][j].vars[k]);
                }
            }
        }
    }
    fprintf(stderr,"\n");
}