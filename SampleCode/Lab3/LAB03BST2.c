// LAB03BST2.c – Lab 03 – Aidan, Darling

// LAB3_BST.C 
// 
// Code for ELEC278 Lab 3.  Some code has already been implemented.
// You will develop your own code - look for the comments.


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2022.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */




#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef long username;

#define	BST_FAIL	0		// return password when BST function fails
#define	BST_SUCCESS	1		// return password when BST function succeeds

// Node in tree has username and pointer to password associated with username.
// Also contains structural components - two pointers to left and
// right subtrees.
typedef struct Node	{
	username				username;
	char			    *password;
	struct Node		*leftChild, *rightChild;
} Node, pNode;

// Tree is basically pointer to top node in a tree.
typedef struct Tree {
	Node *root;
} Tree;

Node *initNode (username k, char *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)	{
		n->username = k;
		n->password = strdup(v);
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	return n;
}//initNode()


Tree *initTree(username k, char *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()


Node *find (username k, Node *root)
// Function locates node with username equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// username password sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->username == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every username in the right subtree is bigger than the username in the tree's
	// root, and every username in the left subtree is smaller than the username in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->username)
		// username sought is larger than current node username, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// username sought is smaller than current node username (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
		
}//find()



int insert(username k, char *v, Node *root)
// Function inserts a new node into the tree, with username k and password pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate username.
{
	int result = BST_FAIL;
	// this if statement can only be true with first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return BST_SUCCESS;
		}
	
	// already exists in tree ==> replace password
	if (root->username == k){
        root->password = v;
        result = 2;
    }
		
	else if (k < root->username) {
		// username less than username in root node - try to insert into left
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
	} else if (k > root->username) {			// test actually redundant
		// username is greater than this nodes username password, so password goes into right
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


Node* findParentHelper (username k, Node* root)
// Help find parent of node with username == k. Parameter root is node with
// at least one child (see findParent()).
{
	// Node used to return pointer to parent node of given child node
	Node *parent;
	// Checks to see if the child exisits for left and right branches,
	// And if the child exisits, is it the desired child
	if (root->leftChild != NULL && k == root->leftChild->username){
		return root;
	}
	else if (root->rightChild != NULL && k == root->rightChild->username){
		return root;
	}
	// Checks to see if the child exisits for left and right branches,
	// If the child exisits, if the value of the password is greater then the value of the current 
	// node, then go to the right node, else go to the left node
	if (root->leftChild != NULL && root->username > k){
		parent = findParentHelper(k, root->leftChild);
	}
	else if (root->rightChild != NULL && root->username < k){
		parent = findParentHelper(k, root->rightChild);
	}
	
	return parent;
}//findparenthelper()

Node *findParent(username k, Node *root)
// 
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	if (root == NULL)	return root;	
	// real root doesn't have parent so we make it parent of itself
	if (root->username == k)	return root;	
	// root has no children
	if ((root->leftChild == NULL) && (root->rightChild == NULL)) 
			return NULL;
	
	// Deal with cases where root has at least one child
	return findParentHelper(k, root);
}//findParent()


void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
	// Deletion has 3 cases - no subtrees, only left or right subtree, or both
	// left and right subtrees.
	Node *deleteNode = n;		// Save copy of pointer to node to delete.

	if (n->leftChild != NULL) {			// there is left child
		// If the right child is null for the node to deleted, determine 
		// Which branch of the parent points to the deleted node and replace the 
		// Pointer to the deleted node with the pointer to the leftChild of the deleted node
		if (n->rightChild == NULL){
            if (p->leftChild == deleteNode){
                p->leftChild = deleteNode->leftChild;
            }
            else{
                p->rightChild = deleteNode->leftChild;
            }
        }
		// If there are two nodes for the deleted node
		// Create a nodes to go thorugh the right child node to find the lowest value
		// In the right branch and replace the deleted node with that value,
		// It then recursivley calls itself and deletes the lowest value used to replace 
		// deleted node. 
		// If there is no lower node then the rightChild node of the deleted node, then
		// replace the values of the deleteNode with the rightChild node and then delete rightChild node
        else{
            if (deleteNode->rightChild->leftChild != NULL){
            	Node *par = deleteNode->rightChild;

				while (par->leftChild->leftChild != NULL){
					par = par->leftChild;
				}
				deleteNode->username = par->leftChild->username;
				deleteNode->password = par->leftChild->password;
				delete(par,par->leftChild);
            }
			else{
				deleteNode->username = deleteNode->rightChild->username;
				deleteNode->password = deleteNode->rightChild->password;
				delete(deleteNode,deleteNode->rightChild);
			}
        }

	} 
	// No need to check if the leftChild node is NULL, as if it was not,
	// This statment would not be checked
	else if (n->rightChild) {			// there is a right child

		// If there are two nodes for the deleted node
		// Create a nodes to go thorugh the right child node to find the lowest value
		// In the right branch and replace the deleted node with that value,
		// It then recursivley calls itself and deletes the lowest value used to replace 
		// deleted node. 
		// If there is no lower node then the rightChild node of the deleted node, then
		// replace the values of the deleteNode with the rightChild node and then delete rightChild node
		if (deleteNode->rightChild->leftChild != NULL){
            	Node *par = deleteNode->rightChild;

				while (par->leftChild->leftChild != NULL){
					par = par->leftChild;
				}
				deleteNode->username = par->leftChild->username;
				deleteNode->password = par->leftChild->password;
				delete(par,par->leftChild);
            }
			else{
				deleteNode->username = deleteNode->rightChild->username;
				deleteNode->password = deleteNode->rightChild->password;
				delete(deleteNode,deleteNode->rightChild);
			}
	} 
	// If there are no children, determine which node the parent points to and replace it with NULL
	else	{							// no children
		if (p->leftChild == deleteNode){
			p->leftChild = NULL;
		}
		else if (p->rightChild == deleteNode){
			p->rightChild = NULL;
		}
		free(deleteNode);
	}


}//delete()

