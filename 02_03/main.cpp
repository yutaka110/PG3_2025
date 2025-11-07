#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess);
void ShowResult(int roll, int userGuess);

int main(void) {
    srand((unsigned)time(NULL));

    int userGuess;
    printf("サイコロの出目が半(奇数)か丁(偶数)かを当ててください。\n");
    printf("半(奇数)=1, 丁(偶数)=0 を入力: ");
    scanf_s("%d", &userGuess);

    int roll = rand() % 6 + 1;
    DelayReveal(ShowResult, 3000, roll, userGuess);

    return 0;
}

//サイコロの出目を遅延表示する関数
void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess) {
    printf("サイコロを振っています");
    Sleep(delayMs);
    printf("\n");
    fn(roll, userGuess);
}

//サイコロの出目と予想を比較して結果表示する関数
void ShowResult(int roll, int userGuess) {
    printf("サイコロの出目は %d でした。\n", roll);

    int isOdd = roll % 2;
    if (isOdd == userGuess) {
        printf("正解です！\n");
    }
    else {
        printf("不正解です！\n");
    }
}
