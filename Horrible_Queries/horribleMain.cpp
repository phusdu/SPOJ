#include<stdio.h>
#include<vector>

using namespace std;

typedef long long int lli;

lli seqLength; //sequence length ..
lli numQueries; //number of queries ..
lli flag; //flag determines the type of query.. 0 - updation query, 1 - print query
lli rangeStart, rangeEnd;
lli adder;

lli segmentTree [400001];
lli lazyTree[400001];

void buildSegmentTree ()
{
    for (int i = 0; i <= 4 * seqLength; i ++)
    {
        segmentTree [i] = 0;
    }
}

void buildLazyTree ()
{
    for (int i = 0; i <= 4 * seqLength; i ++)
    {
        lazyTree [i] = 0;
    }
}

void updateRange (lli currNodeStart, lli currNodeEnd, lli queryStart, lli queryEnd, lli nodeNum)
{
    lli leftChildNum, rightChildNum, mid;
    leftChildNum = nodeNum * 2 + 1;
    rightChildNum = nodeNum * 2 + 2;
    
    //checking if there is some previous update yet to be performed
    if (lazyTree [nodeNum] != 0)
    {
        segmentTree [nodeNum] += (lazyTree [nodeNum] * (currNodeEnd - currNodeStart + 1)); //performing update

        //updating lazy values..
        if (currNodeStart != currNodeEnd)//if children exists
        {
            lazyTree [leftChildNum] += lazyTree [nodeNum];
            lazyTree [rightChildNum] += lazyTree [nodeNum];
        }
        lazyTree [nodeNum] = 0;
    }

    //current node range falls fully within query range
    if ((currNodeStart >= queryStart) && (currNodeEnd <= queryEnd))
    {
        segmentTree [nodeNum] += (adder * (currNodeEnd - currNodeStart + 1));

        //setting lazy values for the children
        if (currNodeStart != currNodeEnd)//if children exists
        {
            lazyTree [leftChildNum] += adder;
            lazyTree [rightChildNum] += adder;
        }

    }
    else if ((currNodeEnd < queryStart) || (currNodeStart > queryEnd))
    {
        return ;
    }
    else
    {
        mid = (currNodeStart + currNodeEnd) / 2;
        updateRange (currNodeStart, mid, queryStart, queryEnd, leftChildNum);
        updateRange (mid + 1, currNodeEnd, queryStart, queryEnd, rightChildNum);

        segmentTree [nodeNum] = segmentTree [leftChildNum] + segmentTree [rightChildNum];
    }
}

lli getRangeSum (lli currNodeStart, lli currNodeEnd, lli queryStart, lli queryEnd, lli nodeNum)
{
    lli leftChildNum, rightChildNum, mid;
    leftChildNum = nodeNum * 2 + 1;
    rightChildNum = nodeNum * 2 + 2;

    //checking if there is some previous update yet to be performed
    if (lazyTree [nodeNum] != 0)
    {
        segmentTree [nodeNum] += (lazyTree [nodeNum] * (currNodeEnd - currNodeStart + 1)); //performing update

        //updating lazy values..
        if (currNodeStart != currNodeEnd)//if children exists
        {
            lazyTree [leftChildNum] += lazyTree [nodeNum];
            lazyTree [rightChildNum] += lazyTree [nodeNum];
        }
        lazyTree [nodeNum] = 0;
    }

    //current node range falls fully within query range
    if ((currNodeStart >= queryStart) && (currNodeEnd <= queryEnd))
    {
        return segmentTree [nodeNum];
    }
    else if ((currNodeEnd < queryStart) || (currNodeStart > queryEnd))
    {
        return 0;
    }
    else
    {
        mid = (currNodeStart + currNodeEnd) / 2;
        return (getRangeSum (currNodeStart, mid, queryStart, queryEnd, leftChildNum) + getRangeSum (mid + 1, currNodeEnd, queryStart, queryEnd, rightChildNum));
    }
}

int main ()
{
    int testCases;
    lli result;
    scanf ("%d", & testCases);

    while (testCases --)
    {
        scanf ("%lli", & seqLength);
        scanf ("%lli", & numQueries);

        buildSegmentTree ();
        buildLazyTree ();

        while (numQueries --)
        {
            scanf ("%lli", & flag);
            scanf ("%lli %lli", & rangeStart, & rangeEnd);

            rangeEnd --;
            rangeStart --;

            if (flag == 0)
            {
                scanf ("%lli", & adder);
                updateRange (0, seqLength - 1, rangeStart, rangeEnd, 0);
            }
            else
            {
                result = getRangeSum (0, seqLength - 1, rangeStart, rangeEnd, 0);
                printf ("%lli\n", result);
            }
        }
    }
}