package lab3;
public class GreedyAlgoHelper {
    private int[][] adjacencyMatrix;
    private int[] path;
    private int[] stepsWeight;

    public GreedyAlgoHelper(int[][] adjMatrix) {
        this.adjacencyMatrix = new int[adjMatrix.length][adjMatrix[0].length];
        for (int i = 0; i < adjMatrix.length; i++) {
            for (int j = 0; j < adjMatrix[0].length; j++) {
                this.adjacencyMatrix[i][j] = adjMatrix[i][j];
            }
        }
        path = new int[this.adjacencyMatrix.length + 1];
        stepsWeight = new int[this.adjacencyMatrix.length + 1];
    }

    public int algorithm() {
        int minLength = 0;
        boolean[] visited = new boolean[this.adjacencyMatrix.length];
        int minIndex = 0;
        // For path and stepsWeight array.
        int tempIndex = 0;

        visited[minIndex] = true;
        // Fill info to path and stepsWeight arrays.
        this.path[tempIndex] = minIndex;
        this.stepsWeight[tempIndex] = minLength;
        // An algorithm.
        for (int i = 0; i < this.adjacencyMatrix.length - 1; i++) {
            minLength += this.findMinValue(this.adjacencyMatrix[minIndex], visited);
            minIndex = this.findMinValueIndex(this.adjacencyMatrix[minIndex], visited);
            visited[minIndex] = true;
            this.path[++tempIndex] = minIndex;
            this.stepsWeight[tempIndex] = minLength;
        }
        // Last step - end the loop.
        minLength += this.adjacencyMatrix[minIndex][0];
        // Fill info to path and stepsWeight arrays.
        this.path[++tempIndex] = 0;
        this.stepsWeight[tempIndex] = minLength;

        return (minLength);
    }

    private int findMinValue(int[] arr, boolean[] visited) {
        int firstIndex = 0;
        for (int i = 0; i < visited.length; i++) {
            if (!visited[i]) {
                firstIndex = i;
                break;
            }
        }
        int minValue = arr[firstIndex];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < minValue && !visited[i]) {
                minValue = arr[i];
            }
        }
        return (minValue);
    }

    private int findMinValueIndex(int[] arr, boolean[] visited) {
        int firstIndex = 0;
        for (int i = 0; i < visited.length; i++) {
            if (!visited[i]) {
                firstIndex = i;
                break;
            }
        }
        int minIndex = firstIndex;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < arr[minIndex] && !visited[i]) {
                minIndex = i;
            }
        }
        return (minIndex);
    }

    public void printMatrix() {
        for (int i = 0; i < this.adjacencyMatrix.length; i++) {
            for (int j = 0; j < this.adjacencyMatrix[0].length; j++) {
                if (this.adjacencyMatrix[i][j] == 1000) {
                    System.out.print("_  ");
                    continue;
                }
                System.out.printf("%d  ", this.adjacencyMatrix[i][j]);
            }
            System.out.println("");
        }
        System.out.println("");
    }

    public void printPath() {
        for (int i = 0; i < this.path.length - 1; i++) {
            System.out.print(this.path[i] + 1 + "->");
        }
        System.out.print(this.path[this.path.length - 1] + 1);
        System.out.println("");
    }

    public void printStepsWeight() {
        for (int i = 0; i < this.stepsWeight.length - 1; i++) {
            System.out.print(this.stepsWeight[i] + "->");
        }
        System.out.print(this.stepsWeight[this.stepsWeight.length - 1]);
        System.out.println("");
    }
}