int withdraw(username k, Node* root)
//	Delete the node with username k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);

	if (m != NULL)	{
		// create a copy of the node with the same username and password
		p = findParent(k,root);
		// can delete the node
		delete(p,m);
		return 1;
	}
	
	return 0;	
}//withdraw()


int main (){
	// Node coount incremented as nodes are added or deleted
	int nodeCount = 0;

	long		pUsername;
	char		*pPassword;
	FILE		*fp;
	Tree 		*t;

	// Get buffer to read password data file into.
	pPassword = (char *)malloc (256);
	// Checks if assigned memory was valid
	if (pPassword == NULL)	{
		fprintf (stderr, "ERROR: Cannot get memory for buffer\n");
		return -1;
	}
	// Opens the required file and checks if the file was able to be opened
	fp = fopen ("IDENTS.TXT", "r");
	if (fp == NULL)	{
		fprintf (stderr, "ERROR: Cannot open data file\n");
		return -1;
	}

	// Scans the first two values in the file and then attempts to create a BST
	fscanf(fp,"%ld", &pUsername);
	fscanf(fp, "%s", pPassword);
	if (t = initTree(pUsername, pPassword)){
		nodeCount++;
		// Loops through reading the two values needed for node until it reaches the end of the file
		while(fscanf(fp,"%ld", &pUsername)!=EOF){
			fscanf(fp, "%s", pPassword);
			// If the insert is valid and not replaceing the password for an already exisiting 
			// Usernam, then increment node count
			if (insert(pUsername, pPassword, t->root) == 1)  nodeCount++;
		}
	}

	// Displays number of nodes
	printf("BST NODES: %d\n", nodeCount);
	fclose (fp);


	
	// Opens the required file and checks if the file was able to be opened
	fp = fopen ("DELETES.TXT", "r");
	if (fp == NULL)	{
		fprintf (stderr, "ERROR: Cannot open data file\n");
		return -1;
	}
	// Loops through file and gets the username to delete from BST until it hits the end of the file
	while(fscanf(fp,"%ld\n", &pUsername)!=EOF){
		// If the value to be deleted exisits, then deincrement node count
		if (withdraw(pUsername, t->root)) nodeCount--;
	}

	// Displays number of nodes after deletion
	printf("BST NODES: %d\n", nodeCount);
	fclose (fp);

	// Opens the required file and checks if the file was able to be opened
	fp = fopen ("LOOKUPS.TXT", "r");
	if (fp == NULL)	{
		fprintf (stderr, "ERROR: Cannot open data file\n");
		return -1;
	}

	// Loops through file checking to see if the username exisits,
	// If it does, then outputs the corresponding password
	// Else it tells the user there is no password related to that username
	Node *pt;
	while(fscanf(fp,"%ld\n", &pUsername)!=EOF){
		if (find(pUsername, t->root)!=NULL){
			pt = find(pUsername, t->root);
			printf("ID %010ld PASSWORD %s\n", pt->username, pt->password);
		}
		else{
			printf("ID %010ld PASSWORD <NOT FOUND>\n", pUsername);
		}
	}
	// }

	fclose (fp);

}//main()