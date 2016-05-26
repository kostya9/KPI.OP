package lab3;
import java.lang.*;
/**
 * Created by kostya on 5/26/2016.
 */
public class Matrix {
    private int dim;
    private int adjMatrix[][];
    private final int INT_MAX = Integer.MAX_VALUE;
    Matrix(int adjMatrix[][], int dim)
    {
        this.adjMatrix = adjMatrix;
        this.dim = dim;
    }
    class Zero{
        public int i;
        public int j;
        public int data = 0;
    }
    int algorithmLittle(int matr[][])
    {
        int n = matr.length;
        int size = n - 1;
        int L = 0;

        while (n > 2)
        {
            // Find minimal element by rows.
            for (int i = 1; i < n; i++)
            {
                int min = INT_MAX;
                for (int j = 1; j < n; j++)
                {
                    if (matr[i][j] < min)
                        min = matr[i][j];
                }
                L += min;
                for (int j = 1; j < n; j++)
                {
                    if (matr[i][j] != INT_MAX)
                        matr[i][j] -= min;
                }
            }
            // Counter for initialization array of Zeros.
            int cnt = 0;
            // Find minimal element by columns.
            for (int i = 1; i < n; i++)
            {
                int min = INT_MAX;
                for (int j = 1; j < n; j++)
                {
                    if (matr[j][i] < min)
                        min = matr[j][i];
                }
                L += min;
                for (int j = 1; j < n; j++)
                {
                    if (matr[j][i] != INT_MAX)
                        matr[j][i] -= min;
                    if (matr[j][i] == 0)
                        cnt++;
                }
            }
            // Initialize array of zeros.
            Zero[] aZero = new Zero[cnt];
            for(int i = 0; i < cnt; i++)
                aZero[i] = new Zero();
            // Fill this array.
            int index = 0;
            for (int i = 1; i < n; i++)
            {
                for (int j = 1; j < n; j++)
                {
                    if (matr[i][j] == 0)
                    {
                        aZero[index].i = i;
                        aZero[index].j = j;
                        index++;
                    }
                }
            }

            // Calculate minimal shit another one time and do all this shit another one time.
            for (index = 0; index < cnt; index++)
            {
                int min = INT_MAX;
                for (int i = 1; i < n; i++)
                {
                    if (aZero[index].i != i && min > matr[i][aZero[index].j])
                        min = matr[i][aZero[index].j];
                }
                aZero[index].data += min;
                min = INT_MAX;
                for (int j = 1; j < n; j++)
                {
                    if (aZero[index].j != j && min > matr[aZero[index].i][j])
                        min = matr[aZero[index].i][j];
                }
                aZero[index].data += min;
            }
            Zero max = aZero[0];
            for (int i = 0; i < cnt; i++)
            {
                if (aZero[i].data > max.data)
                    max = aZero[i];
            }
            n--;

            // Delete unnecessary shit.
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    if (j < max.j && i >= max.i)
                        matr[i][j] = matr[i + 1][j];
                    else if (j >= max.j)
                        if (i < max.i)
                            matr[i][j] = matr[i][j + 1];
                        else
                            matr[i][j] = matr[i + 1][j + 1];
                }

            // Reaarange data array.
            boolean flag = false;
            for (int i = 1; i < n; i++)
            {
                for (int j = 1; j < n; j++)
                {
                    if (matr[i][j] == INT_MAX) break;
                    if (j == n - 1)
                    {
                        int ind = 1;
                        while (!flag)
                        {
                            for (int k = i + 1; k < n; k++)
                            {
                                if (matr[ind][k] == INT_MAX) break;
                                if (k == n - 1)
                                {
                                    matr[i][ind] = INT_MAX;
                                    flag = true;
                                }
                            }
                            ind++;
                            if (ind == n)
                            {
                                matr[i][j] = INT_MAX;
                                flag = true;
                            }
                        }
                    }
                }
                if (flag) break;
            }
        }

        return (L);
    }

    void print(int matr[][])
    {
        int n = matr.length;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matr[i][j] == INT_MAX) {
                    System.out.format("%4c", '_');
                    continue;
                }
                System.out.format("%4d", matr[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }

}
