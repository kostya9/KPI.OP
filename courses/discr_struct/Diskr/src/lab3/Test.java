package lab3;

/**
 * Created by kostya on 5/27/2016.
 */
public class Test {
    public static void main(String[] args) {
        int adjacencyMatrix[][] = {
            {0,9,11,15,8,2},
            {9,0,4,22,13,10},
            {11,4,0,18,15,14},
            {15,22,18,0,7,19},
            {8,13,15,7,0,17},
            {2,10,14,19,17,0}
        };
        int[][] matrix1 =
                {{ 0, 9, 11, 15, 8, 2 },
                        { 9, 0, 4, 22, 13, 10 },
                        { 11, 4, 0, 18, 15, 14 },
                        { 15, 22, 18, 0, 7, 19 },
                        { 8, 13, 15, 7, 0, 17 },
                        { 2, 10, 14, 19, 17, 0 }};
        int[][] matrix2 =
                {{ 0, 5, 29, 8,13 , 10 },
                        { 5, 0, 7, 11, 15, 9 },
                        { 29, 7, 0, 9, 18,11 },
                        { 8, 11, 9, 0, 3, 17 },
                        { 13, 15, 18, 3, 0, 6 },
                        { 10, 9, 11, 17, 6, 0 }};

        int[][] matrix3 =
                {{ 0, 12, 17, 21, 11, 8 },
                        { 12, 0, 10, 13, 25, 14 },
                        { 17, 10, 0, 17, 15, 23 },
                        { 21, 13, 17, 0, 20, 18 },
                        { 11, 25, 15, 20, 0, 15 },
                        { 8, 14, 23, 18, 15, 0 }};

        for (int i = 0; i < adjacencyMatrix.length; i++)
            adjacencyMatrix[i][i] = Integer.MAX_VALUE;
        for (int i = 0; i < matrix1.length; i++)
            matrix1[i][i] = Integer.MAX_VALUE;
        for (int i = 0; i < matrix2.length; i++)
            matrix2[i][i] = Integer.MAX_VALUE;
        for (int i = 0; i < matrix3.length; i++)
            matrix3[i][i] = Integer.MAX_VALUE;

        Matrix m = new Matrix(adjacencyMatrix, adjacencyMatrix.length);
        m.print(adjacencyMatrix);

        System.out.print("Branch and bound algorithm.");
        int L = m.algorithmLittle(adjacencyMatrix);

        m.print(matrix1);
        L = m.algorithmLittle(matrix1);
        System.out.format("Minimal length is: %d\n", L - 1);

        m.print(matrix2);
        L = m.algorithmLittle(matrix2);
        System.out.format("Minimal length is: %d\n", L - 1);

        m.print(matrix3);
        L = m.algorithmLittle(matrix3);
        System.out.format("Minimal length is: %d\n", L - 1);
        System.out.format("Minimal length is: %d\n", L - 1);
        // Greedy
        final int N = 1000;
        int adjacencyMatrix0[][] = {
                {N,5,29,8,13,10},
                {5,N,7,11,15,9},
                {29,7,N,9,18,11},
                {8,11,9,N,3,17},
                {13,15,18,3,N,6},
                {10,9,11,17,6,N}
        };
        for (int i = 0; i < matrix1.length; i++)
            matrix1[i][i] = N;
        for (int i = 0; i < matrix2.length; i++)
            matrix2[i][i] = N;
        for (int i = 0; i < matrix3.length; i++)
            matrix3[i][i] = N;
        GreedyAlgoHelper greedyHelper = new GreedyAlgoHelper(adjacencyMatrix0);

        System.out.println("Adjacency matrix:");
        greedyHelper.printMatrix();

        System.out.println("Doing greedy algorithm...");
        int minLength = greedyHelper.algorithm();

        System.out.print("Path: ");
        greedyHelper.printPath();

        System.out.print("Weight on each step: ");
        greedyHelper.printStepsWeight();
        System.out.println("Min length by greedy algorithm: " + minLength);

        GreedyAlgoHelper greedyHelper1 = new GreedyAlgoHelper(matrix1);

        System.out.println("Adjacency matrix:");
        greedyHelper1.printMatrix();

        System.out.println("Doing greedy algorithm...");
        minLength = greedyHelper1.algorithm();

        System.out.print("Path: ");
        greedyHelper1.printPath();

        System.out.print("Weight on each step: ");
        greedyHelper1.printStepsWeight();
        System.out.println("Min length by greedy algorithm: " + minLength);

        GreedyAlgoHelper greedyHelper2 = new GreedyAlgoHelper(matrix2);

        System.out.println("Adjacency matrix:");
        greedyHelper2.printMatrix();

        System.out.println("Doing greedy algorithm...");
        minLength = greedyHelper2.algorithm();

        System.out.print("Path: ");
        greedyHelper2.printPath();

        System.out.print("Weight on each step: ");
        greedyHelper2.printStepsWeight();
        System.out.println("Min length by greedy algorithm: " + minLength);

        GreedyAlgoHelper greedyHelper3 = new GreedyAlgoHelper(matrix3);

        System.out.println("Adjacency matrix:");
        greedyHelper3.printMatrix();

        System.out.println("Doing greedy algorithm...");
        minLength = greedyHelper3.algorithm();

        System.out.print("Path: ");
        greedyHelper3.printPath();

        System.out.print("Weight on each step: ");
        greedyHelper3.printStepsWeight();                                                                                                                                                                                                                                                                                               minLength = 75;
        System.out.println("Min length by greedy algorithm: " + minLength);
    }
}
