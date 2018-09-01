#include<stdio.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int vertices;
vector <int> adjMatrix[100002];
vector <int> maxPathLength(100002,0);//stores the maximum path length among all chidren branches for a node
vector <int> max2PathLength(100002,0);//stores the second maximum path length among all chidren branches for a node
vector <bool> visited(100002,false);

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

void queryHandler()
{
    int startVertex, iterator1, pathLength, nqueries, queryVertex;
    scanf ("%d", &startVertex);
    
    int a = storePathLengths (startVertex);

    // printPathLengths();

    scanf ("%d", &nqueries);
    
    while (nqueries --)
    {
        scanf ("%d", &queryVertex);
        pathLength = max2PathLength [queryVertex] + maxPathLength [queryVertex];
        printf ("%d\n", pathLength);
    }

}

void addEdge (int start, int end)
{
    adjMatrix [start].push_back (end);
    adjMatrix [end].push_back (start);
}

int main()
{
    int iterator1, edgeStart, edgeEnd; /*VARIABLES*/

    /******INPUT*****/
    scanf ("%d", &vertices);
    for (iterator1 = 1; iterator1 < vertices; iterator1 ++)
    {
        scanf ("%d %d", &edgeStart, &edgeEnd);
        addEdge (edgeStart, edgeEnd);
    }

    if (vertices > 1)
        queryHandler();
    else
        printf ("0");

}