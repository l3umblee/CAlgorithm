#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFail(char* pattern, int* fail, int length) {
    fail[1] = 0;    fail[2] = 1;
    for(int k = 3; k <= length; k++) {
        if(pattern[k-1] == pattern[fail[k-1]]) fail[k] = fail[k-1] + 1;
        else {
            int t = fail[k-1];
            while(1) {
                int r = fail[t];
                if(r == 0) {
                    fail[k] = 1;
                    break;
                }
                else if(pattern[k-1] == pattern[r]) {
                    fail[k] = r + 1;
                    break;
                }
                else {
                    t = r;
                }
            }
        }
    }
}
// length is the length of pattern
void searchPattern(char* memo, char* pattern, int* fail, int length) {
    int failInd, patternInd = 1, count = 0;
    for(int i = 0; i < strlen(memo); i++) {
        printf("-------------------------------------------\n");
        printf("current memo check : %c \n", memo[i]);
        printf("current pattern check :  %c\n", pattern[patternInd]);
        printf("current patter ind : %d\n", patternInd);
        printf("-------------------------------------------\n");
        if(memo[i] == pattern[patternInd]) {
            patternInd++;
            if(patternInd == length+1) {
                patternInd = 1;
                count++;
            }
            continue;
        } // if the character of memo is same with the character of pattern -> patternInd++, get next character(continue;)
        else {
            failInd = fail[patternInd];
            if(fail[failInd] == 0 || fail[failInd] == -1) {
                patternInd = 1;
            }
            else {
                patternInd = fail[failInd];
            }
            continue;
        } // if the character of memo is not same with the character of pattern
    }
    printf("count : %d", count);
}

int main()
{
    char pattern[100];
    printf("Insert pattern : ");
    scanf("%s", pattern);
    int length = strlen(pattern);
    int* fail = (int*)malloc(sizeof(int)*(length+1));
    fail[0] = -1;
    memmove(pattern+1, pattern, length);
    getFail(pattern, fail, length);
    
    char memo[100];
    printf("Insert the sentence : ");
    scanf("%s", memo);
    
    searchPattern(memo, pattern, fail, length);
    
    free(fail);
    return 0;
}
