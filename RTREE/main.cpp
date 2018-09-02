#include<stdio.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int vertices, edges;
vector <int> adjMatrix[1000010];
vector <int> child1PathLength(1000010,0);//stores the maximum path length among all chidren branches for a node
vector <int> child2PathLength(1000010,0);//stores the second maximum path length among all chidren branches for a node
vector <int> maxSubtreePathLength(1000010,0);
vector <int> maxPathLength(1000010,0);
vector <bool> visited(1000010,false);
vector <bool> visited2(1000010,false);

int findSubtreePathLength (int vertex)
{
    int temp;
    visited2 [vertex] = true;
    maxPathLength[vertex] = child1PathLength [vertex] + child2PathLength [vertex];
    maxSubtreePathLength [vertex] = maxPathLength [vertex];

    for (int iterator1 = 0; iterator1 < adjMatrix [vertex].size(); iterator1 ++)
    {
        if (!visited2[adjMatrix [vertex] [iterator1]])
        {
            temp = findSubtreePathLength (adjMatrix [vertex] [iterator1]);

            if (temp >= maxSubtreePathLength [vertex])
            {
                maxSubtreePathLength [vertex] = temp;
            }
        }
    }
    
    return maxSubtreePathLength [vertex];
}

int storePathLengths (int vertex) //usinf BFS to traverse through all nodes and store pathlengths
{
    int temp;
    visited [vertex] = true;

    for (int iterator1 = 0; iterator1 < adjMatrix [vertex].size(); iterator1 ++)
    {
        if (!visited[adjMatrix [vertex] [iterator1]])
        {
            temp = storePathLengths (adjMatrix [vertex] [iterator1]);
            temp ++;

            if (temp >= child1PathLength [vertex])
            {
                child2PathLength [vertex] = child1PathLength [vertex];
                child1PathLength [vertex] = temp;
            }
            else if (temp > child2PathLength [vertex])
            {
                child2PathLength [vertex] = temp;
            }
        }
    }
    
    return child1PathLength [vertex];
}

void queryHandler()
{
    int startVertex, iterator, nqueries, queryVertex;
    scanf ("%d", &startVertex);
    
    int a = storePathLengths (startVertex); // stores path lengths in child1 and child2
    int b = findSubtreePathLength (startVertex);

    scanf ("%d", &nqueries);
    while (nqueries --)
    {
        scanf ("%d", &queryVertex);
        printf ("%d\n", maxSubtreePathLength [queryVertex]);
    }
}

void addEdge (int start, int end)
{
    adjMatrix [start].push_back (end);
    adjMatrix [end].push_back (start);
}

int main()
{
    int iterator, edgeStart, edgeEnd; /*VARIABLES*/

    /******INPUT*****/
    scanf ("%d", &vertices);
    edges = vertices - 1;

    for (iterator = 1; iterator <= edges; iterator ++)
    {
        scanf ("%d %d", &edgeStart, &edgeEnd);
        addEdge (edgeStart, edgeEnd);
    }

    if (vertices > 1)
        queryHandler();
    else
        printf ("0");

}