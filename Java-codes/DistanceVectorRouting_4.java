// 4) Implement distance vector routing algorithm for obtaining routing tables at each node.
import java.util.Scanner;

public class DistanceVectorRouting_4 {
    static final int INF = 9999;

    // Function to print the routing table for each node
    static void printRoutingTable(int numNodes, int[][] distVector, int[][] nextHop) {
        for (int i = 0; i < numNodes; i++) {
            System.out.println("Routing table for node " + i + ":");
            System.out.println("Destination\tNext Hop\tDistance");
            for (int j = 0; j < numNodes; j++) {
                if (distVector[i][j] == INF) {
                    System.out.println(j + "\t\t-\t\tINF");
                } else {
                    System.out.println(j + "\t\t" + nextHop[i][j] + "\t\t" + distVector[i][j]);
                }
            }
            System.out.println();
        }
    }

    static void distanceVectorRouting(int n, int[][] costMat, int[][] distanceVec, int[][] nextHop) {
        boolean updated;
        do {
            updated = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        if (distanceVec[i][k] + distanceVec[k][j] < distanceVec[i][j]) {
                            distanceVec[i][j] = distanceVec[i][k] + distanceVec[k][j];
                            nextHop[i][j] = nextHop[i][k];
                            updated = true;
                        }
                    }
                }
            }
        } while (updated);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of nodes: ");
        int n = sc.nextInt();

        int[][] costMat = new int[n][n];
        int[][] distanceVec = new int[n][n];
        int[][] nextHop = new int[n][n];

        System.out.println("Enter the cost matrix (use " + INF + " for INF):");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                costMat[i][j] = sc.nextInt();
            }
        }

        // Initialize distanceVec and nextHop tables
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                distanceVec[i][j] = costMat[i][j];
                nextHop[i][j] = (costMat[i][j] != INF && i != j) ? j : -1;
            }
        }

        distanceVectorRouting(n, costMat, distanceVec, nextHop);
        printRoutingTable(n, distanceVec, nextHop);

        sc.close();
    }
}
