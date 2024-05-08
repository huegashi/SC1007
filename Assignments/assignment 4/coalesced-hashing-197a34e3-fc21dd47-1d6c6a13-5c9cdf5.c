#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

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
    int val=key%TABLESIZE;

    if(HashFind(key, hashTable)!=-1){
        return-1; //duplicate key
    }
    //sanity check full table
    int i=0;
    while(hashTable[i].indicator==USED && i<TABLESIZE){
        i++;
    }
    if(i>=TABLESIZE){
        return i;
    }
    //insertion of non duplicate key:
    //if spot is not empty we look for the next empty slot from val onwards
    //case 1: next!=-1, keys are chained
    //we iterate to the last chained key
    while(hashTable[val].indicator!=EMPTY && hashTable[val].next!=-1){
        val=hashTable[val].next;
    }
    i=val; //save i as val for temporary iterations
    //case 2/continuation of case 1: we look for the next empty spot
    while(hashTable[i].indicator!=EMPTY && i<TABLESIZE){
        i++;
    }
    //if we cannot find empty spot after val, we may look for one before val
    // (since table is not full, there must be at least 1 empty slot available)
    if (i>=TABLESIZE){
        i=0;
        while(hashTable[i].indicator!=EMPTY && i<val){
            i++;
        }
    }
    //after finding empty spot, we chain up the values and take up empty spot
    if (hashTable[val].indicator == USED) {
        hashTable[val].next = i;
    }

    //insert key into empty spot 
    hashTable[i].indicator=USED;
    hashTable[i].key=key;
    return i;
}

int HashFind(int key, HashSlot hashTable[])
{
    int val=key%TABLESIZE;
    if (hashTable[val].indicator==EMPTY){
        return -1;
    }
    //case1:key is store at immeidate spot
    //case2:key is stored at chained spot from val
    //check if key is at the immediate spot
    if (hashTable[val].key==key){
        return val;
    }
    //if immediate spot does not have key and next==-1,then key is not on table
    if (hashTable[val].next==-1){
        return -1;
    }
    
    //we iterate .next values to look for key
    while (hashTable[val].next!=-1){
        val=hashTable[val].next;
        if (hashTable[val].key==key){
            return val;
        }
    }

    //if loop stopped: next==-1, chain of hash stopped and key has not been found
   
    return -1;

}