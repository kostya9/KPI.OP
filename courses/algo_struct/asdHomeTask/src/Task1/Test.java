package Task1;

import MyPlot.MyChart;
import MyPlot.MyDataSet;
import org.jfree.ui.RefineryUtilities;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.*;

/**
 * Created by kostya on 6/12/2016.
 */
public class Test {

    public static void main(String[] args) {
        String chartTitle = "Sorting arrays using Heap Sort";
        MyDataSet random = getDataSetFromFile("stats10MillionRandom.txt");
        MyDataSet sorted = getDataSetFromFile("stats10MillionSorted.txt");
        MyDataSet reversed = getDataSetFromFile("stats10MillionReversed.txt");
        LinkedList<MyDataSet> dataList = new LinkedList<MyDataSet>();
        dataList.add(random);
        dataList.add(sorted);
        dataList.add(reversed);
        /*try {
            tester.deserialize();
        } catch (IOException e) {
            e.printStackTrace();
        }/**/
        MyChart chart = new MyChart(dataList, chartTitle);
        chart.pack();
        RefineryUtilities.centerFrameOnScreen(chart);
        chart.setVisible(true);
        //System.out.print(Arrays.toString(arr));
    }
    static HeapSortTester generateAndSerialize(){
        HeapSortTester tester = new HeapSortTester();
        int step = (int)1e4;
        tester.sortRandomArrays(step, (int)1e7);
        try {
            tester.serialize();
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return tester;
    }
    static MyDataSet getDataSetFromFile(String fileName){
        HeapSortTester tester = new HeapSortTester();
        try {
            tester.deserialize(fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new MyDataSet(tester.getLengths(), tester.getTime(), fileName);
    }
}
