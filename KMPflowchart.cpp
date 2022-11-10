#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;


int main(void) {
    char pattern[100];
    printf("Insert the term : ");
    scanf("%s", pattern);
    int length = strlen(pattern);
    vector<int> KMPflowchart(length + 1);
    memmove(pattern+1, pattern, sizeof(char)*length);
    KMPflowchart[1] = 0;
    KMPflowchart[2] = 1; // 1번째와 2번째 패턴 문자는 고정
    for(int k = 3; k <= length; k++) {
        if(pattern[k-1] == pattern[KMPflowchart[k-1]])    KMPflowchart[k] = KMPflowchart[k-1] + 1;
        else {
            int t = KMPflowchart[k-1];
            while(1) {
                int r = KMPflowchart[t];
                if(r == 0) {
                    KMPflowchart[k] = 1;
                    break;
                }
                else if(pattern[k-1] == pattern[r]) {
                    KMPflowchart[k] = r+1;
                    break;
                }
                else {
                    t = r;
                }
            }
        }
    }
    for(int i = 1; i <= length; i++) {
        printf(" %d ", KMPflowchart[i]);
    }
    return 0;
}
