// Q3.c – Assignment 03 – Aidan, Darling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool	unsigned char
#define	false	(unsigned char) 0
#define true	(unsigned char) 1

#define MAX 100
#define initial 1
#define waiting 2
#define visited 3

int n;
int     front = 0;      // index of next element to remove
int     length = 0;     // number of elements currently in queue
int adj[MAX][MAX];
int state[MAX];
int queue[MAX];


bool isEmpty_queue (void)
// Returns true if queue is empty
{
    return length==0;
}

bool isFull_queue (void)
// Returns true if queue is full
{
    return length==n;
}//qfull()

bool enqueue (int p)
// Add value n to queue
{
    // First, check if even possible
    if (isFull_queue())    return false;
    // Can insert - new value gets placed at end.
    queue[(front+length) % MAX] = p;
    length++;
    return true;
}


int dequeue ()
// Remove first value from queue
{
    int p;
    // Check if there is anything to remove
    if (isEmpty_queue())   return false;
    // Front element is one to remove
    p = queue[front];
    front = (++front) % MAX;
    length--;
    return p;
}


// Used to create custome graphs 
void create_graph(){
    int count, max_edge, origin, destin;
    // Asks the user for number of vertices
    printf("Enter number of vertices : ");
    scanf("%d",&n);
    max_edge = n*(n-1);
    // Lets user define the directed edges
    for(count=1; count<=max_edge; count++){
        printf("Enter edge %d( -1 -1 to quit ) : ",count);
        scanf("%d %d",&origin,&destin);

        if((origin == -1) && (destin == -1)) break;

        if(origin>=n || destin>=n || origin<0 || destin<0){ 
            printf("Invalid edge!\n");
            count--; 
        }
        else{ 
            adj[origin][destin] = 1;
        }
    }
}

// Runs through all nodes to find mothernodes using Breadth First Traversal
void BF_Traversal(){
    int v;
    int a;
    int mothernode = 0;
    // Runs through all existing nodes
    for (int i = 0; i < n; i++){
        a = 1;
        // Sets all exisiting node to unvisited state
        for(v=0; v<n; v++) state[v] = initial;
        // Checks to see what can be visited from node
        BFS(i);
        // If after calling the function all vertices are all visited
        // Then it is a mothernode
        for(v=0; v<n; v++){
            if (state[v] != visited){
                a = 0;
            }
        }     
        if (a==1){
            printf("Is mothernode: %d\n", i);
            mothernode = 1;
        }
    }
    // If no mothernodes were found, then output
    if (mothernode == 0){
        printf("-1");
    }
}


void BFS(int v){
    int i;

    // Enqueue the current vertex being looked at
    enqueue(v);

    state[v] = waiting;
    // While the queue is not empty, dequeue current value at front of queue
    // And set it to visited
    while(!isEmpty_queue()){
        v = dequeue();
        state[v] = visited;
        // Run through all values that are greater then current vertex
        // If any of them can be visited from current vertex, enqueue them
        for(i=0; i<n; i++){
            if(adj[v][i] == 1 && state[i] == initial){
                enqueue(i);
                state[i] = waiting;
            } 
        }
    }
}


int main(){

    // Code to create graph and call function to search for mothernode
    n = 7;

    adj[1][3] = 1;
    adj[4][1] = 1;
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[6][4] = 1;
    adj[6][0] = 1;
    adj[5][2] = 1;
    adj[5][6] = 1;

    BF_Traversal();


}
