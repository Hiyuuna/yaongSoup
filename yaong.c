
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

void printIntro();
void printState(int soupCount, int intimacy, int mood, int cp); 
void drawRoom(int catPos, int S, int T); //S = 스크래처 있음 , T = 타워 있음 
void updateBadMood(int* mood, int intimacy, const char* catName); //기분나빠짐
void delay(int millis);
int rollDice();
void clearScreen();


//메인
int main(void) {
    srand((unsigned int)time(NULL));

    char catName[20];
    int soupCount = 0;
	int intimacy = 2; 
  
    int mood = 3;  
    int cp = 0;
    int catPos = HOME_POS;
    int S = 0;  
    int T = 0;  

    printIntro();
    printf("야옹이의 이름을 지어주세요: ");
    scanf("%s", catName);

    Sleep(1000);
    clearScreen();

    while (1) {
		printState(soupCount, intimacy, mood, cp); 
        drawRoom(catPos, S, T);

        updateBadMood(&mood, intimacy, catName);

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

        // 야옹이 기분 기반 이동
        printf("\n%s의 기분에 따라 행동합니다.\n", catName);

        if (mood == 0) {
            if (catPos > HOME_POS + 1) {
                catPos--;
                printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", catName);
            }
            else {
                printf("%s은(는) 이미 집 근처입니다.\n", catName);
            }
        }
        else if (mood == 1) {
            if (S || T) {
                int target = -1;
                if (S && T) {
                    target = (abs(catPos - 3) <= abs(catPos - 5)) ? 3 : 5;
                }
                else if (S) {
                    target = 3;
                }
                else if (T) {
                    target = 5;
                }

                if (target > catPos && catPos < BOWL_POS - 1) {
                    catPos++;
                }
                else if (target < catPos && catPos > HOME_POS + 1) {
                    catPos--;
                }

                printf("%s은(는) 심심해서 놀이기구(%c) 쪽으로 이동합니다.\n", catName, (target == 3 ? 'S' : 'T'));
            }
            else {
                printf("놀 거리가 없어서 기분이 매우 나빠집니다!\n");
                if (mood > 0) mood--;
            }
        }
        else if (mood == 2) {
            printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n", catName);
        }
        else if (mood == 3) {
            if (catPos < BOWL_POS - 1) {
                catPos++;
                printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", catName);
            }
            else {
                printf("%s은(는) 이미 냄비 근처입니다.\n", catName);
            }
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


//상태창
void printState(int soupCount, int intimacy, int mood, int cp) {
    const char* moodMessages[] = {                           
        
       "기분이 매우 나쁩니다.",
       "심심해합니다.",
       "식빵을 굽습니다.",
       "골골송을 부릅니다."
	};

    const char* messages[] = {
    "곁에 오는 것조차 싫어합니다.",
    "간식 자판기 취급입니다.",
    "그럭저럭 쓸 만한 집사입니다.",
    "훌륭한 집사로 인정 받고 있습니다.",
    "집사 껌딱지입니다."
    };

    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("CP: %d 포인트\n", cp); 
    printf("%s의 기분(0~3): %d\n", "쫀떡이", mood);            //수정    
    printf("%s\n", moodMessages[mood]);
    printf("집사와의 관계(0~4): %d\n", intimacy);
    printf("%s\n", messages[intimacy]);
    printf("==================================================\n");
}

void drawRoom(int catPos, int S, int T) {
    printf("\n");
    printf("##########\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == HOME_POS) printf("H");
        else if (i == BOWL_POS) printf("B");

        else if (S && i == 3) printf("S"); //스크래처
        else if (T && i == 5) printf("T"); //타워


        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == catPos) printf("C");
        else printf(" ");
    }
    printf("#\n##########\n");
}

void updateBadMood(int* mood, int intimacy, const char* catName) {
    printf("\n아무 이유 없이 기분이 나빠집니다. 고양이니까?\n");

    int badLimit = 6 - intimacy; //기분이 나빠지는 기준선
    printf("6 - 친밀도 = %d → 주사위 눈이 %d 이하면 기분이 나빠져요.\n", badLimit, badLimit);

    printf("주사위를 굴립니다. 또르르...\n");
    int dice = rollDice();
    printf("%d이(가) 나왔습니다.\n", dice);

    if (dice <= badLimit) {
        if (*mood > 0) {
            printf("%s의 기분이 나빠집니다: %d → %d\n", catName, *mood, *mood - 1);
            (*mood)--;
        }
        else {
            printf("기분은 이미 최악입니다...\n");
        }
    }
    else {
        printf("다행히 기분은 유지됐습니다.\n");
    }
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


void printIntro() {
    printf("====================================\n");
	printf("|       야옹이와 수프 v2.3       |\n");  //version 2.3
    printf("|      ***이동 업데이트     |\n"); 
    printf("|                                  |\n");
    printf("|      ( =ᵕᆺᵕ= )                    |\n");
    printf("|                                  |\n");
    printf("|     고양이와 친해져서 수프를      |\n");
    printf("|          만들어 보세요!          |\n");
    printf("====================================\n\n");
}