#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef TEST_INPUT
#include <conio.h>
#endif

#define ROWS 7
#define COLS 6
#define LEVEL_COUNT 3

int playerRow[LEVEL_COUNT];
int playerCol[LEVEL_COUNT];
int step = 0;

char map[ROWS][COLS + 1];

int loadLevel(const char *filename, int index)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }

    char line[64];
    int players = 0;
    int boxes = 0;
    int targets = 0;

    for (int row = 0; row < ROWS; row++) {
        if (fgets(line, sizeof line, fp) == NULL) {
            printf("%s: expected %d rows.\n", filename, ROWS);
            fclose(fp);
            return 0;
        }
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) != COLS) {
            printf("%s: row %d must have %d cells.\n", filename, row + 1, COLS);
            fclose(fp);
            return 0;
        }

        for (int col = 0; col < COLS; col++) {
            char cell = line[col];
            if (strchr("# oxX@+", cell) == NULL) {
                printf("%s: invalid cell at row %d, col %d.\n",
                       filename, row + 1, col + 1);
                fclose(fp);
                return 0;
            }
            if (cell == '@' || cell == '+') {
                playerRow[index] = row;
                playerCol[index] = col;
                players++;
            }
            if (cell == 'o' || cell == 'X') {
                boxes++;
            }
            if (cell == 'x' || cell == 'X' || cell == '+') {
                targets++;
            }
        }
        strcpy(map[row], line);
    }

    if (fgets(line, sizeof line, fp) != NULL || ferror(fp)) {
        printf("%s: too many rows or read error.\n", filename);
        fclose(fp);
        return 0;
    }
    fclose(fp);

    if (players != 1 || boxes == 0 || boxes != targets) {
        printf("%s: need one player and equal positive box/target counts.\n", filename);
        return 0;
    }
    return 1;
}

int saveScore(const char *filename, int level, int steps)
{
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    if (fprintf(fp, "%d:%d\n", level, steps) < 0) {
        printf("Could not write score.\n");
        fclose(fp);
        return 0;
    }
    if (fclose(fp) == EOF) {
        printf("Could not finish saving score.\n");
        return 0;
    }
    return 1;
}

int insideMap(int row, int col)
{
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int arrowCommand(int arrow)
{
    switch (arrow) {
        case 72: return 'w';
        case 80: return 's';
        case 75: return 'a';
        case 77: return 'd';
        default: return 0;
    }
}

int readCommand(void)
{
#ifdef TEST_INPUT
    // 只在自动验证时使用标准输入；正常游戏使用下面的 _getch。
    char command;
    return scanf(" %c", &command) == 1 ? command : EOF;
#else
    int command = _getch();
    if (command == 0 || command == 224) {
        return arrowCommand(_getch());
    }
    return command;
#endif
}

void draw(int level, int steps)
{
#ifndef NO_CLEAR
    system("cls");
#endif
    printf("level:%d   step:%d\n", level, steps);

    for (int row = 0; row < ROWS; row++) {
        printf("%s\n", map[row]);
    }

    printf("Arrow keys or w/a/s/d: move (no Enter), q: quit\n");
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
        if (!loadLevel(levelFiles[index], index)) {
            return 1;
        }
        step = 0;
        draw(index + 1, step);

        int command;

        while (1) {
            command = readCommand();

            if (command == 'q' || command == EOF) {
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
            if (!insideMap(nextRow, nextCol)) {
                continue;
            }
            char next = map[nextRow][nextCol];

            if (next == '#') {      //Wall
                continue;
            }

            if (next == 'o' || next == 'X') {       //Box
                int boxRow = nextRow + dRow;
                int boxCol = nextCol + dCol;
                if (!insideMap(boxRow, boxCol)) {
                    continue;
                }
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
                if (!saveScore("scores.txt", index + 1, step)) {
                    return 1;
                }
                break;
            }
        }
    }

    printf("All levels completed!\n");
    return 0;
}