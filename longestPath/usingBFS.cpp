//using BFS approach to find longest path in a tree..
#include<bits/stdc++.h>
#include<stdio.h>
#include<vector>

using namespace std;

int vertices;
vector <int> adjMatrix[10002];
vector <bool> visited1(10002,false);
vector <bool> visited2(10002,false);
int level[10002];
int queue1 [10002];
int front1 = 0, back1 = -1;
int queue2 [10002];
int front2 = 0, back2 = -1;

void enqueue1(int data)
{
    queue1[++ back1] = data;
}

int dequeue1()
{
    return (queue1 [front1 ++]);
}

void enqueue2(int data)
{
    queue2[++ back2] = data;
}

int dequeue2()
{
    return (queue2 [front2 ++]);
}

int updatedBFS1(int start)
{
    int adjacent, vertex;
    enqueue1 (start);
    while (back1 + 1 != front1)
    {
        vertex = dequeue1 ();
        visited1 [vertex] = true;
        for (adjacent = 0; adjacent < adjMatrix [vertex].size (); adjacent ++)
        {
            if (! visited1 [adjMatrix [vertex] [adjacent]])
            {
                enqueue1 (adjMatrix [vertex] [adjacent]);
            }
        }
    }

    return vertex;
}

void updatedBFS2 (int start)
{
    int adjacent, vertex;
    enqueue2 (start);
    level [start] = 0;
    while (back2 + 1 != front2)
    {
        vertex = dequeue2 ();
        visited2 [vertex] = true;
        for (adjacent = 0; adjacent < adjMatrix [vertex].size (); adjacent ++)
        {
            if (! visited2 [adjMatrix [vertex] [adjacent]])
            {
                level [adjMatrix [vertex] [adjacent]] = level [vertex] + 1;
                enqueue2 (adjMatrix [vertex] [adjacent]);
            }
        }
    }
}

int findLongestPath()
{
    int startVertex = 1, newStartVertex, maxLevel = 0;
    newStartVertex = updatedBFS1(startVertex);

    // printf ("new start vertex :  %d",newStartVertex);
    updatedBFS2(newStartVertex);

    for (startVertex = 1; startVertex <= vertices; startVertex ++)
    {
        if (level [startVertex] > maxLevel)
        {
            maxLevel = level [startVertex];
        }
    }

    return maxLevel;
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