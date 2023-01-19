// Q3 – Assignment 01 – Aidan, Darling

#include <stdio.h>
#include <stdlib.h>


// Handy manifests
#define	EXIT_OK		0
#define	EXIT_ERROR	-1


// Definition for what node in our linked list looks like 
struct node {
	struct node	*pnextnode;
	int			datavalue;
	};

// Global pointers - so they can be used by all functions. One points
// to the first element in the linked list, the other points to the last
// element in the linked list.
struct node	*phead = NULL;
struct node *pback = NULL;


// Notice that we have extracted a piece of code that was common to both
// the insert_data_at_front() and insert_data_at_end() routines in the
// previous program versions. The next function creates a new node and
// initializes the data and next pointer fields.

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
		pn->pnextnode = NULL;	// guarantees that it has unmistakeable value
		}
	// Get here with pn pointing to a filled-in structure, or with pn equal
	// to NULL because malloc() failed. In either case, return pn.
	return pn;
}//pnew_node()
	

int push (int d)
// Insert new item of data at end of linked list.
{
	struct node	*pn = pnew_node (d);

	// make sure node creation worked
	if (pn == NULL)	return -1;

	// New node goes at back of list. If the list is currently empty,
	// then both the head and back pointers need to be updated.
	if (pback == NULL)	{
		pback = pn;
		phead = pn;
	} else	{
		// there are already nodes in the list. Add the new one after
		// the existing last one.
		pback->pnextnode = pn;
		// make the back pointer point to the new one
		pback = pn;
		}
	return 0;
}//insert_data_at_end()



int delete_data(int d){

	// Creates a node to loop through current nodes
	struct node	*ptempmain;

	// Checks to see if empty nodes, if so, let the user know
    if (phead == NULL)	{
		printf ("<EMPTY LIST>\n");
		return 0;
	}

	// Asigns pointer to phead node
	ptempmain = phead;

	// Create a temporary node to use for freeing memory of deleated nodes
	struct node *tempnode;

	// If the value that needs to be deleated is at the front of the list,
	// then a different deleating method is needed
	// For this one, it assigns the node to the tempnode
	// assigns the phead node to a new location, and frees the old node pointer
	if (phead->datavalue == d){
		tempnode = phead;
		phead = phead->pnextnode;
		free(tempnode);

		return 0;
	}

	// Continues looping until the end of the node list is hit
	while(ptempmain->pnextnode != NULL){

		// Checks the next node to see if the value needs to be deleated
		if(ptempmain->pnextnode->datavalue == d){
			// If the next node is the last node, point the current node to NULL
			// and free allocated memory, returns the function as no more 
			// values to check
			if (ptempmain->pnextnode->pnextnode == NULL){
				tempnode = ptempmain->pnextnode->pnextnode;
				ptempmain->pnextnode = NULL;
				pback = ptempmain;
				free(tempnode);
				return 0;
			}
			// Else it replaces the pointer of the curent node to two nodes down
			// and frees the allocated memory of the deleated node
			else{
				tempnode = ptempmain->pnextnode;
				ptempmain->pnextnode = ptempmain->pnextnode->pnextnode;
				free(tempnode);
			}	
		}
		// If the next node does not have a value to deleate,
		// go to the next node
		else{
			ptempmain = ptempmain->pnextnode;
		}
	}
}

int sortQueue(int k){
    // Variables used to run through loop used for switching order
    struct node	*ptempmain;
    int x,y;
    int going = 1;

    // Loop runs until no changes are made to the order of the queue
    while(going){
        // Changes the loop to escapable, so that if no swaps are made, the loop breaks
        going = 0;
        // Assigns a node to phead
        ptempmain = phead;
        // Runs through the linked list until it goes to the position the user wants to change
        for (int i = 1; i < k; i++){
            // If the next value is greater, swap the two values and make it so that
            // The while loop does not break
            if(ptempmain->pnextnode->datavalue > ptempmain->datavalue){
                x = ptempmain->pnextnode->datavalue;
                y = ptempmain->datavalue;
                ptempmain->datavalue = x;
                ptempmain->pnextnode->datavalue = y;
                going = 1;
            } 
            // go to next position in queue
            ptempmain = ptempmain->pnextnode;

        }

    }
}


void print_linked_list (void)
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
	ptemp = phead;
	count = 0;				// 0 on line so far
	while (ptemp != NULL)	{
		printf ("%4d", ptemp->datavalue);
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
	

void main (void){
    // Variables used in main
	char	userChoice;
	int		userVar;
	int		going;
    int     total = 0;

	printf ("On each line, enter letter B or b, followed by a space and a number\n");
	printf ("B means the number is placed at the back of the queue,\n");
	printf ("To end your input, enter letter Q and any number.\n");


	going = 1;
	while (going)	{
		scanf ("%c", &userChoice);			// get the letter in the first position
		scanf ("%d", &userVar);			// get the number after that
		while (getchar() != '\n');	// skip all up to and including newline
		switch (userChoice)	{
		case 'Q':
		case 'q':
			going = 0;		// Q or q means end of input
			break;
		case 'B':
		case 'b':
            total++;
			push(userVar);  // B or b means back of queue
			break;
		default:
			fprintf (stderr, "ERROR: Invalid command --%c--\n", userChoice);
			break;
			}//endswitch
		}//endwhile

    // Asks the user unitl where would they like put in reverse order
    // And adds a quick check to make sure it is a valid input
    going = 1;
    while(going){
        printf("Please write up to what value you would like reverse sorted:\n");
        scanf("%d", &userVar);
        if (userVar > total || userVar < 0){
            printf("Not valid\n");
        }
        else{
            going = 0;
        }
    }

    // Sorts the queue and outputs it
    sortQueue(userVar);
    print_linked_list ();

	printf ("====END====\n");
}//main()
