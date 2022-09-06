#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

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

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g,i,j);

    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    printGraphList(g);
    return 0;
}

int BFS (Graph g, int v, int w){
    // Write your code here

    // initialisation

    ListNode *tmp;

    Queue *q;
    q = malloc(sizeof(Queue *));
    q->head=NULL;
    q->tail=NULL;
    q->size=0;

    int distance = 0;
    int i,j,k,s;

    v = v-1;

    // printf("Step 1: Initialization.\n");

    if (g.list[v] == NULL) {
        return -1;
    }
    else {
        tmp = g.list[v];
    }

    // printf("Step 2: If empty, return, if not, set tmp to list[v].\n");

    while(tmp!=NULL)
    {
        enqueue(q, tmp->vertex);
        tmp = tmp->next;
    }
    // printf("Get front q %d.\n",getFront(*q));
    // printf("Q has %d items.\n",q->size);
    // printf("Step 3: Add list[v]items to queue. \n");

    // STEP 1 enqueue the current level to q, distance + 1
    // STEP 2 check whether the current level contain w, if yes, return distance, if not, next step
    // STEP 3 Dequeue the current level elements, and enqueue the next level elements, distance +1
    // STEP 4 Repeat 2 & 4, until find the w, maximum loop 7 times.

    for (i=0; i<(g.V-1); i++)
    {
        // printf("Step 4: Enter the first for loop, loop i = %d. \n", i);
        distance ++;

        // printf("Distance = %d. \n", distance);

        s = q->size;
        for (j=0; j<s; j++)
        {
            // printf("Step 6: Enter the third for loop, loop j = %d. \n", j);
            // printf("j<q->size, q.size = %d. \n", q->size);
            if (getFront(*q)==w)
            {
                return distance;
            }
            else
            {
                enqueue(q, getFront(*q));
                dequeue(q);
            }
        }

        s = q->size;
        for (k=0; k<s; k++)
        {
            // printf("Step 5: Enter the second for loop, loop k = %d. \n", k);
            tmp = g.list[getFront(*q)-1];
            dequeue(q);
            while(tmp!=NULL)
            {
                enqueue(q, tmp->vertex);
                tmp = tmp->next;
            }
        }

    }
    return -1;
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

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
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

