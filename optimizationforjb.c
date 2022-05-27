#include <stdio.h>
#include <math.h>
typedef double D;
const double ramda = 0.01;

double hpfunc(double x, int num)
{
    double xk = x, xnext, xans;
    int i = 0;
    for(i = 0; i <= num; i++)
    {
        printf("xk = %lf, num = %d\n", xk, i);
        //xnext = (D)(xk + ramda*((D)1-(D)((exp(((D)xk-(D)3)/(D)8))/(D)8))); //일차미분을 이용한 최적화
        xnext = (D)(xk + ((D)1-(D)((exp(((D)xk-(D)3)/(D)8))/(D)8))/((exp(((D)xk-(D)3)/(D)8))/(D)64)); // 이차미분을 이용한 최적화
        xk = xnext;
    }
    xans = xk;
    return xans;
}
int main(void)
{
    double xzero, ans;
    int num = 0;
    printf("insert xzero > ");
    scanf("%lf", &xzero);
    printf("repetition > ");
    scanf("%d", &num);
    ans = hpfunc(xzero, num);

    printf("answer : %lf\n", ans);
    return 0;
}