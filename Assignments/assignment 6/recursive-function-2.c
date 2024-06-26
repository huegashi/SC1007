#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int* dp;

int top_down_dp(int n)
{
    //write your code here
    if (n<=2){
        dp[n]=n;
        return n;
    }

    if (dp[n-1]==-1){
        dp[n-1]=top_down_dp(n-1);
    }
    if (dp[n-2]==-1){
        dp[n-2]=top_down_dp(n-2);
    }
    if (dp[n-3]==-1){
        dp[n-3]=top_down_dp(n-3);
    }
    dp[n]=dp[n-1]+ 2*dp[n-2] - 3*dp[n-3];
    return dp[n];

}




int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    dp=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) dp[i] = -1;

    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));

}
