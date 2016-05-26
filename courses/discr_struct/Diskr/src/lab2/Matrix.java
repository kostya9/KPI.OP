
package lab2;

import java.util.*;

public class Matrix {
    final int INFINITY = 1000;
    final int EMPTY_ITEM = 0;

    private int[][] matrix;
    private int[] distance;
    private int[] prevPaths;
    private int dimension;
    private int[] FulkersonMax;

    public Matrix() {
        this.dimension = -1;
    }

    public Matrix(int[][] matrix, int dimension) {
        this.matrix = matrix;
        this.dimension = dimension; // this.dimension = matrix[0].length;
    }

    public void PrintMainMatrix() {
        System.out.println("Inputed matrix:");
        for (int i = 0; i < this.dimension; i++) {
            for (int j = 0; j < this.dimension; j++) {
                if (i == j) {
                    System.out.printf("%5s", "_");
                    continue;
                }
                if (this.matrix[i][j] == INFINITY) {
                    System.out.printf("%5s", "inf");
                    continue;
                }
                System.out.printf("%5d", this.matrix[i][j]);
            }
            System.out.println("");
        }
        System.out.println("");
    }

    public void EnterMatrix() {
        Scanner scan = new Scanner(System.in);
        while (this.dimension < 1) {
            System.out.print("Input matrix dimension\n>");
            this.dimension = scan.nextInt();
        }
        this.matrix = new int[this.dimension][this.dimension];
        System.out.println("Input matrix items:");
        for (int i = 0; i < this.dimension; i++) {
            for (int j = 0; j < this.dimension; j++) {
                System.out.print(">");
                this.matrix[i][j] = scan.nextInt();
                if (this.matrix[i][j] == EMPTY_ITEM)
                    this.matrix[i][j] = INFINITY;
            }
        }
        scan.close();
    }

    public void DijkstraAlgorithm() {
        System.out.println("Starting Dijkstra algorithm...");
        this.distance = new int[this.dimension];
        this.prevPaths = new int[this.dimension];
        int[] visited = new int[this.dimension];
        int min;
        int nextVertex = 0;
        // First step.
        for (int i = 0; i < this.dimension; i++)
            this.distance[i] = this.matrix[0][i];
        this.distance[0] = 0;
        visited[0] = 1;
        // Step 2-end.
        for (int i = 0; i < this.dimension; i++) {
            min = INFINITY;
            // First, calculate what way to go.
            for (int j = 0; j < this.dimension; j++) {
                if (min > this.distance[j] && visited[j] != 1) {
                    min = this.distance[j];
                    nextVertex = j;
                }
            }
            // Algorithm now is into current vertex.
            visited[nextVertex] = 1;
            // Main behavior in this loop.
            for (int c = 0; c < this.dimension; c++) {
                // If a vertex wasn`t visited yet - count a weight.
                if (visited[c] != 1) {
                    if (min + this.matrix[nextVertex][c] < this.distance[c]) {
                        this.distance[c] = min + matrix[nextVertex][c];
                        this.prevPaths[c] = nextVertex;
                    }
                }
            }
        }
        System.out.println("Ending Dijkstra algorithm...\n");
    }

    public void FulkersonAlgorithm() {
        System.out.println("Starting Fulkerson algorithm...");
        // Get triangle matrix.
        int[][] triangleMatrix = GetTriangleMatrix();
        this.FulkersonMax = new int[this.dimension];
        int[] labels = new int[this.dimension];
        boolean[] visit = new boolean[this.dimension];
        for (int i = 0; i < this.dimension; i++) {
            labels[i] = 0;
            visit[i] = false;
            for (int j = 0; j < this.dimension; j++) {
                if (i != j && triangleMatrix[i][j] == 0)
                    triangleMatrix[i][j] = INFINITY;
            }
        }
        int curr = 0;
        labels[curr] = 0;
        this.FulkersonMax[curr] = 0;
        visit[curr] = true;
        do {
            for (int i = 0; i < this.dimension; i++) {
                if (triangleMatrix[i][curr] != INFINITY) {
                    if (labels[curr] < labels[i] + triangleMatrix[i][curr])
                        labels[curr] = labels[i] + triangleMatrix[i][curr];
                }
            }
            this.FulkersonMax[curr] = labels[curr];
            visit[curr] = true;
            curr++;
        } while (curr != this.dimension);
        System.out.println("Ending Fulkerson algorithm...\n");
    }

    public int[][] GetTriangleMatrix() {
        int[][] triangleMatrix = new int[this.dimension][this.dimension];
        for (int i = 0; i < this.dimension; i++) {
            for (int j = 0; j < this.dimension; j++) {
                triangleMatrix[i][j] = this.matrix[i][j];
            }
        }
        int[] sequence = new int[this.dimension];
        // First, calculate sequence.
        for (int i = 0; i < this.dimension; i++) {
            int curIndex = 0;
            for (int j = 0; j < this.dimension; j++) {
                if (this.matrix[j][i] != INFINITY)
                    curIndex = j + 1;
            }
            sequence[i] = curIndex;
        }
        // Then build a triangular matrix.
        for (int i = 0; i < this.dimension; i++) {
            for (int j = i + 1; j < this.dimension; j++) {
                if (sequence[i] > sequence[j]) {
                    triangleMatrix = Swap(triangleMatrix, i, j);
                    int tmp = sequence[i];
                    sequence[i] = sequence[j];
                    sequence[j] = tmp;
                }
            }
        }
        return (triangleMatrix);
    }

    private int[][] Swap(int[][] triangleMatrix, int a, int b) {
        int[][] toRet = new int[this.dimension][this.dimension];
        for (int i = 0; i < this.dimension; i++) {
            for (int j = 0; j < this.dimension; j++) {
                toRet[i][j] = triangleMatrix[i][j];
            }
        }
        for (int i = 0; i < this.dimension; i++) {
            int tmp = toRet[i][a];
            toRet[i][a] = toRet[i][b];
            toRet[i][b] = tmp;
        }
        for (int j = 0; j < this.dimension; j++) {
            int tmp = toRet[a][j];
            toRet[a][j] = toRet[b][j];
            toRet[b][j] = tmp;
        }
        return (toRet);
    }

    public void PrintMinDistances() {
        System.out.println("Calculated distances:");
        for (int i = 0; i < this.dimension; i++) {
            System.out.println("From [1] to [" + (i + 1) + "] : " + this.distance[i]);
        }
        System.out.println("");
    }

    public void PrintMinPaths() {
        System.out.println("Calculated minimal paths:");
        for (int i = 0; i < this.dimension; i++) {
            System.out.print("Min path to " + (i + 1) + ": ");
            System.out.print((i + 1));
            int j = i;
            do {
                j = this.prevPaths[j];
                System.out.print("<-" + (j + 1));
            } while (j != 0);
            System.out.println("");
        }
        System.out.println("");
    }

    public void PrintMaxDistances() {
        System.out.println("Calculated maximal paths:");
        for (int i = 0; i < this.FulkersonMax.length; i++) {
            System.out.println("Max path to " + (i + 1) + ": " + this.FulkersonMax[i]);
        }
        System.out.println("");
    }
}
