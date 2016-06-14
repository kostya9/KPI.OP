package Task3;

/**
 * Created by kostya on 6/14/2016.
 */
public class DictionarySortedArray<T extends Comparable, E> {
    private Entry<T, E>[] arr;
    private int count;
    final private int iNOTFOUND = -1;

    private class Entry<T, E>{
        private T key;
        private E value;

        Entry(T key, E value) {
            this.key = key;
            this.value = value;
        }

        public T getKey() {
            return key;
        }

        public E getValue() {
            return value;
        }
    }

    public DictionarySortedArray(){
        count = 0;
        arr = (Entry<T, E>[]) new Entry[8];
    }

    public void buildWorstCase(int length){
        this.arr = new Entry[length + 1];
        for(int i = 0; i < length; i++){
            arr[i] = new Entry<T, E>((T)(Object)i, (E)(Object)i);
        }
        this.count = length;
    }
    public E insert(T key, E value){

        // If current array will be full - increase the count
        if(count == arr.length - 2)
        {
            Entry<T, E>[] arr_new = (Entry<T, E>[])new Entry[arr.length * 2];
            System.arraycopy(arr, 0, arr_new, 0, arr.length);
            arr = arr_new;
        }

        int j = 0;
        int pos = 0;

        while(j < count && arr[j].getKey().compareTo(key) < 0)
            j++;

        if(j == count)
        {
            arr[j] = new Entry<T, E>(key, value);
            count++;
            return null;
        }
        // Replace existing and return previous
        if(arr[j].getKey().equals(key))
        {
            E retValue = arr[j].getValue();
            arr[j] = new Entry<T, E>(key, value);
            return retValue;
        }

        // Shift right
        for(int i = count - 1; i >= j; i--)
        {
            arr[i + 1] = arr[i];
        }
        arr[j] = new Entry<T, E>(key, value);
        count++;

        // No replacements
        return null;
    }

    private int getIndex(T key){
        int left = 0;
        int right = count - 1;

        do{
            int mid = (right + left)/2;
            if(key.compareTo(arr[mid].getKey()) > 0)
            {
                left = mid + 1;
            }
            else if(key.compareTo(arr[mid].getKey()) < 0)
            {
                right = mid - 1;
            }
            else
            {
                return mid;
            }
        } while(left <= right);

        return iNOTFOUND;
    }

    public E get(T key){
        int index = getIndex(key);

        if(index == iNOTFOUND)
            return null;

        Entry<T, E> e = arr[index];

        return e.getValue();
    }

    public E remove(T key){
        int index = getIndex(key);

        if(index == iNOTFOUND)
            return null;

        E retValue = arr[index].getValue();

        // Shift left
        for(int i = index; i < count - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        count--;
        return retValue;
    }

    public int getCount(){
        return count;
    }

}
