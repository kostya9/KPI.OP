package Task2;

import MyPlot.MyChart;
import MyPlot.MyDataSet;
import Task1.HeapSortTester;
import org.jfree.ui.ArrowPanel;
import org.jfree.ui.RefineryUtilities;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.List;

/**
 * Created by kostya on 6/13/2016.
 */
public class Test {
    public static void main(String[] args) {
        //generateAndSerialize();
        MergeTester tester = new MergeTester();
        try {
            tester.deserialize("10MillionMerge.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
        List<MyDataSet> sets = tester.getDataSets();
        MyChart chart = new MyChart(sets, "Merge testing");
        chart.pack();
        RefineryUtilities.centerFrameOnScreen(chart);
        chart.setVisible(true);
    }
    static void generateAndSerialize(){
        MergeTester tester = new MergeTester();
        tester.merge((int)1e3, (int)1e7);
        try {
            tester.serialize("10MillionMerge.txt");
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
    static void testConsole(){
        int length = 10;
        int first[] = new int[length];
        int second[] = new int[length];
        //Filling
        for(int i = 0; i < length; i++){
            first[i] = 5*i + 1;
            second[i] = 2*i + (i%3) * (i/100);
        }
        String firstArray = Arrays.toString(first);
        String secondArray = Arrays.toString(second);
        System.out.println(firstArray);
        System.out.println("+");
        System.out.println(secondArray);
        System.out.println("=");
        int[] result = Merge.abstractInPlaceMerge(first, second);
        int[] result1 = Merge.twoWayMerge(first, second);
        System.out.println(Arrays.toString(result));
        System.out.println("OR");
        System.out.println(Arrays.toString(result1));
    }
}
