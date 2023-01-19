// readnumsv6.c – Lab 01 – Aidan, Darling

#include <stdio.h>


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
	


int insert_data_at_front (int d)
// Insert a new item of data at the front of the linked list.
{
	struct node	*pn = pnew_node (d);

	// Make sure node creation worked
	if (pn == NULL)	return -1;

	// New node goes at the head of the list. The current head of the list
	// is pointed to by phead, so we make the new node point to the place
	// that phead points to and make phead point to the new node. So the
	// new node is at the beginning of the list and the previous list is
	// unchanged and pointed to by the new first node.
	pn->pnextnode = phead;
	phead = pn;
	// check if this was the very first node added - if so, we have to update
	// the end pointer as well
	if (pback == NULL)	pback = pn;
	return 0;
}//insert_data_at_front()


int insert_data_at_end (int d)
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
	

void main (void)
{
	char	ch;
	int		d;
	int		going;

	printf ("On each line, enter letter F or B, followed by a space and\n");
	printf ("a number. F means the number is placed at the front of the\n");
	printf ("list and B means the number is placed at the back,\n");
    printf ("and D means that number is deleted\n");
	printf ("To end your input, enter letter Q and any number.\n");

	going = 1;
	while (going)	{
		// very specific format !!
		scanf ("%c", &ch);			// get the letter in the first position
		scanf ("%d", &d);			// get the number after that
		while (getchar() != '\n');	// skip all up to and including newline
		printf ("Received %c %d\n", ch, d);
		switch (ch)	{
		case 'Q':
		case 'q':
			going = 0;		// Q or q means end of input
			break;
		case 'F':
		case 'f':
			insert_data_at_front (d);
			break;
		case 'B':
		case 'b':
			insert_data_at_end (d);
			break;
        case 'D':
        case 'd':
            delete_data (d);
            break;
		default:
			fprintf (stderr, "ERROR: Invalid command --%c--\n", ch);
			break;
			}//endswitch
		}//endwhile

	// User has entered all they wanted to
	print_linked_list ();

	printf ("====END====\n");
}//main()
