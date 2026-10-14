#include <stdio.h>
#include <time.h>

int Prime(int x, const int known[], int num)
{
    for (int i = 0; i < num && known[i] <= x / known[i]; i++) {
        if (x % known[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    const int limit = 1000;
    int prime[1000];
    int count = 1;
    prime[0] = 2;

    clock_t start = clock();

    for (int i = 3; i <= limit; i += 2) {
        if (Prime(i, prime, count)) {
            prime[count++] = i;
        }
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < count; i++) {
        printf("%4d", prime[i]);

        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    if (count % 10 != 0) {
        printf("\n");
    }

    printf("共%d个素数\n", count);
    printf("计算用时：%.6f秒\n", seconds);

    return 0;
}