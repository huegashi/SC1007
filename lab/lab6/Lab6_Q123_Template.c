#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV); //Q3

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g); //Q1

    calDegreeV(g,degreeV); //Q3

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g); //Q2
    printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjM2adjL(Graph *g)
{
     // Question 1
     // Write your code here
    ListNode* newNode;
    ListNode** list;


    if(g->type == ADJ_LIST) {printf("Error"); return;}
    if(g->V<=0){printf("Empty graph!"); return;}

    list = (ListNode **) malloc(g->V*sizeof(ListNode *));
    for(int i=0;i<g->V;i++)
        list[i] = NULL;



    for(int i=0;i<g->V;i++){
        for(int j=0;j<g->V;j++){
            if (g->adj.matrix[i][j]!=0){
                if (list[i]==NULL){
                    list[i] = (ListNode*)malloc(sizeof(ListNode));
                    list[i]->vertex = j+1;
                    list[i]->next =NULL;
                    newNode=list[i];
                }
                else{
                    newNode->next = (ListNode*)malloc(sizeof(ListNode));
                    newNode->next->vertex = j+1;
                    newNode->next->next =NULL;
                    newNode=newNode->next;
                }
            }
        }
     }
     g->type = ADJ_LIST;

     //free adjMatrix
    for(int i=0;i<g->V;i++)
        free(g->adj.matrix[i]);
    free(g->adj.matrix);

    g->adj.list=list;

     return;
}

void adjL2adjM(Graph *g){
	// Question 2
    // Write your code here
    int i;
    ListNode* temp;

    if(g->type == ADJ_MATRIX) {printf("Error"); return;}

    if(g->V<=0){printf("Empty graph!"); return;}

    int ** mat = (int **)malloc(g->V*sizeof(int *));
    for(int i=0;i<g->V;i++)
        mat[i] = (int *)malloc(g->V*sizeof(int));

    for(int i=0;i<g->V;i++)
        for(int j=0;j<g->V;j++)
            mat[i][j] = 0;

    g->adj.matrix = mat;

    for(i=0;i<g->V;i++)
    {
        temp = g->adj.list[i];
        while(temp!=NULL){
            int j=temp->vertex;
            g->adj.matrix[i][j-1]=1;
            temp = temp->next;
        }

    }
    g->type = ADJ_MATRIX;

    for(i=0;i<g->V;i++)
        free(g->adj.list[i]);
    free(g->adj.list);



    return;


}

void calDegreeV(Graph g, int *degreeV)
{
	// Question 3
    // Write your code here

    if(g.type == ADJ_MATRIX){
        for(int i=0;i<g.V;i++){
            degreeV[i]=0;
            for(int j=0;j<g.V;j++){
                degreeV[i]+=g.adj.matrix[i][j];

            }
        }

    }else{
        for(int i=0;i<g.V;i++){
            degreeV[i]=0;
            ListNode *temp = g.adj.list[i];
            while(temp!=NULL){
                degreeV[i]++;
                temp = temp->next;
            }
        }
    }
    return;
}

