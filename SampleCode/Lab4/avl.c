// LAB4_AVL.c – Lab 04 – Aidan, Darling

// AVL.C 
//
// Code for ELEC278 Lab 4.  Some code has already been implemented.
// You will develop your own code - look for the comments that say:
// "Your code goes here";
//


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


#include <stdio.h>
#include "bintree.h"
#include "avl.h"


void printTree(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	printf("{");		// Tree starts with an opening curly bracket
	// then value of root node
	printf("(%d)", root->key);
	//printf("(%d,%d)", root->key, *(int*) root->value);
						// need to cast void pointer actual data type
	printf(",");		// children come next

	// left child. If NULL it will just print two empty braces,
	// otherwise it prints whole left tree.
	if (root->leftChild) {
		printTree(root->leftChild);
	} else
		printf("{}");
	// separate left child from right child
	printf(",");
	// right child. If NULL it will just print two empty braces,
	// otherwise it prints whole right tree.
	if (root->rightChild) {
		printTree(root->rightChild);
	} else
		printf("{}");
	printf("}");	// Tree ends with closing curly bracket
}//printTree()

//=============================================================================
// ALTERNATE IMPLEMENTATION OF PRINTTREE - FOR YOUR REVIEW.
//    YOU MAY IGNORE THIS.

void printTree2(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	if (root == NULL)	{
		// printing an empty tree
		printf("{}");
	} else	{
		// printing non-empty tree
		printf("{");		// Tree starts with an opening curly bracket
		// then value of root node
		printf("(%ld,%d)", (long) root->key, *(int*) root->value);
							// need to cast void pointer actual data type
		printf(",");		// children come next

		// left child.
		printTree(root->leftChild);
		// separate left child from right child
		printf(",");
		// right child.
		printTree(root->rightChild);
		printf("}");	// Tree ends with closing curly bracket
		}
}//printTree2()
//=============================================================================

int maxint(int a, int b)	{ return (a>=b) ? a : b; }


void insertAVL (Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
	// Check for mistakes, including verification of tree type
	if ((t == NULL) || (t->tt != AVL))	return;
	// Check if tree empty - if so, insert first node
	if (t->root == NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	} else	{
		t->root = insertNodeAVL(k, v, t->root);
		}
	return;
}//insert()


Node* rotateRight(Node* root)
// Rotate to right.  Returns new root pointer.
{
	printf("Rotate Right\n");
//---Your code goes here
//---<SNIP>---

	Node *lc;
    lc = root->leftChild; 
    root->leftChild = lc->rightChild;
    lc->rightChild = root;
    root->height = calcHeight(root); 
    lc->height = calcHeight(lc); 

    //root = lc;
	return lc;

//---</SNIP>---
	//return root;
}//rotateRight()


Node* rotateLeft(Node* root)
// Rotate to left.  Returns new root pointer.
{
	printf("Rotate Left\n");
//---Your code goes here
//---<SNIP>---

	Node *rc; 
    rc = root->rightChild; 
    root->rightChild = rc->leftChild; 
    rc->leftChild = root; 
    root->height = calcHeight(root); 
    rc->height = calcHeight(rc); 

	return rc;
//---</SNIP>---
	//return root;
}//rotateLeft()


int getBalanceFactor(Node* root)
// Get balance factor - difference between left height and right height
{
	int	hr = -1, hl = -1;		// Default values
//---Your code goes here
//---<SNIP>---
 	if(root->leftChild != NULL) hl = root->leftChild->height;

    if(root->rightChild != NULL) hr = root->rightChild->height; 
//---</SNIP>---
	return hl - hr;
}//getBalanceFactor()


int calcHeight(Node* root)
// Calculate height of this node by adding 1 to maximum of left, right
// child height.
{
	int hrl = -1, hll = -1;		// Default values

//---Your code goes here
//---Code has to compute hrl - height of right subtree - and compute
//---hll - height of left subtree. In last line, 1 is added to the maximum
//---of hll and hrl and that value is returned.
//---<SNIP>---
	//int heightval;
    if (root != NULL){
        // Retruns the highest value
        hll = calcHeight(root->leftChild);
        hrl = calcHeight(root->rightChild); 
		root->height = maxint(hrl, hll) + 1;
    } 
	else return -1;
    //return heightval; 
//---</SNIP>---
	return maxint(hrl, hll) + 1;
}//calcHeight();


