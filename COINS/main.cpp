#include<stdio.h>

using namespace std;

long long int dp[1000001];

long long int findMax (long long int n)
{
    long long int temp;
    if (n == 0)
    {
        return 0;
    }
    if ((n <= 1000000) && (dp[n] != 0))
    {
        return dp[n];
    }
    if ((n <= 1000000) && (dp[n] == 0))
    {
        temp = findMax(n/2) + findMax(n/3) + findMax(n/4);
        dp[n] = n > temp ? n : temp;
        return dp[n];
    }
    if (n > 1000000)
    {
        temp = findMax(n/2) + findMax(n/3) + findMax(n/4);
        return  (n > temp ? n : temp); 
    }
}

int main()
{
    long long int n;
    long long int ans;
    while (scanf ("%lli", &n) == 1)
    {
        ans = findMax (n);
        printf ("%lli \n", ans);
    }

    return 0;
}