
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
    int intimacy = 2; // 초기 친밀도
    int catPos = HOME_POS; // 초기 위치 (집)

    printIntro();
    printf("야옹이의 이름을 지어주세요: ");
    scanf("%s", catName);

    Sleep(1000);
    clearScreen();

    while (1) {
        printState(soupCount, intimacy);
        drawRoom(catPos);

        int choice;
        while (1) {
            printf("\n어떤 상호작용을 하시겠습니까?  0. 아무것도 하지 않음  1. 긁어주기\n>> ");
            scanf("%d", &choice);
            if (choice == 0 || choice == 1) break;
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            Sleep(500);
        }

        if (choice == 0) {
            printf("\n아무것도 하지 않습니다.\n");
            printf("4/6 확률로 친밀도가 떨어집니다.\n");
            int dice = rollDice();
            printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);
            if (dice <= 4) {
                intimacy--;
                if (intimacy < 0) intimacy = 0;
                printf("친밀도가 떨어졌습니다! 현재 친밀도: %d\n", intimacy);
            }
            else {
                printf("다행히 친밀도가 유지되었습니다.\n");
            }
        }
        else if (choice == 1) {
            printf("\n%s의 턱을 긁어주었습니다.\n", catName);
            printf("2/6 확률로 친밀도가 올라갑니다.\n");
            int dice = rollDice();
            printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);
            if (dice >= 5) {
                intimacy++;
                if (intimacy > 4) intimacy = 4;
                printf("친밀도가 올라갔습니다! 현재 친밀도: %d\n", intimacy);
            }
            else {
                printf("변화가 없습니다.\n");
            }
        }

        Sleep(500);

        // 야옹이 이동
        printf("\n%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", catName);
        int dice = rollDice();
        printf("주사위를 굴립니다... %d 나왔습니다!\n", dice);

        if (dice >= (6 - intimacy)) {
            printf("냄비 쪽으로 움직입니다.\n");
            if (catPos < BOWL_POS - 1) catPos++;
        }
        else {
            printf("집 쪽으로 움직입니다.\n");
            if (catPos > HOME_POS + 1) catPos--;
        }

        Sleep(500);

        // 야옹이 행동
        if (catPos == HOME_POS) {
            printf("\n%s는 자신의 집에서 편안히 쉬고 있습니다.\n", catName);
        }
        else if (catPos == BOWL_POS) {
            printf("\n%s이(가) 수프를 만듭니다!\n", catName);
            int soupType = rand() % 3;
            if (soupType == 0) printf("감자 수프를 만들었습니다!\n");
            else if (soupType == 1) printf("양송이 수프를 만들었습니다!\n");
            else printf("브로콜리 수프를 만들었습니다!\n");
            soupCount++;
        }

        Sleep(2500);
        clearScreen();
    }

    return 0;
}

void printIntro() {
    printf("====================================\n");
    printf("|       야옹이와 수프 v1           |\n");
    printf("|      (귀여운 고양이 등장!)        |\n");
    printf("|                                  |\n");
    printf("|      ( =\u2460\u03c9\u2460= )                  |\n");
    printf("|                                  |\n");
    printf("|     고양이와 친해져서 수프를      |\n");
    printf("|          만들어 보세요!          |\n");
    printf("====================================\n\n");
}

void printState(int soupCount, int intimacy) {
    const char* messages[] = {
        "곁에 오는 것조차 싫어합니다.",
        "간식 자판기 취급입니다.",
        "그럭저럭 쓸 만한 집사입니다.",
        "훌륭한 집사로 인정 받고 있습니다.",
        "집사 껌딱지입니다."
    };

    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("집사와의 관계(0~4): %d\n", intimacy);
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
