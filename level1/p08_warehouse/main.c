#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define DATA_FILE "data.txt"
#define MAX_GOODS 100

typedef struct Goods {
    char name[32];
    int amount;
} Goods;

Goods goods[MAX_GOODS];
int goodsAmount = 0;

// 每次读取整行；过长输入也要读完，避免干扰下一次菜单。
// 1: 成功，0: 输入结束，-1: 行太长。
int readLine(FILE *fp, char *line, int capacity) {
    if (fgets(line, capacity, fp) == NULL) {
        return 0;
    }
    if (strchr(line, '\n') == NULL) {
        int ch = fgetc(fp);
        if (ch != EOF && ch != '\n') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }
    line[strcspn(line, "\r\n")] = '\0';
    return 1;
}

int parseInt(const char *text, int *value) {
    char *end;
    errno = 0;
    long number = strtol(text, &end, 10);
    if (end == text || errno == ERANGE || number < INT_MIN || number > INT_MAX) {
        return 0;
    }
    while (isspace((unsigned char)*end)) {
        end++;
    }
    if (*end != '\0') {
        return 0;
    }
    *value = (int)number;
    return 1;
}

// 型号不能含空白；数量后不允许附带额外字段。
int parseGoods(const char *line, char *name, int *amount) {
    char number[128];
    char extra[2];
    if (sscanf(line, "%31s %127s %1s", name, number, extra) != 2) {
        return 0;
    }
    return parseInt(number, amount);
}

int findGoods(const char *name) {
    for (int i = 0; i < goodsAmount; i++) {
        if (strcmp(name, goods[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

int loadData(const char *filename) {
    FILE *fp = fopen(filename, "r");
    goodsAmount = 0;

    if (fp == NULL) {
        if (errno == ENOENT) {
            return 1;
        }
        perror("无法打开库存文件");
        return 0;
    }

    char line[256];
    char name[32];
    int amount;
    int result;

    while ((result = readLine(fp, line, sizeof line)) != 0) {
        if (result < 0 || !parseGoods(line, name, &amount) || amount < 0 ||
            goodsAmount == MAX_GOODS || findGoods(name) != -1) {
            printf("库存文件格式错误、数量非法、型号重复或种类过多。\n");
            fclose(fp);
            return 0;
        }
        strcpy(goods[goodsAmount].name, name);
        goods[goodsAmount].amount = amount;
        goodsAmount++;
    }
    if (ferror(fp)) {
        perror("读取库存失败");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}

int saveGoods(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("无法保存库存");
        return 0;
    }

    for (int i = 0; i < goodsAmount; i++) {
        if (fprintf(fp, "%s %d\n", goods[i].name, goods[i].amount) < 0) {
            printf("写入库存失败\n");
            fclose(fp);
            return 0;
        }
    }

    if (fclose(fp) == EOF) {
        printf("关闭库存文件失败\n");
        return 0;
    }
    return 1;
}

void showMenu(void) {
    printf("\n菜单\n");
    printf("1. 显示存货列表\n");
    printf("2. 入库\n");
    printf("3. 出库\n");
    printf("4. 保存并退出\n");
    printf("请选择功能: ");
}

void showGoods(void) {
    if (goodsAmount == 0) {
        printf("暂无存货！\n");
        return;
    }

    printf("型号\t数量\n");
    for (int i = 0; i < goodsAmount; i++) {
        printf("%s\t%d\n", goods[i].name, goods[i].amount);
    }
}

void in(const char *input, int quantity) {
    if (quantity <= 0) {
        printf("入库数量必须大于 0！\n");
        return;
    }

    int place = findGoods(input);
    if (place == -1) {
        if (goodsAmount == MAX_GOODS) {
            printf("货物种类已满！\n");
            return;
        }
        strcpy(goods[goodsAmount].name, input);
        goods[goodsAmount].amount = quantity;
        goodsAmount++;
    } else {
        if (quantity > INT_MAX - goods[place].amount) {
            printf("累计库存数量溢出！\n");
            return;
        }
        goods[place].amount += quantity;
    }
    printf("成功入库！\n");
}

void out(const char *output, int quantity) {
    if (quantity <= 0) {
        printf("出库数量必须大于 0！\n");
        return;
    }

    int place = findGoods(output);
    if (place == -1) {
        printf("货物不存在！\n");
        return;
    }

    if (quantity > goods[place].amount) {
        printf("货物不足！\n");
        return;
    }

    goods[place].amount -= quantity;
    printf("成功出库！\n");
}

int main(void) {
#ifdef _WIN32
    // Match the Windows console input/output encoding to UTF-8.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (!loadData(DATA_FILE)) {
        return 1;
    }

    while (1) {
        showMenu();
        char line[256];
        int option;
        int result = readLine(stdin, line, sizeof line);
        if (result == 0) {
            return saveGoods(DATA_FILE) ? 0 : 1;
        }
        if (result < 0 || !parseInt(line, &option)) {
            printf("请输入完整的菜单数字！\n");
            continue;
        }

        switch (option) {
            case 1:
                showGoods();
                break;
            case 2: {
                char name1[32];
                int amount1;
                printf("请输入货物型号和数量：\n");
                if (readLine(stdin, line, sizeof line) != 1 ||
                    !parseGoods(line, name1, &amount1)) {
                    printf("输入格式错误！\n");
                    break;
                }
                in(name1, amount1);
                break;
            }
            case 3: {
                char name2[32];
                int amount2;
                printf("请输入货物型号和数量：\n");
                if (readLine(stdin, line, sizeof line) != 1 ||
                    !parseGoods(line, name2, &amount2)) {
                    printf("输入格式错误！\n");
                    break;
                }
                out(name2, amount2);
                break;
            }
            case 4:
                if (saveGoods(DATA_FILE)) {
                    printf("库存已保存，再见！\n");
                    return 0;
                }
                printf("保存失败，暂不退出，请检查路径后重试。\n");
                break;
            default:
                printf("没有这个选项！\n");
                break;
        }
    }
}
