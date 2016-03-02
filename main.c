#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define ROWS 10
#define COLS 10


void gotoxy(int x, int y){
	printf("%c[%d;%df", 0x1B, y, x);
}

/***************************************************
* The folowing function was taken from this stack overflow post
* http://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
***************************************************/

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
/**********************************************
* End function
**********************************************/


void printMap(char map[][COLS], int x, int y){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			gotoxy(j, i);
			printf("%c",map[i][j]);
		}
		puts("");
	}
}

int main(){
	int cont = 1, i, j, x = COLS / 2, y = ROWS / 2;
	char map[ROWS][COLS];
	char input;
	
	system("clear");
	printf("\e[?25l");  //Hides cursor

	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLS; j++){
			map[i][j] = ' ';
		}
	}

	while(cont){
		printMap(map, x, y);
		
		gotoxy(x, y);	
		printf("x");
		fflush(stdout);

		input = getch();
		
		gotoxy(x, y);
		printf(" ");
		fflush(stdout);
		
		if(input == 'w')
			y--;
		else if(input == 's')
			y++;
		else if(input == 'a')
			x--;
		else if(input == 'd')
			x++;
		else if(input == 'q'){
			system("clear");
			cont = 0;
			printf("\e[?25h");  //unhides cursor
		}
		
		if(x < 0)
			x *= -1;
		if(y < 0)
			y *= -1;
	}
}
