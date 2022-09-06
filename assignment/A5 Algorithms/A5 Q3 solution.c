#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");

    printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");

    printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
    // STEP 1: Initialization

    // reverse prefix char
    char RevPrefix[SIZE];
    int begin, end, count = 0;

    // while loop
    char c;
    int i = 0;

    BTNode* Tmp;

    // Tmp Stack
    Stack s;
    s.head=NULL;
    s.size=0;

    //calculate number
    int tmpNum=-1;
    char n;
    int power=0;
    int tmpPower=0;
    int h = 0;


    /* STEP 2: Reverse Prefix char */

    // Calculating string length
    while (prefix[count] != '\0')
        count++;
    end = count - 1;

    // Reverse string
    for (begin = 0; begin < count; begin++)
    {
        RevPrefix[begin] = prefix[end];
        end--;
    }
    RevPrefix[begin] = '\0';

    //printf("RevPrefix is %s\n", RevPrefix);


    // STEP 3: use while loop to go through prefix
    while (RevPrefix[i] != '\0')
    {
        c = RevPrefix[i];

        switch(c)
        {
        case ' ':
            break;
        case '+':
        case '-':
        case '*':
        case '/':

            //printf("It's a operator.\n");
            //printf("create a btnode, root is operator, left node pop from s, right node pop from s, push back to s. \n");

            Tmp = malloc(sizeof(BTNode));
            Tmp->item = (int)c;
            Tmp->left = s.head->item;
            pop(&s);
            Tmp->right = s.head->item;
            pop(&s);

            push(&s, Tmp);

            break;
        default:
            //printf("It's a number.\n");
            c = c - '0';
            //printf("in default case, c is %d.\n", c);


            if ( tmpNum == -1 ){
                tmpNum = c;
            }
            else{
                h = c;
                power ++;

                tmpPower = power;
                while (tmpPower != 0) {
                    //printf("h = %d * 10.\n", h);
                    h = h*10;
                    //printf("h = %d.\n", h);

                    tmpPower --;
                }
                tmpNum = tmpNum+h;

                //printf("TmpNum is %d.\n", tmpNum);
                }

            // If next char is operator or end, just end here
            if (RevPrefix[i+1]==' ')
            {
                //printf("Create a btnode, push btnode %d to stack. \n", (int)tmpNum);

                Tmp = malloc(sizeof(BTNode));
                Tmp->item = tmpNum;
                Tmp->left = NULL;
                Tmp->right = NULL;

                push(&s, Tmp);
                tmpNum = -1;
                power = 0;
            }

            break;
        } //end of switch case


        i++; // while loop counter
    } //end of while loop


    // STEP 3: set root to the last element in s, pop s
    //printf("set root to the last element in s, pop s.\n");
    *root = s.head->item;
    pop(&s);


}

void printTree(BTNode *node){
    //Write your code here
    if (node == NULL){
        return;
    }
    printTree(node->left);

    if ( node->item == '+' || node->item == '-' || node->item == '*' || node->item == '/' )
        printf("%c ",node->item);
    else printf("%d ",node->item);

    printTree(node->right);
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if (node == NULL){
        return;
    }

    printTreePostfix(node->left);
    printTreePostfix(node->right);

    if ( node->item == '+' || node->item == '-' || node->item == '*' || node->item == '/' )
        printf("%c ",node->item);
    else printf("%d ",node->item);


}

double computeTree(BTNode *node){
//Write your code here
    if (node == NULL){
        return 0;
    }

    //double op1, op2 = 0;

    //computeTree(node->left);
    //computeTree(node->right);

    if ( node->item == '+' )
        return computeTree(node->left) + computeTree(node->right);
    else if (node->item == '-')
        return computeTree(node->left) - computeTree(node->right);
    else if (node->item == '*')
        return computeTree(node->left) * computeTree(node->right);
    else if (node->item == '/')
        return computeTree(node->left) / computeTree(node->right);
    else {
        return node->item;
    }
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}
