package Task1;

import java.io.*;
import java.nio.file.Files;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

/**
 * Created by kostya on 6/13/2016.
 */
public class HeapSortTester {
    List<Double> time;
    List<Integer> lengths;
    final String SERIALIZE_FILENAME = "stats.txt";
    HeapSortTester()
    {
        time = new LinkedList<>();
        lengths = new LinkedList<>();
    }
    void sortReversedArrays(int step, int last)
    {
        for(int length = 1; length < last && length > 0; length += step) {
            int[] arr = new int[length];

            for (int i = 0; i < length; i++) {
                arr[i] = length - i;
            }
            sortAndRecord(length, arr);
        }
    }
    void sortSortedArrays(int step, int last)
    {
        for(int length = 1; length < last && length > 0; length += step) {
            int[] arr = new int[length];

            for (int i = 0; i < length; i++) {
                arr[i] = i;
            }
            sortAndRecord(length, arr);
        }
    }

    void sortRandomArrays(int step, int last)
    {
        for(int length = 1; length < last && length > 0; length += step) {
            int[] arr = new int[length];
            Random r = new Random();

            for (int i = 0; i < length; i++) {
                arr[i] = r.nextInt(length * 10);
            }
            sortAndRecord(length, arr);
        }
    }

    void sortAlmostSortedArrays(int step, int last){
        for(int length = 1; length < last && length > 0; length += step) {
            int[] arr = new int[length];
            Random r = new Random();
            for (int i = 0; i < length; i++) {
                arr[i] = i;
            }
            for(int i = 0; i < length/40; i++){
                HeapSort.swap(r.nextInt(length), r.nextInt(length), arr);
            }
            sortAndRecord(length, arr);
        }
    }
    private void sortAndRecord(int length, int[] arr) {
        long tStart = System.nanoTime();
        HeapSort.sort(arr);
        long tEnd = System.nanoTime();
        long delta = tEnd - tStart;
        double deltaSeconds = delta / (double) (1e6);
        System.out.format("Elapsed %.4f milliseconds for sorting %d elements\n", deltaSeconds, length);
        time.add(deltaSeconds);
        lengths.add(length);
    }
    void serialize() throws FileNotFoundException, UnsupportedEncodingException {
        serialize(SERIALIZE_FILENAME);
    }
    void serialize(String fileName) throws FileNotFoundException, UnsupportedEncodingException {
        PrintWriter writer = new PrintWriter(fileName, "UTF-8");
        for(int i = 0; i < time.size(); i++)
        {
            writer.format("%d %f\n", lengths.get(i), time.get(i));
        }
        writer.close();
    }
    void deserialize() throws IOException {
        deserialize(SERIALIZE_FILENAME);
    }
    void deserialize(String fileName) throws IOException
    {
        File file = new File(fileName);
        Files.lines(file.toPath()).forEach(
                (String s) ->{
                    String[] numbers = s.split(" ");
                    lengths.add(new Integer(numbers[0]));
                    time.add(new Double(numbers[1]));
                }
        );
    }

    List<Double> getTime(){
        return time;
    }
    List<Integer> getLengths(){
        return lengths;
    }
}