Node* rebalance(Node* root)
// Check balance factor to see if balancing required (bf > 1 or bf < -1).
// If balancing required, perform necessary rotations.
{
	int bf = getBalanceFactor(root);
//---Your code goes here
//---<SNIP>---

	//printf("\n%d - %d - ", root->key, bf);

	if (bf > 1 && getBalanceFactor(root->leftChild) == 1){
		printf("Node %d is unbalenced. Left of Left: ", root->key);
		root = rotateRight(root);
	} //return LL(node);

	 // Left Right Case 
    else if (bf > 1 && getBalanceFactor(root->leftChild) != 1){
		printf("Node %d is unbalenced. Left of Right: ", root->key);
		Node *lc = root->leftChild;
		root->leftChild = rotateLeft(lc);
		root = rotateRight(root);
	} //return LR(node);   


    // Right Right Case 
    else if (bf < -1 && getBalanceFactor(root->rightChild) == -1){
		printf("Node %d is unbalenced. Right of Right: ", root->key);
		root = rotateLeft(root);
	} //return RR(node);
   
    // Right Left Case 
    else if (bf < -1 && getBalanceFactor(root->rightChild) != -1){
		printf("Node %d is unbalenced. Right of Left: ", root->key);
		Node *rc = root->rightChild;
		root->rightChild = rotateRight(rc);
		root = rotateLeft(root);
	} //return RL(node);
//---</SNIP>---
	return root;
}//rebalance()


Node* insertNodeAVL(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
	if (root==NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		return n;
	}
	if (k < root->key) {
		root->leftChild = insertNodeAVL(k, v, root->leftChild);
		root->height = calcHeight(root);
	} 
	else if (k > root->key) {
		root->rightChild = insertNodeAVL(k, v, root->rightChild);
		root->height = calcHeight(root);
	}
	// Note - ignored equal case - should not occur.
	return rebalance(root);
}//insertNode()


void inOrderT(Node* root)
// In order traversal of tree displaying contents
{
	if (root) {
		inOrderT(root->leftChild);
		printf("%d(h=%d,bf=%d) - ", root->key, root->height,getBalanceFactor(root));
		inOrderT(root->rightChild);
		}
}//inOrderT()

//////

pNode findParent(Key k, pNode root)
// 
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	Node *root1 = root;
	if (root1 == NULL)	return root;	
	// real root doesn't have parent so we make it parent of itself
	if (root1->key == k)	return root;	
	// root has no children
	if ((root1->leftChild == NULL) && (root1->rightChild == NULL)) 
			return NULL;
	
	// Deal with cases where root has at least one child
	return findParentHelper(k, root1);
}//findParent()

Node* findParentHelper (Key k, Node* root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
	// Node used to return pointer to parent node of given child node
	Node *parent;
	// Checks to see if the child exisits for left and right branches,
	// And if the child exisits, is it the desired child
	if (root->leftChild != NULL && k == root->leftChild->key){
		return root;
	}
	else if (root->rightChild != NULL && k == root->rightChild->key){
		return root;
	}
	// Checks to see if the child exisits for left and right branches,
	// If the child exisits, if the value of the value is greater then the value of the current 
	// node, then go to the right node, else go to the left node
	if (root->leftChild != NULL && root->key > k){
		parent = findParentHelper(k, root->leftChild);
	}
	else if (root->rightChild != NULL && root->key < k){
		parent = findParentHelper(k, root->rightChild);
	}

	return parent;
}//findparenthelper()

void delete(Node *p, Node *n)
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
			// Calculate height and rebalence the node
			p->height = calcHeight(p);
			p = rebalance(p);

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
				deleteNode->key = par->leftChild->key;
				deleteNode->value = par->leftChild->value;
				delete(par,par->leftChild);
            }
			else{
				deleteNode->key = deleteNode->rightChild->key;
				deleteNode->value = deleteNode->rightChild->value;
				delete(deleteNode,deleteNode->rightChild);
			}
			// Calculate height and rebalence the node
			deleteNode->height = calcHeight(deleteNode);
			n = rebalance(deleteNode);
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
				deleteNode->key = par->leftChild->key;
				deleteNode->value = par->leftChild->value;
				delete(par,par->leftChild);
            }
			else{
				deleteNode->key = deleteNode->rightChild->key;
				deleteNode->value = deleteNode->rightChild->value;
				delete(deleteNode,deleteNode->rightChild);
			}
			// Calculate height and rebalence the node
			deleteNode->height = calcHeight(deleteNode);
			n = rebalance(deleteNode);
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
	// Rebalences the parent node after changes
	p->height = calcHeight(p);
	p = rebalance(p);


}//delete()

pNode withdraw(Key k, Node* root)
//	Delete the node with username k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);

	if (m != NULL)	{
		// create a copy of the node with the same username and password
		p = findParent(k,root);
		delete(p,m);
		// Calculate height and rebalence the root node
		root->height = calcHeight(root);
		root = rebalance(root);
	}
	return root;

}//withdraw()