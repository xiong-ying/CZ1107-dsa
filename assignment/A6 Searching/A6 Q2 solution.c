#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 7
#define PRIME     3

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);

// my functions
void checkAllEmpty(HashSlot hashTable[]);
int HashSearch(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    //Write your code here
    int i=0;
    int index;
    int comparisons=0;
    int savedDeletedIndex = -1;

    do{
        index = hash1(key + i*hash2(key) ) ;

        if (hashTable[index].indicator == USED)
        {
            comparisons++;
            if (hashTable[index].key == key) return -1;
        }
        else if (hashTable[index].indicator == DELETED)
        {
            //comparisons++;
            if (savedDeletedIndex == -1)
                savedDeletedIndex = index;
        }
        else if (hashTable[index].indicator == EMPTY)
        {
            if (savedDeletedIndex == -1){
                hashTable[index].key = key;
                hashTable[index].indicator = USED;
                return comparisons;
            }
            else{
                hashTable[savedDeletedIndex].key = key;
                hashTable[savedDeletedIndex].indicator = USED;
                return comparisons;
            }
        }
        else
        {
            printf("Error.\n");
        }
        i++;
    } while (i<TABLESIZE);

    if (savedDeletedIndex != -1){
        hashTable[savedDeletedIndex].key = key;
        hashTable[savedDeletedIndex].indicator = USED;
        return comparisons;
    }
    else{
        return comparisons;
    }


   /*
    int index;
    int i;

    // if key is a duplicate, return -1;
    if (HashSearch(key, hashTable)!= -1) return -1;

    // loop through and check for EMPTY and DELETED slot
    for(i=0; i<TABLESIZE; i++){
        index = hash1(key + i*hash2(key) ) ;

        if (hashTable[index].indicator==EMPTY || hashTable[index].indicator==DELETED)
        {
            hashTable[index].key = key;
            hashTable[index].indicator = USED;
            return i;
        }
    }

    return i;
    */
}

int HashDelete(int key, HashSlot hashTable[])
{
    //Write your code here
    int i=0;
    int index;
    int comparisons=0;

    do{
        index = hash1(key + i*hash2(key) ) ;

        if (hashTable[index].indicator == USED)
        {
            comparisons++;
            if (hashTable[index].key == key){
                hashTable[index].indicator = DELETED;
                return comparisons;
            }
        }
        else if (hashTable[index].indicator == DELETED)
        {
            comparisons++;
        }
        else if (hashTable[index].indicator == EMPTY)
        {
            comparisons++;
        }
        else
        {
            printf("Error.\n");
        }
        i++;
    } while (i<TABLESIZE);

    return -1;

    /*
    int index;
    int i;
    int comparisons = 0;

    // if key is not exist, return -1;
    if (HashSearch(key, hashTable)== -1) return -1;

    for(i=0; i<TABLESIZE; i++){
        index = hash1(key + i*hash2(key) );

        if (hashTable[index].indicator==USED){
            comparisons ++;
            if (hashTable[index].key == key){
                hashTable[index].indicator = DELETED;
                checkAllEmpty(hashTable);
                return comparisons;
            }
        }
    }
    checkAllEmpty(hashTable);
    return -1;
    */

}

int HashSearch(int key, HashSlot hashTable[]){
    int i;
    int index=-1;
    for(i=0; i<TABLESIZE; i++){
        if (hashTable[i].indicator == USED && hashTable[i].key == key){
            index = i;
            break;
        }
    }
    return index;
}


void checkAllEmpty(HashSlot hashTable[])
{

    int i;
    int isEmpty = 0;
    // if all tags are EMPTY, set DELETED slot to EMPTY
    for(i=0; i<TABLESIZE; i++){
        if (hashTable[i].indicator == USED){
            isEmpty = 0;
            break;
        }
        else {
            isEmpty = 1;
        }
    }
    if (isEmpty == 1){
        for(i=0; i<TABLESIZE; i++){
            hashTable[i].key=0;
            hashTable[i].indicator=EMPTY;
        }
    }
}
