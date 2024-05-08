#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


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
    int hash=hash1(key),i=0, comparisons=0, savepoint=0;
    
    //NOTE: Must iterate and check all possible probes if not empty to check for duplicates
    //hash= (hash+ i*hash2(key))%TABLESIZE;
    //printf("%d \n", index);

    //iteratable entries
    while(hashTable[hash].indicator==USED && hashTable[hash].key!=key && i < TABLESIZE){
        hash= (hash+ hash2(key))%TABLESIZE;
        i++;
    }

    //sanity check for full table
    if (i >= TABLESIZE) {
        return i;
    }
    comparisons=i;
    
    if (hashTable[hash].indicator==USED && hashTable[hash].key==key){
        return -1; //return for duplicate found
    }

    //if deleted, we keep interating to look for duplicates
    savepoint=hash;
    
    while(hashTable[hash].indicator!=EMPTY && i<TABLESIZE){
        if (hashTable[hash].indicator==USED && hashTable[hash].key==key){
            return -1; //return for duplicate found
        }else if(hashTable[hash].indicator==USED){
            // we addd a comparison if its not deleted or a duplicate
            comparisons++;
        }
        hash= (hash+ hash2(key))%TABLESIZE;
        i++;
    }
    
    //if i exceeds, means we have checked the whole table for duplicates
    //since theres no duplicates, we save at the first empty/deleted point we saved earlier

    hashTable[savepoint].key = key;
    hashTable[savepoint].indicator = USED;
    return comparisons;
    
}

int HashDelete(int key, HashSlot hashTable[])
{   
    int hash=hash1(key),comparisons=0,i=0;
    while(hashTable[hash].indicator!=EMPTY && i<TABLESIZE){
        
        if (hashTable[hash].indicator==USED && hashTable[hash].key==key){
            hashTable[hash].indicator=DELETED;
            return comparisons+1;
        }else if (hashTable[hash].indicator==USED){
            // we only add comparisons if indicator is used
            // if indicator is deleted, we continue interating but without counting as a comparison
            comparisons++;
        }
        hash= (hash+ hash2(key))%TABLESIZE;
        i++;
        
    }
    return -1;
}