#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getCharJump(char* pattern, int* charJump, int length) {
    int m = length, jumpInd = 1, minuswithm;
    char check;
    for(int i = length; i > 0; i--) {
        check = pattern[i]; // 지금 검사할 패턴의 문자
        jumpInd = (int)check-64; // 지금 검사할 패턴의 문자를 기록할 charJump의 인덱스
        if(charJump[jumpInd] == 0) {  // charJump에 처음 기록, 이미 기록되어 있다면 바꾸면 안됨, jump의 값을 제일 작게 할 것이기 때문에
            for(int j = length; j > 0; j--) {
                if(pattern[j] == check && j != length) { // pattern을 검사하는데, 검사 대상이 뒤에서 봤을 때 2번째로 등장하는 것이어야 함. -> jump의 값을 작게하기 위해
                    minuswithm = j; // Tj와 동일한 문자 중 가장 오른쪽에 있는 인덱스 기록
                    break;
                }
            }
            charJump[jumpInd] = m - minuswithm; // m-i 실행
        }
        else continue;
    }
    for(int i = 1; i <= 26; i++) {
        if(charJump[i] == 0) {
            charJump[i] = length;
        }
    }
}

void BMFunc(char* memo, char* pattern, int* charJump, int memolength, int patternlength) {
    int count = 0, checkInd = patternlength-1, patternInd = patternlength, jumpInd, jumpSize;
    char jumpc;
    while(checkInd < memolength) {
        for(int i = patternlength; i > 0; i--) {
            if(memo[checkInd] != pattern[i]) {
                printf("memo[checkInd] : %c, pattern[i] : %c\n", memo[checkInd], pattern[i]);
                jumpc = memo[checkInd];
                jumpInd = (int)jumpc - 64;
                if((int)jumpc < 65) jumpSize = patternlength;
                else jumpSize = charJump[jumpInd];
                printf("jumpc : %c, jumpInd : %d, jumpSize : %d\n", jumpc, jumpInd, jumpSize);
                checkInd += jumpSize;
                patternInd = patternlength;
                break;
            }
            else if(i == 1 && pattern[i] == memo[checkInd]) {
                count++;
                checkInd += patternlength;
            }
            else if(i != 1 && pattern[i] == memo[checkInd]) {
                checkInd--;
            }
        }
    }
    printf("count : %d\n", count);
}

int main()
{
    char pattern[100];
    printf("insert pattern : ");
    scanf("%s", pattern);
    int patternlength = strlen(pattern);
    memmove(pattern+1, pattern, sizeof(int)*patternlength+1);
    int* charJump = (int*)calloc(27, sizeof(int)); // the number of alphabet
    getCharJump(pattern, charJump, patternlength);
    for(int i = 1; i <= 26; i++) {
        printf("%d ", charJump[i]);
    }
    printf("\n");
    getchar();
    char memo[100];
    int memolength;
    printf("insert string : ");
    scanf("%[^\n]s", memo);
    memolength = strlen(memo);
    BMFunc(memo, pattern, charJump, memolength, patternlength);
    printf("%s\n", memo);
    free(charJump);
    return 0;
}
