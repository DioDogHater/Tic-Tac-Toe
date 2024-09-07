#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0

int toes[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
};

int wins[8][3][2] = {
	{{0,0},{0,1},{0,2}},
	{{2,0},{2,1},{2,2}},
	{{0,0},{1,0},{2,0}},
	{{2,0},{2,1},{2,2}},
	{{1,0},{1,1},{1,2}},
	{{0,1},{1,1},{2,1}},
	{{0,0},{1,1},{2,2}},
	{{2,0},{1,1},{0,2}}
};

int abs(int x){
	if(x < 0){return -x;}
	return x;
}

void drawToes(){
    for(int y = -1; y < 3; y++){
        for(int x = -1; x < 3; x++){
			if(y == -1){if(x == -1){printf("\\|");continue;}else{printf("%d|",x);continue;}}
			if(x == -1){printf("%d|",y);continue;}
            switch(toes[y][x]){
            case 0:
                printf(" ");
                break;
            case 1:
                printf("X");
                break;
            case -1:
                printf("O");
                break;
            default:
                printf("!E!");
            }
			printf("|");
        }
		printf("\n");
		if(y < 2){printf("--------\n");}
    }
}

int getToe(int win, int x){
	return toes[wins[win][x][0]][wins[win][x][1]];
}

void setToe(int win, int x, int val){
	toes[wins[win][x][0]][wins[win][x][1]] = val;
}

int getWinner(){
	for(int win = 0; win < 8; win++){
		int startVal = getToe(win,0);
		for(int x = 1; x < 3; x++){
			if(getToe(win,x) != startVal){break;}
			if(x == 2){return startVal;}
		}
	}
	return 0;
}

int getWinProb(int win, int porc){
	unsigned int quantity = 0;
	unsigned int enemyQuant = 0;
	for(int x = 0; x < 3; x++){
		if(getToe(win,x) == porc){quantity++;}
		if(getToe(win,x) == -porc){enemyQuant++;}
	}
	if(quantity-enemyQuant < 0){return 0;}
	return quantity-enemyQuant;
}

int boardFull(){
	int total = 0;
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			if(toes[y][x] != 0){total++;}
		}
	}
	if(total == 9){return true;}
	return false;
}

void doSomething(){
	if(boardFull() == true){return;}
	for(int win = 0; win < 8; win++){
		// Check for any possible wins from the player and stop it
		if(getWinProb(win,1) == 2){
			for(int x = 0; x < 3; x++){
				if(getToe(win,x) == 0){
					setToe(win,x,-1);
					return;
				}
			}
		}int cpuWinProb = getWinProb(win,-1);
		// Check for any possible wins for the cpu and take it
		if(cpuWinProb == 2){
			for(int x = 0; x < 3; x++){
				if(getToe(win,x) == 0){
					setToe(win,x,-1);
					return;
				}
			}
		}// Check for any possible moves that might help the cpu
		if(cpuWinProb == 1){
			for(int x = 0; x < 3; x++){
				if(getToe(win,x) == 0){
					setToe(win,x,-1);
					return;
				}
			}
		}
	}
	rand();
	int randWin = rand()%8;
	while(getWinProb(randWin,1) != 0){randWin = rand()%8;}
	int randMove = rand()%3;
	while(getToe(randWin,randMove) != 0){randMove = rand()%3;}
	setToe(randWin,randMove,-1);
	return;
}

void resetToes(){
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){
			toes[y][x] = 0;
		}
	}
}

int checkWin(){
	int currWin = getWinner();
	if(currWin != 0){
		system("cls");
		drawToes();
		if(currWin == 1){printf("YOU WON!");}else{printf("YOU LOST!");}
		return true;
	}else if(boardFull() == true){
		system("cls");
		drawToes();
		printf("TIE!");
		return true;
	}
	return false;
}

void gameLoop(){
	system("cls");
	drawToes();
    while(true){
		int x; int y;
		printf("ENTER X Y:\n> ");
		scanf("%d %d",&x,&y);
		if(x < 0 || y < 0 || x > 2 || y > 2 || toes[y][x] != 0){continue;}
		toes[y][x] = 1;
		if(checkWin()){return;}
		doSomething();
		if(checkWin()){return;}
		system("cls");
		drawToes();
	}
}

int main(){
	srand(time(NULL));
	while(true){
		gameLoop();
		printf("\nPLAY AGAIN? (y/n): ");
		char answer;
		scanf("\n%c",&answer);
		if(answer == 'y' || answer == 'Y'){resetToes();continue;}
		else{break;}
	}
	return 0;
}
