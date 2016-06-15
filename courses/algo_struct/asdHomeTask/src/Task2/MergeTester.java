package Task2;

import java.io.*;
import java.nio.file.Files;
import java.util.IntSummaryStatistics;
import java.util.LinkedList;
import java.util.List;
import MyPlot.MyDataSet;
/**
 * Created by kostya on 6/13/2016.
 */
public class MergeTester {
    List<Integer> lengths;
    List<Double> timeTwoWayMerge;
    List<Double> timeInPlaceMerge;
    final String SERIALIZE_FILENAME = "statsMerge.txt";
    MergeTester(){
        lengths = new LinkedList<Integer>();
        timeInPlaceMerge = new LinkedList<Double>();
        timeTwoWayMerge = new LinkedList<Double>();
    }
    void merge(int step, int last){
        for(int length = 1; length < last; length+=step){
            int first[] = new int[length];
            int second[] = new int[length];

            //Filling
            for(int i = 0; i < length; i++){
                first[i] = 5*i + 1;
                second[i] = 2*i + (i%3) * (i/100);
            }

            //Merging
            lengths.add(length);
            long tStart = System.nanoTime();
            int[] result1 = Merge.twoWayMerge(first, second);
            long tEnd = System.nanoTime();
            long delta = tEnd - tStart;
            double deltaSecondsTwoWay = delta / (double) (1e6);
            timeTwoWayMerge.add(deltaSecondsTwoWay);

            tStart = System.nanoTime();
            int[] result2 = Merge.abstractInPlaceMerge(first, second);
            tEnd = System.nanoTime();
            delta = tEnd - tStart;
            double deltaSecondsInPlace = delta / (double) (1e6);
            timeInPlaceMerge.add(deltaSecondsInPlace);

            System.out.format("Merged %d elements two-way vs in-place : %.4f vs %.4f\n", length, deltaSecondsTwoWay, deltaSecondsInPlace);
        }
    }
    void serialize(String fileName) throws FileNotFoundException, UnsupportedEncodingException {
        PrintWriter writer = new PrintWriter(fileName, "UTF-8");
        for(int i = 0; i < lengths.size(); i++)
        {
            writer.format("%d %f %f\n", lengths.get(i), timeTwoWayMerge.get(i), timeInPlaceMerge.get(i));
        }
        writer.close();
    }
    void deserialize(String fileName) throws IOException {
        File file = new File(fileName);
        Files.lines(file.toPath()).forEach(
                (String s) ->{
                    String[] numbers = s.split(" ");
                    lengths.add(new Integer(numbers[0]));
                    timeTwoWayMerge.add(new Double(numbers[1]));
                    timeInPlaceMerge.add(new Double(numbers[2]));
                }
        );
    }

    List<MyDataSet> getDataSets(){
        MyDataSet setTwoWay = new MyDataSet(lengths, timeTwoWayMerge, "Two-way merge");
        MyDataSet setInPlace = new MyDataSet(lengths, timeInPlaceMerge, "Abstract in place merge");
        List<MyDataSet> sets = new LinkedList<>();
        sets.add(setTwoWay);
        sets.add(setInPlace);
        return sets;
    }

}
