#include <stdio.h>
#include <windows.h>   
#include <conio.h>     


void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



int main() {
    const char *msg = "A";
    int len = 0;
    while (msg[len] != '\0') len++;  

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    int width = info.srWindow.Right - info.srWindow.Left + 1;   
    int height = info.srWindow.Bottom - info.srWindow.Top + 1;  

    int x = 0;          
    int y = height / 2; 
    int dx = 1;         
    int speed = 100;    

    hideCursor();       
    
    while (1) {
      
        if (_kbhit()) {
            break;
        }

      
        gotoxy(x, y);
        for (int i = 0; i < len; i++) {
            putchar(' ');
        }

        x += dx;

        if (x <= 0) {
            x = 0;
            dx = 1;
        } else if (x + len >= width) {
            x = width - len;
            dx = -1;
        }

        gotoxy(x, y);
        printf("%s", msg);

        Sleep(speed);   
    }



    return 0;
}
