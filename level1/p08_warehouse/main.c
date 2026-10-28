#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
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

    char name[32];
    int amount;
    int result;

    while ((result = fscanf(fp, "%31s %d", name, &amount)) == 2) {
        if (goodsAmount == MAX_GOODS) {
            printf("库存文件满\n");
            fclose(fp);
            return 0;
        }
        strcpy(goods[goodsAmount].name, name);
        goods[goodsAmount].amount = amount;
        goodsAmount++;
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
        int option;
        int result = scanf("%d", &option);

        if (result == EOF) {
            return saveGoods(DATA_FILE) ? 0 : 1;
        }
        if (result != 1) {
            printf("请输入菜单数字！\n");
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
                if (scanf("%31s %d", name1, &amount1) != 2) {
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
                if (scanf("%31s %d", name2, &amount2) != 2) {
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
