// Q2.c – Assingment 01 – Aidan, Darling

#include <stdio.h>

// Definition of stack node - this version implements stack of integers
typedef struct _sn {
	struct _sn	*next;
	char			nodval;
} StkNode;

#define	SZSTKNODE	(sizeof(struct _sn))

// This implementation has only one stack
StkNode		*head = NULL;


char push (char n)
// Top of stack is front of linked list.  Create node to hold data and
// place it at front of list. Returns 0 if no node created; 1 for success.
{
	StkNode *p = (StkNode *)malloc(SZSTKNODE);
	if (p == NULL)	return 0;
	p->nodval = n;
	p->next = head;
	head = p;
	return  1;
}//push()


char  pop (char *pvalue)
// Top of stack is front of linked list. Check if list empty; if not,
// remove first node on list and copy value to supplied location.
{
	int	rslt = 0;
	if (pvalue != NULL)	{
		StkNode *p = head;
		if (p != NULL)	{
			head = p->next;
			*pvalue = p->nodval;
			free (p);
			rslt = 1;
			}//endif stack not empty
		}//endif result location available
	return rslt;
}// pop()
        

// Recurisive function used to run through the linked list
// Recusion is as there can be mmultiple closed type brackets before
// Running into an open bracket.
int balancedEquation(char x){

    // temp variable for holding popped value
    char var;
    // Saves popped value to variable
    pop(&var);

    // If the popped value is a closing bracket, then recursivly run the code
    if (var == '}' || var == ']' || var == ')'){
        balancedEquation(var);
    }
    // If the bracket is an opening bracket, check the value held by the recusion
    // If it is the relevent closing bracket, then return 1 as it balanced
    else if (var == '{' && x == '}'){
        return 1;
    }
    else if (var == '[' && x == ']'){
        return 1;
    }
    else if (var == '(' && x == ')'){
        return 1;
    }
    // If it is not balanced, then return 0
    else{
        return 0;
    }
}



void print_linked_list (void)
// Routine prints data contents of linked list
{
	StkNode	*ptemp;		// temporary pointer used to traverse list
	int			count;		// count how many printed on one line
	if (head == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	// List has some real data to be printed. We will point ptemp at
	// the first node in the list, print the data, and if there is 
	// more list, move ptemp to point to the next node. We'll keep
	// doing this until there are no more nodes to look at.
	ptemp = head;
	count = 0;				// 0 on line so far
	while (ptemp != NULL)	{
		printf ("%c", ptemp->nodval);
		if (ptemp->nodval != NULL)	{
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
		ptemp = ptemp->next;
		}
	// all done
	return;
} // print_linked_list()


int main (void)
{

    // Local variables used
    char y = NULL;
	char userVar;

    // Loop to run through all the values given by the user
    // All values are pushed to the link list stack
	printf("Please put open and closed brackets that you want to determine if they are balanced\n");
	printf("Ex: {[]}() is balanced, ({)} is not balanced\n");
    int leave = 0;
    while(!leave){
        scanf("%c", &userVar);
        if (userVar =='\n'){
            leave = 1;
        }
        else{
            push(userVar);
        }
    }

    // Checks to see if the stack is balanced,
    // If it is, outputs it to the user
    // If not, outputs it to the user
    if (balancedEquation(y) == 1){
        printf("Balanced\n");
    }
    else{
        printf("Not balanced\n");
    }

}