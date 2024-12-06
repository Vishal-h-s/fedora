/*
Implement distance vector routing algorithm for obtaining routing tables at each node.

Sample Output:
Enter the number of nodes: 4
Enter the cost matrix (use 9999 for INF):
0 12 9 4
12 0 1 9999
9 1 0 2
4 9999 2 0
Routing table for node 0:
Destination	Next Hop	Distance
0		-1		0
1		3		7
2		3		6
3		3		4

Routing table for node 1:
Destination	Next Hop	Distance
0		2		7
1		-1		0
2		2		1
3		2		3

Routing table for node 2:
Destination	Next Hop	Distance
0		3		6
1		1		1
2		-1		0
3		3		2

Routing table for node 3:
Destination	Next Hop	Distance
0		0		4
1		2		3
2		2		2
3		-1		0

*/
#include<stdio.h>
#include<stdlib.h>
#define INF 9999

// Function to print the routing table for each node
void printRoutingTable(int numNodes, int **distVector, int **nextHop) {
    for (int i = 0; i < numNodes; i++) {
        printf("Routing table for node %d:\n", i);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < numNodes; j++) {
            if (distVector[i][j] == INF) {
                printf("%d\t\t-\t\tINF\n", j);
            } else {
                printf("%d\t\t%d\t\t%d\n", j, nextHop[i][j], distVector[i][j]);
            }
        }
        printf("\n");
    }
}

void distanceVectorRouting(int n,int **costMat,int **distanceVec,int **nextHop){
        int updated;
        do{
            updated = 0;
            for(int i = 0 ; i < n ; i++){
                for(int j = 0 ; j < n ; j++){
                    for(int k = 0 ; k < n ; k++){
                        if(distanceVec[i][k] + distanceVec[k][j] < distanceVec[i][j]){
                            distanceVec[i][j] = distanceVec[i][k] + distanceVec[k][j];
                            nextHop[i][j] = nextHop[i][k];
                            updated = 1;
                        }
                    }
                }
            }
        }while(updated);
}
int main(){
    
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    
    int **costMat = (int **)malloc(n * sizeof(int *));
    int **distanceVec = (int **)malloc(n * sizeof(int *));
    int **nextHop = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        costMat[i] = (int *)malloc(n * sizeof(int));
        distanceVec[i] = (int *)malloc(n * sizeof(int));
        nextHop[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Enter the cost matrix (use %d for INF):\n",INF);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&costMat[i][j]);
        }
    }
    
    // now initilize distanceVec and routing table
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            distanceVec[i][j] = costMat[i][j];
            
            nextHop[i][j] = (costMat[i][j] != INF && i != j) ? j : -1; // else put -1 for no connection 
        }
    }
    
    distanceVectorRouting(n,costMat,distanceVec,nextHop);
    printRoutingTable(n, distanceVec, nextHop);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(costMat[i]);
        free(distanceVec[i]);
        free(nextHop[i]);
    }
    free(costMat);
    free(distanceVec);
    free(nextHop);
    
    return 0;
}