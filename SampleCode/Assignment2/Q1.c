// Q1.c – Assignment 02 – Aidan, Darling



#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define	BST_FAIL	0		// return value when BST function fails
#define	BST_SUCCESS	1		// return value when BST function succeeds

// Node in tree has key and pointer to value associated with key.
// Also contains structural components - two pointers to left and
// right subtrees.
typedef struct Node	{
	int				key;
	char			value;
	struct Node		*leftChild, *rightChild;
} Node, pNode;

typedef struct LNode{
    char key;
    struct LNode *pNextNode;
} LNode;

struct LNode	*phead = NULL;
struct LNode 	*pback = NULL;

// Tree is basically pointer to top node in a tree.
typedef struct Tree {
	Node *root;
} Tree;

Node *initNode (int k, char v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	return n;
}//initNode()

struct LNode *pnew_node (int d)
// Function creates a new node, and initializes the structure fields. Function
// returns pointer to the new node if everything worked, or it returns NULL
// because malloc() was unable to ge memory.
// Notice we have started taking some coding shortcuts here
{
	// Declaration of local node pointer, with initialization
	struct LNode	*pn = (struct LNode *) malloc (sizeof (struct LNode));

	// If we actually got memory, use it
	if (pn != NULL)	{
		// Now fill in structure. Notice the syntax. You can read this as
		// "assign value in d to datavalue field in structure pointed
		//  to by pn".
		pn->key = d;
		pn->pNextNode = NULL;	// guarantees that it has unmistakeable value
		}
	// Get here with pn pointing to a filled-in structure, or with pn equal
	// to NULL because malloc() failed. In either case, return pn.
	return pn;
}//pnew_node()
	

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
		pback->pNextNode = pn;
		// make the back pointer point to the new one
		pback = pn;
		}
	return 0;
}//insert_data_at_end()

Tree *initTree(int k, char v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()


Node *find (int k, Node *root)
// Function locates node with key equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// key sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// key sought is smaller than current node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
		
}//find()



int insert(int k, char v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
	int result = BST_FAIL;
	// this if statement can only be true with first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return BST_SUCCESS;
		}
	
	// already exists in tree ==> replace value
	if (root->key == k){
        root->value = v;
        result = 2;
    }
		
	else if (k < root->key) {
		// key less than key in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = BST_SUCCESS;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node*n = initNode(k,v);
			root->rightChild = n;
			result = BST_SUCCESS;
			}
		}
	return result;	
}//insert()

void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically knows the types in the tree node
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%d,%c),", root->key, root->value);
	// printf("(%ld,%d),", root->key, *(int*)root->value);
	
	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)	printTree(root->leftChild);
	else							printf("{}");
	// Marker between left and right subtrees		
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)	printTree(root->rightChild);
	else							printf("{}");
	// Close display of this tree with closing curly bracket	
	printf("}");
}//printTree()

void print_linked_list (void)
// Routine prints data contents of linked list
{
	struct LNode	*ptemp;		// temporary pointer used to traverse list
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
		printf ("%c", ptemp->key);
		if (ptemp->pNextNode != NULL)	{
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
		ptemp = ptemp->pNextNode;
		}
	// all done
	return;
} // print_linked_list()

// Print tree values based on postorder traversal. Function gets pointer to
// node, then prints left subtree, right subtree, node value.
void create_postorder (Node *pn){
	// If we were passed NULL, we have nothing to do
	if (pn == NULL)	return 0;
	create_postorder(pn->leftChild);
	create_postorder (pn->rightChild);
	insert_data_at_end(pn->value);
}//print_postorder()


int main (){

	// char		*pvalue;
	Tree 		*t;
    t = initTree(7, 'A');

    insert(4,'B', t->root);
	insert(9,'C', t->root);

	insert(2,'D', t->root);
	insert(6,'E', t->root);
	insert(8,'F', t->root);
	insert(11,'G', t->root);

	insert(1,'H', t->root);
	insert(3,'I', t->root);
	insert(5,'J', t->root);
	insert(10,'K', t->root);

	create_postorder(t->root);
	print_linked_list();

}//main()