//using tabular approach.
#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;

long long int dp [5010]; //dp[i] stores the value of number of decodes for encodedString[0...i]
char encodedString[5010];

long long int calcDecodes (int strLength)
{
    dp[0] = 1;
    int i, num;

    for (i = 1; i < strLength; i ++)
    {
        if (encodedString [i] != '0')
        {
            dp [i] = dp [i - 1];
        }
        else
        {
            dp [i] = 0;
        }

        num = (encodedString [i] - '0') + ((encodedString [i - 1] - '0') * 10); // number formed by last 2 digits
        if (num > 9 && num < 27)
        {
            if (i == 1)
            {
                dp [i] += 1;
            }
            else
            {
                dp [i] += dp [i - 2];
            }
        }

    }

    return dp [strLength - 1];
}

int main()
{
    long long int numDecodes;
    int i, strLength;

    scanf("%s", encodedString);    

    while (encodedString[0] != '0')
    {
        strLength = strlen (encodedString);
        for (i = 0; i < strLength; i ++)
        {
            dp [i] = 0;
        }

        numDecodes = calcDecodes (strLength);
        printf("%lli\n", numDecodes);

        scanf("%s", encodedString);
    }

    return 0;
}