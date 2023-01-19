// Q1 – Assignment 01 – Aidan, Darling

#include <stdio.h>


struct node{
    struct node *pnextnode;
    struct node *pbacknode;
    int datavalue;
};


struct node *pnew_node (int d)
// Function creates a new node, and initializes the structure fields. Function
// returns pointer to the new node if everything worked, or it returns NULL
// because malloc() was unable to ge memory.
// Notice we have started taking some coding shortcuts here
{
	// Declaration of local node pointer, with initialization
	struct node	*pn = (struct node *) malloc (sizeof (struct node));

	// If we actually got memory, use it
	if (pn != NULL)	{
		// Now fill in structure. Notice the syntax. You can read this as
		// "assign value in d to datavalue field in structure pointed
		//  to by pn".
		pn->datavalue = d;
        pn->pbacknode = NULL;
		pn->pnextnode = NULL;	// guarantees that it has unmistakeable value
		}
	// Get here with pn pointing to a filled-in structure, or with pn equal
	// to NULL because malloc() failed. In either case, return pn.
	return pn;
}//pnew_node()

// Insert a new item of data at the front of the double linked list.
void insertFirst (int d, struct node **phead, struct node **pback){
	struct node	*pn = pnew_node (d);

	// Make sure node creation worked
	if (pn != NULL){
        // If there is nothing in the list, then assign phead and pback to the node
        if (*pback == NULL){
		    *pback = pn;
            *phead = pn;
        }
        // Else, assign current pheads back node to the new node and make the new node
        // Point to the next node held by phead and make phead now point to the new node
        else{
            (*phead)->pbacknode = pn;
            pn->pnextnode = *phead;
            *phead = pn;
        }   
    }
}

// Insert a new item of data at the end of the double linked list.
void insertPos(int d, struct node **phead, struct node **pback){
    struct node	*pn = pnew_node (d);

	// Make sure node creation worked
	if (pn != NULL){
        // If there is nothing in the list, then assign phead and pback to the node
        if (pback == NULL){
		    *pback = pn;
            *phead = pn;
        }
        // Else, assign current pback next node to the new node and make the new node
        // Point to the previous node held by pback and make pback now point to the new node
        else{
            (*pback)->pnextnode = pn;
            pn->pbacknode = *pback;
            *pback = pn;
        }   
    }
}


// Deletes the fist node in the doubly linked list
void deleteFirst(struct node **phead){
    // If the list is not empty, then deleate the first value
    if (phead != NULL){
        // Create a temp node to hold pointer to node after the one being deleated
        struct node	*pn = (*phead)->pnextnode;
        // Make the next node point to nul for pbacknode so it points to nothing
        pn->pbacknode = NULL;
        // Free the node held at phead and then reassign phaed to the new head
        free(phead);
        *phead = pn;
    }
}

void sortList(struct node **phead){
    // Variables used to run through loop used for switching order
    struct node	*ptempmain = *phead;
    int x,y;
    int going = 1;
    int change = 0;

    // Loop runs until no changes are made to the order of the queue
    while(going){
        // If the next value is greater, swap the two values and make it so that
        // The while loop does not break
        if(ptempmain->pnextnode->datavalue < ptempmain->datavalue){
            x = ptempmain->pnextnode->datavalue;
            y = ptempmain->datavalue;
            ptempmain->datavalue = x;
            ptempmain->pnextnode->datavalue = y;
            change = 1;
        } 
        // Checks to see if at the end if the list
        if (ptempmain->pnextnode->pnextnode == NULL){

            // If no changes have been made , leave the loop
            if (change == 0){
                going = 0;
            }
            // If changes have been made, restart the loop
            else{
                ptempmain = *phead;
                change = 0;
            }
        }
        // Go to the next position in list
        else{
            ptempmain = ptempmain->pnextnode;
        }

    }
}

// Samea as the inserFirst function, but made to work when called in another function
void insertFirstSpecial (int d, struct node ***phead, struct node ***pback){
	struct node	*pn = pnew_node (d);

	// Make sure node creation worked
	if (pn != NULL){
        // If there is nothing in the list, then assign phead and pback to the node
        if (**pback == NULL){
		    **pback = pn;
            **phead = pn;
        }
        // Else, assign current pheads back node to the new node and make the new node
        // Point to the next node held by phead and make phead now point to the new node
        else{
            (**phead)->pbacknode = pn;
            pn->pnextnode = **phead;
            **phead = pn;
        }   
    }
}

