// Q2.c – Assignment 03 – Aidan, Darling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    int key;
    int priority;
    int data;
    struct node *next;
}; /* node in the listed list */

struct hash {
    struct node *head; /* head of the listed list */
    int count;
}; /* hash table */


int M = 21;
int maxPrority = 0;
int inTable = 0;
struct hash hashTable[21];

struct node * createNode(int key, int data) {
    struct node *newnode;
    newnode = (struct node *) malloc(sizeof(struct node));
    newnode->key = key;
    newnode->priority = maxPrority;
    newnode->data = data;
    newnode->next = NULL;
return newnode;
}


// Searches through whole table to see if value associated to key exisits
int find(int key, int data){
    int result = 0;
    struct node *temp;
    for (int i = 0; i < M; i++){
        // If the modulus is empty, skip it to save time
        if (hashTable[i].count != 0){
            // Search through whole linked list, if the value is found retrun 1, else return 0
            temp = hashTable[i].head;
            // if found, replace data with new value and increase priority to max
            if (temp->key == key){
                temp->data = data;
                result = temp->priority;
                temp->priority = maxPrority;
                //result = 1;
            }
            else{
                while(temp->next != NULL){
                    temp = temp->next;
                    if (temp->key == key){
                        temp->data = data;
                        result = temp->priority;
                        temp->priority = maxPrority;
                        //result = 1;
                    }
                }
            }
            
        }
    }
    return result;
}

// Lowers the priority for all priorities values greater then the current keys prioritiey before being put to max priority
void lowerPriority(int key, int prio){
    struct node *temp;
    for (int i = 0; i < M; i++){
        // If the modulus is empty, skip it to save time
        if (hashTable[i].count != 0){
            // Checks through whole table to lower priotity of all nodes other then key
            temp = hashTable[i].head;
            if (temp->key != key && temp->priority > prio){
                temp->priority--;
            }
            while(temp->next !=NULL && temp->priority > prio){
                temp = temp->next;
                if (temp->key != key){
                    temp->priority--;
                }
            }
        }
    }
}


void delete_data(){

	// Creates a node to loop through current nodes
	struct node	*ptempmain;

    for (int i = 0; i < M; i++)
    {
         if (hashTable[i].count != 0){
            // Asigns pointer to phead node
            ptempmain = hashTable[i].head;

            // Create a temporary node to use for freeing memory of deleated nodes
            struct node *tempnode;

            // If the value that needs to be deleated is at the front of the list,
            // then a different deleating method is needed
            // For this one, it assigns the node to the tempnode
            // assigns the phead node to a new location, and frees the old node pointer
            if (hashTable[i].head->priority == 1){
                tempnode = hashTable[i].head;
                hashTable[i].head = hashTable[i].head->next;
                free(tempnode);
                hashTable[i].count--;
                return;
            }

            // Continues looping until the end of the node list is hit
            while(ptempmain->next != NULL){

                // Checks the next node to see if the value needs to be deleated
                if(ptempmain->next->priority == 1){
                    // If the next node is the last node, point the current node to NULL
                    // and free allocated memory, returns the function as no more 
                    // values to check
                    if (ptempmain->next->next == NULL){
                        tempnode = ptempmain->next;
                        ptempmain->next = NULL;        
                        free(tempnode);
                        hashTable[i].count--;
                        return;
                    }
                    // Else it replaces the pointer of the curent node to two nodes down
                    // and frees the allocated memory of the deleated node
                    else{
                        tempnode = ptempmain->next;
                        ptempmain->next = ptempmain->next->next;
                        free(tempnode);
                        hashTable[i].count--;
                        return;
                    }	
                }
                // If the next node does not have a value to deleate,
                // go to the next node
                else{
                    ptempmain = ptempmain->next;
                }
            }
        }
    }
}

void put(int key, int data) {
    // Gets the hash index for key
    int hashIndex = key % M;

    // Checks to see if the current key already exisits, and if so replace it with new value
    // Also lowers priority of all other exising nodes to keep proper priority
    int temp = find(key,data);
    if(temp!=0){
        lowerPriority(key, temp);
        return;
    }

    // If the table is full, delete the lowest priority value
    if (inTable == maxPrority){
        delete_data();
        inTable--;
    }

    struct node *newnode = createNode(key, data);
    /* head of list for the bucket with index "hashIndex" */
    if (!hashTable[hashIndex].head) {
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count = 1;
        inTable++;
        lowerPriority(key, 1);
        return;
    }
    newnode->next = (hashTable[hashIndex].head);
    /* update the head of the list and no of nodes in the current
    bucket*/
    hashTable[hashIndex].head = newnode;
    hashTable[hashIndex].count++;
    inTable++;
    lowerPriority(key, 1);
}


// Assigns to the global value the maximum ammount of items that can be held
void cache(int capacity){
    maxPrority = capacity;
    // Sets all the values in the array structures propwer base values
    for (int i = 0; i < M; i++)
    {
        hashTable[i].count = 0;
        hashTable[i].head = NULL;
    }
}

// retrives the value associated to a key
int get(int key){
    int hold;
    struct node *temp;
    for (int i = 0; i < M; i++){
        // If the modulus is empty, skip it to save time
        if (hashTable[i].count != 0){
            temp = hashTable[i].head;
            // If the key exists, increase the priority to max, lower all other priorities
            // And return the data value
            if (temp->key == key){
                hold = temp->priority;
                temp->priority = maxPrority;
                lowerPriority(key, hold);
                //delete_data();
                return temp->data;
            }
            else{
                while(temp->next !=NULL){
                    temp = temp->next;
                    if (temp->key == key){

                        hold = temp->priority;
                        temp->priority = maxPrority;
                        lowerPriority(key, hold);
                        //delete_data();
                        return temp->data;
                    }
                }
            } 
        }
    }
    // If the key could not be found, return -1
    return -1;
}


// Prints the whole 
void printTable(){
    struct node *temp;
    for (int i = 0; i < M; i++){
        if (hashTable[i].count != 0){
            temp = hashTable[i].head;
            printf("Modulus %d:", i);
            printf(" data %d", hashTable[i].head->data);
            printf(" priority %d", hashTable[i].head->priority);
            while(temp->next!=NULL){
                temp = temp->next;
                printf("- data %d", temp->data);
                printf(" priority %d", temp->priority);
            }
            printf("\n");
        }
    }
}

int main(){
    int hold;
    cache(2);

    put(1,10);
    printTable();
    printf("\n");

    put(2,20);
    printTable();
    printf("\n");

    hold = get(1);
    if (hold!=-1){
        printf("key 1 - %d\n", hold);
    }
    else {
        printf("key 1 not found\n");
    }
    printf("\n");

    put(3,30);
    printTable();
    printf("\n");

    hold = get(2);
    if (hold!=-1){
        printf("key 2 - %d\n", hold);
    }
    else {
        printf("key 2 not found(-1)\n");
    }
    printf("\n");

    put(4,40);
    printTable();
    printf("\n");


    hold = get(1);
    if (hold!=-1){
        printf("key 1 - %d\n", hold);
    }
    else {
        printf("key 1 not found(-1)\n");
    }
    printf("\n");


    hold = get(3);
    if (hold!=-1){
        printf("key 3 - %d\n", hold);
    }
    else {
        printf("key 3 not found(-1)\n");
    }
    printf("\n");


    hold = get(4);
    if (hold!=-1){
        printf("key 4 - %d\n", hold);
    }
    else {
        printf("key 4 not found(-1)\n");
    }
    printf("\n");

    
    put(5,50);
    printTable();


}