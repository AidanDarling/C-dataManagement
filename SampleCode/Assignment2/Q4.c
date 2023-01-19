// Q4.c – Assignment 02 – Aidan, Darling

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#define	BST_FAIL	0		// return password when BST function fails
#define	BST_SUCCESS	1		// return password when BST function succeeds

// Node in tree has key and pointer to password associated with key.
// Also contains structural components - two pointers to leftChildand
// rightChild subtrees.
typedef struct Node	{
	int				key;
	int			    height;
	struct Node		*leftChild, *rightChild;
} Node;//, pNode;

Node *createNode(int key){
    Node *n = malloc(sizeof(Node));

    n->key = key;
    n->height = 0;
    n->leftChild = NULL;
    n->rightChild = NULL;
    
    return n;
}

// Tree is basically pointer to top node in a tree.
typedef struct Tree {
	Node *root;
} Tree;

Tree *initTree(int k)
// Set up new tree. Allocates memory for Tree structure, then
// calls createNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = createNode(k);
	return t;
}//initTree()

int getHeight(struct Node *t) {
    int heightLeft, heightRight, heightval;
    if (t == NULL) return heightval = -1;
    else {
        heightLeft = getHeight(t ->leftChild);
        heightRight = getHeight(t->rightChild); 
        heightval = 1 + ((heightLeft > heightRight)? heightLeft : heightRight);
    } 
    return heightval;
}

int isBalanced(Node *tree) {
    int lh, rh; 
    if(tree == NULL) return(0);

    if(tree->leftChild == NULL) lh = -1;

    else lh = tree->leftChild->height;

    if(tree->rightChild == NULL) rh = -1;
    
    else rh = tree->rightChild->height; 
    
    if (abs(lh-rh)>1){
        return 1;
    }
    else {
        return 0;
    }
}




Node *insert(Node *node, int key) {

    if(node==NULL) {
        Node *temp; 
        temp = (Node *)malloc(sizeof(Node)); 
        temp->key = key; 
        temp->height = 0;
        temp->leftChild = temp->rightChild = NULL; 
        return temp;
    }

    if(key >(node->key)) {
        node->rightChild = insert(node->rightChild, key);
        node->height = getHeight(node);
    }
        
    else if(key < (node->key)) {
        node->leftChild = insert(node->leftChild, key); 
        node->height = getHeight(node);
    }
    
    return node;
}


// Inorder traversal of BST that saves values to an array
void InOrder(Node *root, int *array[], int *index){
    if (root !=NULL){
        InOrder(root->leftChild, array, index);
        array[(*index)] = root->key;
        (*index)++;
        InOrder(root->rightChild, array, index);
    }
}


Node *arrayToBST(int *array[], int first, int last){
    if (first > last){
        return NULL;
    }
    int mid = (first + last)/2;

    Node *root = createNode(array[mid]);
    root->leftChild =  arrayToBST(array, first, mid-1);
    root->rightChild = arrayToBST(array, mid+1, last);
    
    root->height = getHeight(root);
 
    return root;
}

Tree *Rotation(Node *root){

    Tree *t = malloc(sizeof(Tree));
    if (t != NULL){
        int len = pow(2,root->height + 1)-1;
        int *array[len];
        int lenArray = 0;
        InOrder(root, array, &lenArray);
        t->root = arrayToBST(array, 0, lenArray-1);
        return t;
    }   
}

// Prints
void printPreorder(struct Node* node){
    if (node == NULL) {
        return;
    }
    printf("%d ", node->key);
    printPreorder(node->leftChild);
    printPreorder(node->rightChild);
}

int main (){

    Tree *t;
    t = initTree(12);
    t->root = insert(t->root, 18);
    t->root = insert(t->root, 17);
    t->root = insert(t->root, 8);
    t->root = insert(t->root, 9);
    t->root = insert(t->root, 5);
    t->root = insert(t->root, 4);
    t->root = insert(t->root, 2);

    // CHecks to see if the given tree is an AVL,
    // if it not, then balence the BST into an AVL
    while(isBalanced(t->root)){
        t = Rotation(t->root);
    }
    printPreorder(t->root);
}//main()