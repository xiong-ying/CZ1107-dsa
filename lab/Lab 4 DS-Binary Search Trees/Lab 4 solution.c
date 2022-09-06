//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);

int isBST2(BTNode *node);
int isBSTX(BTNode *node, BTNode* l, BTNode* r);

BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
			//printf("Insert successful.\n");
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);
	printf("\n");

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// write your code here
    if (*node == NULL)
    {
        *node = malloc(sizeof(BTNode));
        (*node)->item = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }

	if ((*node)->item == value){
        printf("Duplicate!\n");
        return;
	}
	else if ( value < (*node)->item ){
        insertBSTNode(&((*node)->left), value);
	}
	else {
        insertBSTNode(&((*node)->right), value);
	}

    /*
	if (*node == NULL){
        int size;
        size = malloc(size of(value));
        *node->item = value;
        *node->left = NULL;
        *node->right = NULL;
        return;
	}

    if (value < node->item){
        insertBSTNode(*node->left);
    }
    else if (value > node->item){
        insertBSTNode(*node->right);
    }
    else {
        printf("Cannot have same value");
        return;
    }
    */

}

//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// write your code here
	if (node==NULL) return;
	printBSTInOrder(node->left);
	printf("%d ", node->item);
	printBSTInOrder(node->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	// write your code here
    if (node == NULL) return 1;

    if ( (node->item) <= min || (node->item) >= max)
        return 0;

    return isBST(node->left, min, node->item) && isBST(node->right, node->item, max);

	/*
    if (node == NULL){
        return 1;
    }

    if ( min < (node->item) -> max){
        isBST(node->left, min, max);
        isBST(node->right, min, max);
    }
    else{
        return 0;
    }

    return 1;
    */

}

// Another method to check if it is BST
int isBST2(BTNode *node)
{
    if (node == NULL) return 1;

    return isBSTX(node, NULL, NULL);
}

int isBSTX(BTNode *node, BTNode* l, BTNode* r)
{
    if (node == NULL) return 1;

    if (l!=NULL && node->item <= l->item)
        return 0;
    if (r!=NULL && node->item >= r->item)
        return 0;

    return isBSTX(node->left, l, node) && isBSTX(node-right, node, r);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
    BTNode *p;

    if(node == NULL)
        return NULL;

    if((node->item) > value)
        node->left = removeBSTNode(node->left, value);
    else if (node->item < value)
        node->right = removeBSTNode(node->right,value);
    else //this is the node to be removed
    {
        //To modify the node - begin

        // case 1: node has two children
        if(node->left!=NULL && node->right !=NULL)
        {
            p=findMin(node->right);
            node->item = p->item;
            node->right = removeBSTNode(node->right, p->item);
        }
        else{ //case 2: x has no child or one child
            p = node;

            if (node->left != NULL)
                node=node->left;
            else
                node=node->right;

            free(p);
        }

        //To modify the node - end
    }

    return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
	if(p->left != NULL)
        return findMin(p->left);
	else
        return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
