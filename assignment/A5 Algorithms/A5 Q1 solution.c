#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);

void expressionLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL, int seed);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    expressionLL(infix, &inExpLL);

    int seed;
    printf("Enter a seed: \n");
    scanf("%d",&seed);
    printExpLL(inExpLL,seed);

    removeAllNodes(&inExpLL);
    return 0;
}


void expressionLL(char* infix, LinkedList *inExpLL)
{
    // STEP 1: Initialization
    char c;
    int i = 0;

    int PrevIsNum = 0;
    int TmpNum = 0;

    LinkedList TmpList;
    TmpList.head = NULL;
    TmpList.size = 0;

    ListNode* TmpNode =NULL;

    //printf("Initialization success. \n");


    // STEP 2: go through the infix and sort every item  into linkedlist
    while ( infix[i]!='\0'){
        //printf("while loop %d, infix[i] = %c.",i,infix[i]);
        c = infix[i];

        switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            c = (int)c; //convert char to ascii
            //printf("c = %d. \n",c);

            //if previous char is number, add TmpNum to linkedlist
            if (PrevIsNum == 1){
                insertNode(&TmpList, TmpNum, OPERAND);
                TmpNum = 0;
            }

            //Then add operator to linkedlist
            insertNode(&TmpList, c, OPT);

            //define the type of this char
            PrevIsNum = 0;
            break;

        default: //when c is digit
            c = c - '0'; //convert char to int

            if (PrevIsNum == 1){
                TmpNum = c + TmpNum * 10;
            }
            else{
                TmpNum = c;
            }
            //printf("c = %d. \n",c);

            //define the type of this char
            PrevIsNum = 1;
            break;

        }

        i++; //while loop counter
    } // out of while loop

    //If last char is digit, add to linked list
    if (PrevIsNum == 1) insertNode(&TmpList, TmpNum, OPERAND);


    //STEP 3: Reverse the Tmp linkedlist
    TmpNode = TmpList.head;

    while (isEmptyLinkedList(TmpList) == 0){
        insertNode(inExpLL, TmpNode->item, TmpNode->type);
        deleteNode(&TmpList);
        TmpNode = TmpNode->next;
    }


}

void printExpLL(LinkedList inExpLL, int seed)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item+ seed);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}
