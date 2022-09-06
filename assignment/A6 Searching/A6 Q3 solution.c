#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 7
#define PRIME     3

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    // Write your code here
    int i;
    int index;
    int firstIndex=-1;

    if (HashFind(key, hashTable)!= -1)
        return -1;

    index = hash(key);

    for (i=0; i<TABLESIZE; i++){

        if (hashTable[index].indicator==EMPTY){
            hashTable[index].key = key;
            hashTable[index].indicator = USED;
            if (firstIndex != -1)
                hashTable[firstIndex].next = index;
            return index;
        }
        else{
            if(hashTable[index].next==-1){
                if(firstIndex == -1) firstIndex = index;
                index = (index + 1) % TABLESIZE;
            }
            else{
                index = hashTable[index].next;
            }
        }
    }
    return TABLESIZE;
    /*
    int i;
    int index = hash(key);
    int pre = index;

    for (i=0; i<TABLESIZE; i++){
        // find a duplicate key
        if (hashTable[index].key == key && hashTable[index].indicator == USED){
            return -1;
        }
        // find a empty slot
        else if (hashTable[index].indicator == EMPTY){
            hashTable[index].key = key;
            hashTable[index].indicator = USED;
            if (i>0){
                hashTable[pre].next = index;
            }

            return index;
        }
        // it's a used slot
        else {
            if (0<=index && index<TABLESIZE){
                index = index + 1;
            }
            else if (index == TABLESIZE)
                index = 0;
            else{
                printf("error");
            }

        }
    }
    return TABLESIZE;
    */
}

int HashFind(int key, HashSlot hashTable[])
{
 // Write your code here
    int i;

    for (i=0; i<TABLESIZE; i++){
        if(hashTable[i].key == key && hashTable[i].indicator==USED)
            return i;
    }
    return -1;
}
