#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 6
#define LEVEL_COUNT 3

int playerRow[LEVEL_COUNT] = {2, 1, 3};
int playerCol[LEVEL_COUNT] = {3, 2, 2};
int step = 0;

char map[ROWS][COLS + 1];

void loadLevel(const char *filename)    //读取关卡地图
{
    FILE *fp = fopen(filename, "r");
    char line[COLS + 3];

    for (int row = 0; row < ROWS; row++) {
        fgets(line, sizeof line, fp);
        line[strcspn(line, "\r\n")] = '\0';
        strcpy(map[row], line);
    }

    fclose(fp); //和一位
}

void saveScore(const char *filename, int level, int steps)
{
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "%d:%d\n", level, steps);
    fclose(fp);
}

void draw(int level, int steps)
{
    system("cls");
    printf("level:%d   step:%d\n", level, steps);

    for (int row = 0; row < ROWS; row++) {
        printf("%s\n", map[row]);
    }

    printf("w/a/s/d + Enter: move, q: quit\n");
    printf("o: box, x: target, X: box on target, +: player on target\n");
}

int isWin(void) //遍历地图没有o
{
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (map[row][col] == 'o') {
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
    const char *levelFiles[LEVEL_COUNT] = {
        "level01.txt",
        "level02.txt",
        "level03.txt"
    };

    for (int index = 0; index < LEVEL_COUNT; index++) {
        loadLevel(levelFiles[index]);
        step = 0;
        draw(index + 1, step);

        char command;

        while (1) {
            scanf(" %c", &command);

            if (command == 'q') {
                return 0;
            }
            int dRow = 0;
            int dCol = 0;

            switch (command) {
                case 'w':
                    dRow = -1;
                    break;
                case 's':
                    dRow = 1;
                    break;
                case 'a':
                    dCol = -1;
                    break;
                case 'd':
                    dCol = 1;
                    break;
                default:
                    continue;
            }

            int row = playerRow[index];
            int col = playerCol[index];
            int nextRow = row + dRow;
            int nextCol = col + dCol;
            char next = map[nextRow][nextCol];

            if (next == '#') {      //Wall
                continue;
            }

            if (next == 'o' || next == 'X') {       //Box
                int boxRow = nextRow + dRow;
                int boxCol = nextCol + dCol;
                char behind = map[boxRow][boxCol];      //box next

                if (behind == '#' || behind == 'o' || behind == 'X') {      //Box+Box||Box+Wall
                    continue;
                }

                if (behind == 'x') {
                    map[boxRow][boxCol] = 'X';
                } else {
                    map[boxRow][boxCol] = 'o';
                }
            }

            if (map[row][col] == '+') {     //leave
                map[row][col] = 'x';
            } else {
                map[row][col] = ' ';
            }

            if (next == 'x' || next == 'X') {       //enter
                map[nextRow][nextCol] = '+';
            } else {
                map[nextRow][nextCol] = '@';
            }

            playerRow[index] = nextRow;
            playerCol[index] = nextCol;
            step++;
            draw(index + 1, step);

            if (isWin()) {
                printf("You Win! Steps: %d\n", step);
                saveScore("scores.txt", index + 1, step);
                break;
            }
        }
    }

    printf("All levels completed!\n");
    return 0;
}