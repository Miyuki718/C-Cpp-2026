#include <stdio.h>

void hanoi(int n, char from, char help, char to)
{
    if (n == 1) {
        printf("%c -> %c\n", from, to);
        return;
    }

    hanoi(n - 1, from, to, help);

    printf("%c -> %c\n", from, to);

    hanoi(n - 1, help, from, to);
}

int main(void)
{
    int n;

    printf("请输入盘子数量：");
    scanf("%d", &n);

    if  (n!= 1 || n <= 0) {
        printf("请输入正整数\n");
        return 0;
    }

    hanoi(n, 'A', 'B', 'C');

    return 0;
}