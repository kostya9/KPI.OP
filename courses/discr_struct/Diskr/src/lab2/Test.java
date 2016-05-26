
package lab2;

public class Test {
    public static void main(String[] args) {
        int[][] matrix = {
                { 0, 10, 8, 7, 18, 0 },
                { 1, 0, 11, 0, 0, 0 },
                { 0, 2, 0, 3, 0, 17 },
                { 0, 10, 12, 0, 6, 0 },
                { 0, 7, 8, 0, 0, 11 },
                { 3, 0, 0, 4, 0, 2 }
        };


        int dimension = matrix[0].length;
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (matrix[i][j] == 0)
                    matrix[i][j] = 1000;
            }
        }


        // Algorithms algoHelper = new Algorithms();
        // algoHelper.EnterMatrix();

        System.out.println("Start of the program.\n");
        Matrix algoHelper = new Matrix(matrix, dimension);
        algoHelper.PrintMainMatrix();
        algoHelper.DijkstraAlgorithm();
        algoHelper.PrintMinDistances();
        algoHelper.PrintMinPaths();
        algoHelper.FulkersonAlgorithm();
        algoHelper.PrintMaxDistances();
        System.out.println("End of the program.");
    }
}
