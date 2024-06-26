#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize;
   int nSize;
   HashTableNode *Table;
} HashTable;

int Hash(int,int);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q4Hash;
    Q4Hash.hSize = 0;
    Q4Hash.nSize = 0;
    Q4Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter number of data to be inserted:\n");
            scanf("%d",&size);

            Q4Hash.hSize = (int)size/ LOAD_FACTOR;
            Q4Hash.nSize = 0;

            Q4Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q4Hash.hSize));

            for(i=0;i<Q4Hash.hSize;i++){
               Q4Hash.Table[i].head = NULL;
               Q4Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q4Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q4Hash, key);

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q4Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q4Hash.hSize;i++)
    {
        while(Q4Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q4Hash.Table[i].head;
            Q4Hash.Table[i].head = Q4Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q4Hash.Table);

    return 0;

}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q4Hash, int key)
{
    // Write your code here
    int i=Hash(key, Q4Hash.hSize);
    ListNode *temp=Q4Hash.Table[i].head;
    while(temp !=NULL)
    {
        if (temp->key==key){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int HashInsert(HashTable* Q4HashPtr, int key) {
  // Sanity check for duplicate (assuming HashSearch exists)
  if (HashSearch(*Q4HashPtr, key) != NULL) {
    return 0; // Duplicate found
  }

  int h = Hash(key, &(Q4HashPtr->hSize)); // Calculate hash index

  // Allocate memory for the new node
  ListNode* newnode = malloc(sizeof(ListNode));

  newnode->key = key;
  newnode->next = NULL;  // Set next pointer to NULL for tail

  // If the bucket list is empty, make the new node the head
  if (Q4HashPtr->Table[h].head == NULL) {
    Q4HashPtr->Table[h].head = newnode;
    newnode->next=NULL;
    Q4HashPtr->Table[h].size++;
    Q4HashPtr->nSize++;
    return 1;
  }

  // Traverse to the last node using a separate pointer
  ListNode* last = Q4HashPtr->Table[h].head;
  while (last->next != NULL) {
    last = last->next;
  }

  // Insert the new node at the end
  last->next = newnode;
  Q4HashPtr->Table[h].size++;
  Q4HashPtr->nSize++;
  last->next=NULL;

  // Optional size update (consider tracking total elements separately)
  // Q4HashPtr->nSize++; // Increment total size of hash table

  return 1;
}


void HashPrint(HashTable Q4Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q4Hash.hSize;i++)
    {
        temp =Q4Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}
