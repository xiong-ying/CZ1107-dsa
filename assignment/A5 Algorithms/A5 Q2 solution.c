#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

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

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Test case: 99+(88-77)*(66/(55-44)+33)
    /* STEP 1: Initialize */

    // reverse infix char
    char RevInfix[SIZE];
    int begin, end, count = 0;

    // while loop through Revinfix
    int i=0;
    char c;

    //Tmp stack to store operators
    Stack OperatorS;
    OperatorS.head=NULL;
    OperatorS.size=0;

    //Tmp number to store operands
    int tmpNum=-1;
    char n;
    int power=0;
    int tmpPower=0;
    int h = 0;

    //printf("Initialization successful. \n");


    /* STEP 2: Reverse infix char */

    // Calculating string length
    while (infix[count] != '\0'){
        count++;
    }
    end = count - 1;

    //printf("infix count = %d, end = %d.\n",count,end);

    // Reverse string
    for (begin = 0; begin < count; begin++)
    {
        RevInfix[begin] = infix[end];
        end--;
    }
    RevInfix[begin] = '\0';

    //printf("RevInfix is %s\n", RevInfix);


    /* STEP 3: change to prefix */
    while (RevInfix[i]!='\0'){
        c = RevInfix[i];

        //printf("\n");
        //printf("while loop %d, RevInfix[i] = %c, c = %c .\n", i, RevInfix[i], c);

        switch(c){
        case ' ':
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            // compare c and peek(s)'s precedence

            if (isEmptyStack(OperatorS) == 0){ // if Operator Stack not empty

                while ( ( c == '+' || c == '-') && (peek(OperatorS) == '*' || peek(OperatorS) == '/') ) {
                    //printf("c is +-, when peek(S) is * /. \n");
                    //printf("pop 1 operator, insert to inExpLL, push c to S. \n");

                    insertNode(inExpLL, peek(OperatorS), OPT);
                    pop(&OperatorS);

                    if (isEmptyStack(OperatorS) == 1) break;
                }
            }
            //printf("push c to operator stack. \n");
            push(&OperatorS, c);
            break;

        case '(':

            while (peek(OperatorS) != ')'){

                //printf("pop 1 operator, add to front of inExpLL, until encouter ). \n");
                insertNode(inExpLL, peek(OperatorS), OPT);
                pop(&OperatorS);
            }
            //printf("pop ) .\n");
            pop(&OperatorS);

            break;


        case ')':

            //printf("Push ')' to operator stack. \n");
            push(&OperatorS, c);
            break;

        default: // if c is number

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

            // Check the next char in infix
            n = RevInfix[i+1];

            // If next char is operator or end, just insert number to LL
            if (n=='+' || n=='-' || n=='*'  || n=='/'  || n=='('  || n==')' || n==' ' || n=='\0' ){
                //printf("insert number %d to LL. \n", (int)tmpNum);
                insertNode(inExpLL, (int)tmpNum, OPERAND);
                tmpNum = -1;
                power = 0;
            }


            break;
        }

        i++; //while loop counter
    }//out of while loop

    /* STEP 4: POP all operators from stack */
    while ( isEmptyStack(OperatorS) == 0 ){
        insertNode(inExpLL, peek(OperatorS), OPT);
        pop(&OperatorS);
    }




    /*
    //STEP 1: Initialize
    int i=0;
    char c;
    char n;

    char* op1 = '\0';
    char* op2 = '\0';
    char* op = '\0';
    int p=0;
    int counter=0;

    int TmpNum=0;

    Stack OperatorS;
    OperatorS.head=NULL;
    OperatorS.size=0;

    Stack OperandS;
    OperandS.head=NULL;
    OperandS.size=0;

    printf("Initialization successful. \n");


    //STEP 2: loop through infix
    while (infix[i]!='\0'){
        c = infix[i];

        printf("\n");
        printf("while loop %d, infix[i] = %c, c = %c .\n", i, infix[i], c);

        switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
            // compare c and peek(s)'s precedence

            if (isEmptyStack(OperatorS) == 0){ // if Operator Stack not empty

                if ( ( c == '+' || c == '-') && (peek(OperatorS) != '(') ) {
                    printf("c is +-, and previous one is +-* /, execute the previous operation. \n");

                    printf("pop 1 operator, pop 2 operands, connect them, push back to OperandS. \n");

                    //pop operator
                    op[counter++] = peek(OperatorS);
                    pop(&OperatorS);
                    printf("pop 1 operator is %c .\n", *op);

                    //pop 2 Operands
                    op2[p] = peek(OperandS);
                    pop(&OperandS);
                    printf("pop op2 is %c .\n", *op2);

                    op1[p] = peek(OperandS);
                    pop(&OperandS);
                    printf("pop op1 is %c .\n", *op1);

                    //connect strings

                    while (op1[p]!='\0'){
                        op[counter++] = op1[p];
                        p++;
                    }
                    p=0;
                    while (op2[p]!='\0'){
                        op[counter++] = op1[p];
                        p++;
                    }
                    p=0;
                    counter=0;

                    printf("Connected op is %c .\n", *op);

                    //push back to operand stack
                    push(&OperandS, *op);

                }
                else if ( ( c == '*' || c == '/') && ( peek(OperatorS) == '*' || peek(OperatorS) == '/') ){
                    printf("c is * /, and previous one is * /, execute the previous operation. \n");

                    printf("pop 1 operator, pop 2 operands, connect them, push back to OperandS. \n");



                    //pop operator
                    op[counter++] = peek(OperatorS);
                    pop(&OperatorS);
                    printf("pop 1 operator is %c .\n", *op);

                    //pop 2 Operands
                    op2[p] = peek(OperandS);
                    pop(&OperandS);
                    printf("pop op2 is %c .\n", *op2);

                    op1[p] = peek(OperandS);
                    pop(&OperandS);
                    printf("pop op1 is %c .\n", *op1);

                    //connect strings

                    while (op1[p]!='\0'){
                        op[counter++] = op1[p];
                        p++;
                    }
                    p=0;
                    while (op2[p]!='\0'){
                        op[counter++] = op1[p];
                        p++;
                    }
                    p=0;
                    counter=0;

                    printf("Connected op is %c .\n", *op);

                    //push back to operand stack
                    push(&OperandS, *op);




                }
                else{
                    printf("Previous operator decedence lower, just push to stack. \n");
                }
            }

            printf("Just push to operator stack. \n");
            push(&OperatorS, c);
            break;

        case '(':
            printf("Just push '(' to stack. \n");
            push(&OperatorS, c);
            break;

        case ')':

            while (peek(OperatorS) != '('){

                printf("pop 1 operator, pop 2 operands, connect them, push back to OperandS. \n");

                //pop operator
                op[counter++] = peek(OperatorS);
                pop(&OperatorS);
                printf("pop 1 operator is %c .\n", *op);

                //pop 2 Operands
                op2[p] = peek(OperandS);
                pop(&OperandS);
                printf("pop op2 is %c .\n", *op2);

                op1[p] = peek(OperandS);
                pop(&OperandS);
                printf("pop op1 is %c .\n", *op1);

                //connect strings

                while (op1[p]!='\0'){
                    op[counter++] = op1[p];
                    p++;
                }
                p=0;
                while (op2[p]!='\0'){
                    op[counter++] = op1[p];
                    p++;
                }
                p=0;
                counter=0;

                printf("Connected op is %c .\n", *op);

                //push back to operand stack
                push(&OperandS, *op);



            }
            printf("pop ( .\n");
            pop(&OperatorS);

            break;


        default: // if c is number

            c = c - '0';
            TmpNum = TmpNum * 10 + c;

            // Check the next char in infix
            n = infix[i+1];

            // If next char is operator or end, just push to the stack
            if (n=='+' || n=='-' || n=='*'  || n=='/'  || n=='('  || n==')' || n=='\0' ){
                printf("Push number %d to Operand stack. \n", TmpNum);
                push(&OperandS, TmpNum + '0');
                TmpNum = 0;
            }

            break;
        }

        i++; //while loop counter
    }//out of while loop


    // STEP 3: finish the calculation while Stack are not empty
    while ( isEmptyStack(OperatorS) == 0 ){
        printf("pop 1 operator, pop 2 operands, connect them, push back to OperandS. \n");


        //pop operator
        op[counter++] = peek(OperatorS);
        pop(&OperatorS);
        printf("pop 1 operator is %c .\n", *op);

        //pop 2 Operands
        op2[p] = peek(OperandS);
        pop(&OperandS);
        printf("pop op2 is %c .\n", *op2);

        op1[p] = peek(OperandS);
        pop(&OperandS);
        printf("pop op1 is %c .\n", *op1);

        //connect strings

        while (op1[p]!='\0')
        {
            op[counter++] = op1[p];
            p++;
        }
        p=0;
        while (op2[p]!='\0')
        {
            op[counter++] = op1[p];
            p++;
        }
        p=0;
        counter=0;

        printf("Connected op is %c .\n", *op);

        //push back to operand stack
        push(&OperandS, *op);




    }

    // The last element in Operand Stack is the formula we want. put it in the linked list
    printf("%c",peek(OperandS));

    */

}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
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
    if(LLPtr==NULL || LLPtr->size==0){
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

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
