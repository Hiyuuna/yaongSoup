
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

void printIntro();
void printState(int soupCount, int intimacy);
void drawRoom(int catPos);
void delay(int millis);
int rollDice();
void clearScreen();

int main(void) {
    srand((unsigned int)time(NULL));

    char catName[20];
    int soupCount = 0;
    int intimacy = 2; // �ʱ� ģ�е�
    int catPos = HOME_POS; // �ʱ� ��ġ (��)

    printIntro();
    printf("�߿����� �̸��� �����ּ���: ");
    scanf("%s", catName);

    Sleep(1000);
    clearScreen();

    while (1) {
        printState(soupCount, intimacy);
        drawRoom(catPos);

        int choice;
        while (1) {
            printf("\n� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?  0. �ƹ��͵� ���� ����  1. �ܾ��ֱ�\n>> ");
            scanf("%d", &choice);
            if (choice == 0 || choice == 1) break;
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
            Sleep(500);
        }

        if (choice == 0) {
            printf("\n�ƹ��͵� ���� �ʽ��ϴ�.\n");
            printf("4/6 Ȯ���� ģ�е��� �������ϴ�.\n");
            int dice = rollDice();
            printf("�ֻ����� �����ϴ�... %d ���Խ��ϴ�!\n", dice);
            if (dice <= 4) {
                intimacy--;
                if (intimacy < 0) intimacy = 0;
                printf("ģ�е��� ���������ϴ�! ���� ģ�е�: %d\n", intimacy);
            }
            else {
                printf("������ ģ�е��� �����Ǿ����ϴ�.\n");
            }
        }
        else if (choice == 1) {
            printf("\n%s�� ���� �ܾ��־����ϴ�.\n", catName);
            printf("2/6 Ȯ���� ģ�е��� �ö󰩴ϴ�.\n");
            int dice = rollDice();
            printf("�ֻ����� �����ϴ�... %d ���Խ��ϴ�!\n", dice);
            if (dice >= 5) {
                intimacy++;
                if (intimacy > 4) intimacy = 4;
                printf("ģ�е��� �ö󰬽��ϴ�! ���� ģ�е�: %d\n", intimacy);
            }
            else {
                printf("��ȭ�� �����ϴ�.\n");
            }
        }

        Sleep(500);

        // �߿��� �̵�
        printf("\n%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", catName);
        int dice = rollDice();
        printf("�ֻ����� �����ϴ�... %d ���Խ��ϴ�!\n", dice);

        if (dice >= (6 - intimacy)) {
            printf("���� ������ �����Դϴ�.\n");
            if (catPos < BOWL_POS - 1) catPos++;
        }
        else {
            printf("�� ������ �����Դϴ�.\n");
            if (catPos > HOME_POS + 1) catPos--;
        }

        Sleep(500);

        // �߿��� �ൿ
        if (catPos == HOME_POS) {
            printf("\n%s�� �ڽ��� ������ ����� ���� �ֽ��ϴ�.\n", catName);
        }
        else if (catPos == BOWL_POS) {
            printf("\n%s��(��) ������ ����ϴ�!\n", catName);
            int soupType = rand() % 3;
            if (soupType == 0) printf("���� ������ ��������ϴ�!\n");
            else if (soupType == 1) printf("����� ������ ��������ϴ�!\n");
            else printf("����ݸ� ������ ��������ϴ�!\n");
            soupCount++;
        }

        Sleep(2500);
        clearScreen();
    }

    return 0;
}

void printIntro() {
    printf("====================================\n");
    printf("|       �߿��̿� ���� v1           |\n");
    printf("|      (�Ϳ��� ����� ����!)        |\n");
    printf("|                                  |\n");
    printf("|      ( =\u2460\u03c9\u2460= )                  |\n");
    printf("|                                  |\n");
    printf("|     ����̿� ģ������ ������      |\n");
    printf("|          ����� ������!          |\n");
    printf("====================================\n\n");
}

void printState(int soupCount, int intimacy) {
    const char* messages[] = {
        "�翡 ���� ������ �Ⱦ��մϴ�.",
        "���� ���Ǳ� ����Դϴ�.",
        "�׷����� �� ���� �����Դϴ�.",
        "�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.",
        "���� �������Դϴ�."
    };

    printf("==================== ���� ���� ===================\n");
    printf("������� ���� ����: %d��\n", soupCount);
    printf("������� ����(0~4): %d\n", intimacy);
    printf("%s\n", messages[intimacy]);
    printf("==================================================\n");
}

void drawRoom(int catPos) {
    printf("\n");
    printf("##########\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == HOME_POS) printf("H");
        else if (i == BOWL_POS) printf("B");
        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == catPos) printf("C");
        else printf(" ");
    }
    printf("#\n##########\n");
}

void delay(int millis) {
    Sleep(millis);
}

int rollDice() {
    return rand() % 6 + 1; // 1~6
}

void clearScreen() {
    system("cls");
}
