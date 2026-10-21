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

    if (scanf("%d", &n) != 1) {
        printf("输入失败，请输入整数\n");
        return 0;
    }

    if (n <= 0) {
        printf("盘子数量必须大于0\n");
        return 0;
    }

    hanoi(n, 'A', 'B', 'C');

    return 0;
}