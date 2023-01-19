// queueproblem.c – Lab 02 - Aidan, Darling

#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node	*pnextnode;
	int			datavalue;
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
		pn->pnextnode = NULL;	// guarantees that it has unmistakeable value
		}
	// Get here with pn pointing to a filled-in structure, or with pn equal
	// to NULL because malloc() failed. In either case, return pn.
	return pn;
}//pnew_node()


int insert_data_at_end (int d, struct node **phead, struct node **pback)
// Insert new item of data at end of linked list.
{
	struct node	*pn = pnew_node (d);

	// make sure node creation worked
	if (pn == NULL)	return -1;

	// New node goes at back of list. If the list is currently empty,
	// then both the head and back pointers need to be updated.
	// Calls the pointer to the main functions values to make changes to them
	if (*pback == NULL)	{
		*pback = pn;
		*phead = pn;
	} 
	else{
		// there are already nodes in the list. Add the new one after
		// the existing last one.

		// Calls the pointer to the main functions values to make changes to them
		(*pback)->pnextnode = pn;

		// make the back pointer point to the new one
		*pback = pn;
	}
	return;
}//insert_data_at_end()


void print_linked_list (struct node **phead)
// Routine prints data contents of linked list
{
	// Assigns the value pointed at by the function, in this case, the head
	// of the current linked list
	struct node	*ptemp = *phead;		// temporary pointer used to traverse list
	int			count;		// count how many printed on one line
	if (ptemp == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	// List has some real data to be printed. We will point ptemp at
	// the first node in the list, print the data, and if there is 
	// more list, move ptemp to point to the next node. We'll keep
	// doing this until there are no more nodes to look at.
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

	// Creates 4 heads and backs for the linked lists as local variables
	// Which makes it easier to call the function used for assinging the values 
	// Given by the user to the proper linked list as it 
    struct node	*phead1 = NULL;
    struct node *pback1 = NULL;

	struct node	*phead2 = NULL;
    struct node *pback2 = NULL;

	struct node	*phead3 = NULL;
    struct node *pback3 = NULL;

	struct node	*phead4 = NULL;
    struct node *pback4 = NULL;

	// Variables used to escape loop
	int leave = 0;
	// Variable used to hold user value
	int temp;
	// Variable used to keep track of how many variables to see if max hit
	int count= 0;
	// Value to determine which linked list to add user value to
	int modVal;
	while(!leave){
		// Gets value from user
		scanf("%d", &temp);

		// Checks to see if the espace conditons for the loop are met
		if (count == 400 || temp < 0){
			leave = 1;
		}
		else{
			// Increments the count and gets the result for modulus devision by 4 of user value
			count++;
			modVal = temp % 4;
			// Sends the user value to proper value based on modVal result
			switch (modVal){
				case 0:
					insert_data_at_end(temp,&phead1, &pback1);
					break;

				case 1:
					insert_data_at_end(temp,&phead2, &pback2);
					break;

				case 2:
					insert_data_at_end(temp,&phead3, &pback3);
					break;

				case 3:
					insert_data_at_end(temp,&phead4, &pback4);
					break;
			}
		}

	}

	// Outputs the 4 linked lists and tells the user which lists they are seeing
	printf("Linked list 1:\n");
	print_linked_list(&phead1);

	printf("Linked list 2:\n");
	print_linked_list(&phead2);

	printf("Linked list 3:\n");
	print_linked_list(&phead3);

	printf("Linked list 4:\n");
	print_linked_list(&phead4);  

}