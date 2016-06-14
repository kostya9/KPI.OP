package Task2;

import java.util.Arrays;

/**
 * Created by kostya on 6/13/2016.
 */
public class Merge {
    static int[] twoWayMerge(int[] first, int[] second)
    {
        int iFirst = 0;
        int iSecond = 0;
        int iResult = 0;
        int[] result = new int[first.length + second.length];
        while(iFirst < first.length && iSecond < second.length)
        {
            if(first[iFirst] < second[iSecond])
            {
                result[iResult] = first[iFirst];
                iFirst++;
                iResult++;
            }
            else
            {
                result[iResult] = second[iSecond];
                iResult++;
                iSecond++;
            }
        }

        // Copy remaining.
        // One array was fully processed and some elements left in the second
        System.arraycopy(first, iFirst, result, iResult, first.length - iFirst);
        System.arraycopy(second, iSecond, result, iResult, second.length - iSecond);
        return result;
    }

    static int[] abstractInPlaceMerge(int[] first, int[] second)
    {
        int length = first.length + second.length;
        int[] result = new int[length];
        int[] aux = new int[length];

        System.arraycopy(first, 0, aux, 0, first.length);
        //Backwards copy
        for(int i = 0; i < second.length; i++){
            aux[length - 1 - i] = second[i];
        }

        int i = 0;
        int j = length - 1;
        for(int k = 0; k < aux.length; k++)
        {
            if(aux[j] < aux[i]) {
                result[k] = aux[j];
                j--;
            }
            else
            {
                result[k] = aux[i];
                i++;
            }
        }
        return result;
    }


}
