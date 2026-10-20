#include <stdio.h>
#include <stdlib.h>
#define ROWS 11
#define COLS 15

char map[ROWS][COLS + 1] = {
    "###############",
    "#@    #       #",
    "##### # ##### #",
    "#     # #     #",
    "# ##### # #####",
    "#       #     #",
    "# ########### #",
    "# #           #",
    "# # ######### #",
    "#          ## #",
    "#############E#"
};

void draw(void);

int main() {
    int xPosition=1, yPosition=1;
    char command;
    draw();
    while (1) {
        if (scanf(" %c", &command) != 1) {
            break;
        }
        if (command == 'q') {
            break;
        }

            switch (command) {
                case 'w':
                    if (map[xPosition-1][yPosition]!='#') {
                        map[xPosition][yPosition]=' ';
                        xPosition-=1;
                        map[xPosition][yPosition]='@';
                        draw();
                    }
                    break;
                case 's':
                    if (map[xPosition+1][yPosition]!='#') {
                        map[xPosition][yPosition]=' ';
                        xPosition+=1;
                        map[xPosition][yPosition]='@';
                        draw();
                    }
                    break;
                case 'a':
                    if (map[xPosition][yPosition-1]!='#') {
                        map[xPosition][yPosition]=' ';
                        yPosition-=1;
                        map[xPosition][yPosition]='@';
                        draw();
                    }
                    break;
                case 'd':
                    if (map[xPosition][yPosition+1]!='#') {
                        map[xPosition][yPosition]=' ';
                        yPosition+=1;
                        map[xPosition][yPosition]='@';
                        draw();
                    }
                    break;
                default:
                    break;
            }
            if (xPosition==10&&yPosition==13) {
                printf("You Win! \n");
                return 0;
            }

    }
    return 0;
}

void draw(void) {
    system("cls");
    for (int row=0;row<ROWS;row++) {
        printf("%s\n",map[row]);
    }
}