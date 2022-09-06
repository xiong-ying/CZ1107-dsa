#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

int CC (Graph g);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;

        if(g.list[i]==NULL){
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else{
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");

    printGraphList(g);

    int res = CC(g);
    if(res ==1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    printGraphList(g);
    return 0;
}

int CC (Graph g)
{
    // Write your code here
    Queue q;
    //q = (Queue *)malloc(sizeof(Queue));
    q.head=NULL;
    q.tail=NULL;
    q.size=0;

    Stack s;
    //s = (Stack *)malloc(sizeof(Stack));
    s.head=NULL;
    s.size=0;

    ListNode *tmp;

    int i, j, k;
    int visited[g.V];


    for (i=0; i<g.V; i++){
        visited[i] = 0;
        //printf("visited is %d.\n", visited[i]);
    }

    for (j=0; j<g.V; j++){

        //printf("1. For loop, j = %d.\n", j);
        visited[j] = 1;

        enqueue(&q, j+1);

        while (isEmptyQueue(q)==0){
            //printf("2. While isEmptyQueue == 0.\n");
            //printf("getFront(*q) is %d.\n", getFront(q));
            tmp = g.list[getFront(q)-1];

            while(tmp!=NULL)
            {
                //printf("3. While tmp!=NULL.\n");
                push(&s, tmp->vertex);
                tmp = tmp->next;
            }

            while (isEmptyStack(s)==0)
            {
                //printf("4. While isEmptyStack ==0.\n");
                if (visited[peek(s)-1]==0) {enqueue(&q, peek(s));}
                visited[peek(s)-1]=1;
                pop(&s);
            }

            //printf("%d.\n", getFront(q));
            dequeue(&q);


        }

        //printf("5. Before comparison.\n");
        for (k=0; k<g.V; k++){
            // end of comparison, check result
            if (visited[k] == 0) {
                //printf("6. cannot reach this element %d.\n", k+1);
                return 0;
            }
            // restore visited array
            else {
                visited[k] = 0;
                //printf("7. reset the array for the %d element.\n", k);
            }
        }


    }
    return 1;


    /*
    int canFind = 0;
    int i,j,k,cur;
    int isVisited = 0;

    ListNode *tmp;

    Queue *q;
    q = malloc(sizeof(Queue *));
    q->head=NULL;
    q->tail=NULL;
    q->size=0;

    Stack *s;
    s = malloc(sizeof(Stack *));
    s->head=NULL;
    s->size=0;

    printf("Step 1: Initialization. \n");

    for (i=0; i<g.V; i++)
    {   printf("Step 2: First for loop, i = %d. \n", i);
        for (j=0; j<g.V; j++)
        {// cannot be the same vertex
            if (i==j) continue;

            // Start of i j search
            printf("Step 3: Second for loop, j = %d. \n", j);

            tmp = g.list[i];
            while (tmp!=NULL)
            {
                printf("Step 4: First while loop.\n");

                push(s, tmp->vertex);
                printf("Finished push. peek stack is %d.\n", peek(*s));

                tmp = tmp->next;
            }

            // if search = j:canFind = 1;
            while (isEmptyStack(*s)==0)
            {
                printf("Step 5: isEmptyStack while loop.\n");

                cur = peek(*s);
                printf("cur is %d,\n", cur);
                pop(s);

                if (cur == j+1)
                {
                    canFind = 1;
                    removeAllItemsFromQueue(q);
                    removeAllItemsFromStack(s);
                    break;
                }
                else
                {
                    for (k=0; k<q->size; k++){
                        if (getFront(*q) == cur){
                            isVisited = 1;
                        }
                        enqueue(q, getFront(*q));
                        dequeue(q);
                    }


                    if (isVisited == 0)
                    {

                        tmp = g.list[cur-1];
                        while (tmp!=NULL)
                        {
                            printf("Step 6: while loop.\n");

                            for (k=0; k<q->size; k++){
                                if (getFront(*q) == tmp->vertex){
                                    isVisited = 1;
                                }
                                enqueue(q, getFront(*q));
                                dequeue(q);
                            }
                            if (isVisited == 0){push(s, tmp->vertex);}
                            else {isVisited=0;}
                            printf("Finished push. peek stack is %d.\n", peek(*s));
                            tmp = tmp->next;
                        }
                    }
                    else{
                        isVisited = 0;
                    }

                }
            }

            //end of i j search:

            removeAllItemsFromQueue(q);
            removeAllItemsFromStack(s);

            printf("canfind = %d.\n", canFind);
            printf(" \n");
            if (canFind == 1) {canFind = 0;}
            else {return 0;}
        }
    }

    return 1;
    */

}


void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