// Samea as the sortList function, but made to work when called in another function
void sortListSpecial(struct node ***phead){
    // Variables used to run through loop used for switching order
    struct node	*ptempmain = **phead;
    int x,y;
    int going = 1;
    int change = 0;

    // Loop runs until no changes are made to the order of the queue
    while(going){
        // If the next value is greater, swap the two values and make it so that
        // The while loop does not break
        if(ptempmain->pnextnode->datavalue < ptempmain->datavalue){
            x = ptempmain->pnextnode->datavalue;
            y = ptempmain->datavalue;
            ptempmain->datavalue = x;
            ptempmain->pnextnode->datavalue = y;
            change = 1;
        } 
        // Checks to see if at the end if the list
        if (ptempmain->pnextnode->pnextnode == NULL){

            // If no changes have been made , leave the loop
            if (change == 0){
                going = 0;
            }
            // If changes have been made, restart the loop
            else{
                ptempmain = **phead;
                change = 0;
            }
        }
        // Go to the next position in list
        else{
            ptempmain = ptempmain->pnextnode;
        }

    }
}

// Function used to create  a doubly linked list A
void createListA(struct node **phead, struct node **pback){
    insertFirstSpecial(50, &phead, &pback);
    insertFirstSpecial(20, &phead, &pback);
    insertFirstSpecial(10, &phead, &pback);
}

// Function used to create  a doubly linked list E
void createListE(struct node **phead, struct node **pback){
    insertFirstSpecial(36, &phead, &pback);
    insertFirstSpecial(25, &phead, &pback);
    insertFirstSpecial(24, &phead, &pback);
}


// Merges the doubly linked list D and E
void merge(struct node **phead1, struct node **phead2, struct node **phead3, struct node **pback3){
    
    struct node	*ptemp;		// temporary pointer used to traverse list

	// both lists need to be assigned to the new list. We will point ptemp at
	// the first node in the list D, save to new list, and if there is 
	// more list, move ptemp to point to the next node. We'll keep
	// doing this until there are no more nodes to look at. 
    // Afterwards, go through list E in the same manner
	ptemp = *phead1;
	while (ptemp != NULL)	{
        insertFirstSpecial(ptemp->datavalue, &phead3, &pback3);
        ptemp = ptemp->pnextnode;
	}

    ptemp = *phead2;
	while (ptemp != NULL)	{
        insertFirstSpecial(ptemp->datavalue, &phead3, &pback3); 
        ptemp = ptemp->pnextnode;
	}
    // After, sort the combined list
    sortListSpecial(&phead3);

}

void print_linked_list (struct node **phead)
// Routine prints data contents of linked list
{
	struct node	*ptemp;		// temporary pointer used to traverse list
	int			count;		// count how many printed on one line
	if (phead == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	// List has some real data to be printed. We will point ptemp at
	// the first node in the list, print the data, and if there is 
	// more list, move ptemp to point to the next node. We'll keep
	// doing this until there are no more nodes to look at.
	ptemp = *phead;
	count = 0;				// 0 on line so far
	while (ptemp != NULL)	{
		printf ("%5d", ptemp->datavalue);
		if (ptemp->pnextnode != NULL)	{
			printf ("->");
			count++;			// one more on the line
			// check if getting close to right edge - if so, move to start of
			// next line and reset count.
			if (count > 12)	{
				putchar ('\n');
				count = 0;
				}
		} else	{
			putchar ('\n');
			}
		ptemp = ptemp->pnextnode;
		}
	// all done
	return;
} // print_linked_list()

int main(){

    // Nodes used for the doubly linked lists called for the program
    struct node *phead1 = NULL;
    struct node *pback1 = NULL;

    struct node *phead2 = NULL;
    struct node *pback2 = NULL;

    struct node *phead3 = NULL;
    struct node *pback3 = NULL;

    // All the functions used and called to display required steps for the assignment
    printf("List A:\n");
    createListA(&phead1, &pback1);
    print_linked_list(&phead1);

    printf("List B:\n");
    insertFirst(5, &phead1, &pback1);
    print_linked_list(&phead1);

    printf("List C:\n");
    deleteFirst(&phead1);
    print_linked_list(&phead1);

    printf("List D before sorting:\n");
    insertPos(30, &phead1, &pback1);
    print_linked_list(&phead1);

    printf("List D after sorting:\n");
    sortList(&phead1);
    print_linked_list(&phead1);

    printf("List E:\n");
    createListE(&phead2, &pback2);
    print_linked_list(&phead2);

    printf("Merged list D and E sorted:\n");
    merge(&phead1,&phead2,&phead3,&pback3);
    print_linked_list(&phead3);
}

