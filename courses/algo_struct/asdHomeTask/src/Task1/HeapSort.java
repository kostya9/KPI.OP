package Task1;

/**
 * Created by kostya on 6/12/2016.
 */
public class HeapSort {
    private static int getLeftIndex(int arr[], int index) {
        return index * 2 + 1;
    }

    private static int getRightIndex(int arr[], int index) {
        return index * 2 + 2;
    }

    private static void sink(int arr[], int index, int end)
    {
        int left = getLeftIndex(arr, index);
        int right = getRightIndex(arr, index);
        int max = index;

        if(left < end && arr[left] > arr[max])
            max = left;

        if(right < end && arr[right] > arr[max])
            max = right;

        if(max != index)
        {
            swap(index, max, arr);
            sink(arr, max, end);
        }
    }

    static void sort(int arr[])
    {
        // Build Heap
        int length = arr.length;
        int built = length/2;

        for(int i = built; i >= 0; i--)
            sink(arr, i, arr.length);

        //
        for(int i = 1; i < length; i++) {
            swap(0, length - i, arr);
            sink(arr, 0, length - i);
        }

    }

    public static void swap(int index1, int index2, int[] arr)
    {
        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }


}
