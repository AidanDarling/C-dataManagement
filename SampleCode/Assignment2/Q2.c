// Q2.c – Assignment 02 – Aidan, Darling

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

// Determines the height by comparing the height of the children nodes
int getHeight(struct Node *t) {
    int heightLeft, heightRight, heightval;
    if (t == NULL) return heightval = -1;
    else {
        // Retruns the highest value
        heightLeft = getHeight(t ->leftChild);
        heightRight = getHeight(t->rightChild); 
        heightval = 1 + ((heightLeft > heightRight)? heightLeft : heightRight);
    } 
    return heightval;
}

// Determines if the tree is balenced by comparing the height of the children
// If the children are within one level, then no issues
int getBalance(Node *tree) {
    int lh, rh; 
    if(tree == NULL) return(0);

    if(tree->leftChild == NULL) lh = -1;
    else lh = tree->leftChild->height;

    if(tree->rightChild == NULL) rh = -1;
    else rh = tree->rightChild->height; 
    
    return lh-rh; 
}



Node *rotateLeft(Node *p) {
    Node *rc; 
    rc = p->rightChild; 
    p->rightChild = rc->leftChild; 
    rc->leftChild = p; 
    p->height = getHeight(p); 
    rc->height = getHeight(rc); 
    return rc;
}

Node *rotateRight(Node *p) {
    Node *lc;
    lc = p->leftChild; 
    p->leftChild = lc->rightChild;
    lc->rightChild = p;
    p->height = getHeight(p); 
    lc->height = getHeight(lc); 
    return lc;
}

Node *RR(Node *p) {
    return rotateLeft(p);
}

Node *LL(Node *p) {
    return rotateRight(p); 
}

Node *LR(Node *p) {
    Node *lc = p->leftChild;
    p->leftChild = rotateLeft(lc); 
    return rotateRight(p);
}

Node *RL(Node *p) { 
    Node *rc = p->rightChild; 
    p->rightChild = rotateRight(rc); 
    return rotateLeft(p); 
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
    
    /* Else there is nothing to do as the key is already in the tree. */
    /* Get the balance factor to check whether this node became unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then // there are 4 cases
    // Left Left Case 
    if (balance > 1 && key < node->leftChild->key) return LL(node);
    // Right Right Case 
    if (balance < -1 && key > node->rightChild->key) return RR(node);
    // Left Right Case 
    if (balance > 1 && key > node->leftChild->key) return LR(node);   
    // Right Left Case 
    if (balance < -1 && key < node->rightChild->key) return RL(node);
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


// Takes two arrays and combines them into a third
void combineArray(int *array1[],int *array2[], int *array3[], int lenArray1, int lenArray2){
    int a1 = 0;
    int a2 = 0;
    int k = 0;
    int len1 = lenArray1;
    int len2 = lenArray2;
    // Compare values for array at current index
    // compares values at current index values for each array,
    // then puts the lower one into the third array
    while (a1 != len1 && a2 != len2){
        if (array1[a1] <= array2[a2]){
            array3[k++] = array1[a1++];
        }
        else{
            array3[k++] = array2[a2++];
        }
    }
    // If the second array is shorter then the first array, then put the 
    // remaining values in the first array into the third array
    if (a1 != len1 && a2 == len2){
        for (int m = a1; m < len1; m++){
            array3[k++] = array1[m];
        }
        
    }
    // same as above, but for the second array is longer
    if (a2 != len2 && a1 == len1){
        for (int n = a2; n < len2; n++){
            array3[k++] = array2[n];
        }    
    }
}


// Takes an array that is sorted from min to max and turns it into a BST
Node *arrayToBST(int *array[], int first, int last){
    if (first > last){
        return NULL;
    }
    // Sets the middle value in the array as the node
    // and the children nodes to the left and right of the current index in the array
    int mid = (first + last)/2;
    Node *root = createNode(array[mid]);
 
    root->leftChild =  arrayToBST(array, first, mid-1);
 
    root->rightChild = arrayToBST(array, mid+1, last);
    
    root->height = getHeight(root);
 
    return root;
}

// Takes two BST and combines them into a third BST that is balennced
Tree *Merge(Node *root1, Node *root2){

    Tree *t = malloc(sizeof(Tree));
    if (t != NULL){
        // Puts both arrays into min to max arrays
        int len = pow(2,root1->height + 1)-1;
        int *array1[len];
        int lenArray1 = 0;
        InOrder(root1, array1, &lenArray1);

        len = pow(2,root2->height + 1)-1;
        int *array2[len];
        int lenArray2 = 0;
        InOrder(root2, array2, &lenArray2);


        // Combines the two arrays into a third
        int *array3[(lenArray1+lenArray2-1)];
        combineArray(array1,array2,array3,lenArray1,lenArray2);

        // Creates a BST using the third array
        int lenArray3  = lenArray1+lenArray2;
        t->root = arrayToBST(array3, 0, lenArray3-1);
        return t;
    } 
    
}


// Print node if at proper height 
void printHeight(struct Node* root, int height){
    if (root == NULL){
        return;
    }
    // if at desired height, print value
    if (height == 0){
        printf("%d ", root->key);
    }
    // If still above deisred height, go downn the BST
    else if (height > 0) {
        printHeight(root->leftChild, height - 1);
        printHeight(root->rightChild, height - 1);
    }
}

// Breadth first traversal
void BreadthFirstTraversal(struct Node* root){
    // Gets the max height of the BST
    int h = getHeight(root);
    printf("%d ", root->key);
    // Runs through all values at the each height starting at the top
    for (int i = 1; i <= h; i++)
        printHeight(root, i);
}





int main (){

    // BST used
    Tree *t1;
    t1 = initTree(3);
    t1->root = insert(t1->root, 2);
    t1->root = insert(t1->root, 5);
    t1->root = insert(t1->root, 1);

    Tree *t2;
    t2 = initTree(4);
    t2->root = insert(t2->root, 1);
    t2->root = insert(t2->root, 7);
    t2->root = insert(t2->root, 2);
    t2->root = insert(t2->root, 9);


    Tree *t3;
    t3 = Merge(t1->root, t2->root);
    BreadthFirstTraversal(t3->root);



}//main()