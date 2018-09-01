//using dfs approach to find the longest path in a tree
#include<stdio.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int vertices;
vector <int> adjMatrix[10002];
vector <int> maxPathLength(10002,0);//stores the maximum path length among all chidren branches for a node
vector <int> max2PathLength(10002,0);//stores the second maximum path length among all chidren branches for a node
vector <bool> visited(10002,false);

int storePathLengths (int vertex)
{
    int temp;
    visited [vertex] = true;

    for (int iterator1 = 0; iterator1 < adjMatrix [vertex].size(); iterator1 ++)
    {
        if (!visited[adjMatrix [vertex] [iterator1]])
        {
            temp = storePathLengths (adjMatrix [vertex] [iterator1]);
            temp ++;

            if (temp >= maxPathLength [vertex])
            {
                max2PathLength [vertex] = maxPathLength [vertex];
                maxPathLength [vertex] = temp;
            }
            else if (temp > max2PathLength [vertex])
            {
                max2PathLength [vertex] = temp;
            }
        }
    }
    
    return maxPathLength [vertex];
    
}

// void printPathLengths()
// {
//     int i = 1;
//     for (i = 1; i <= vertices; i ++)
//     {
//         printf ("The path length at node %d is %d with max1 = %d and max2 = %d\n",i,(max2PathLength[i] + maxPathLength[i]),maxPathLength[i],max2PathLength[i]);
//     }
// }

int findLongestPath()
{
    int startVertex = 1, iterator1, pathLength, longestPathLength = 0;
    
    int a = storePathLengths (startVertex);

    // printPathLengths();
    
    for (iterator1 = 1; iterator1 <= vertices; iterator1 ++)
    {
        pathLength = max2PathLength [iterator1] + maxPathLength [iterator1];
        if (pathLength > longestPathLength)
        {
            longestPathLength = pathLength;
        }
    }

    return longestPathLength;

}

void addEdge (int start, int end)
{
    adjMatrix [start].push_back (end);
    adjMatrix [end].push_back (start);
}

int main()
{
    int iterator1, edgeStart, edgeEnd, longestPath = 0; /*VARIABLES*/

    /******INPUT*****/
    scanf ("%d", &vertices);
    for (iterator1 = 1; iterator1 < vertices; iterator1 ++)
    {
        scanf ("%d %d", &edgeStart, &edgeEnd);
        addEdge (edgeStart, edgeEnd);
    }

    if (vertices > 1)
        longestPath = findLongestPath();

    printf ("%d", longestPath);

}