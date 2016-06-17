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
        //generateAndSerialize();
        MyDataSet random = getDataSetFromFile("stats10MillionRandom.txt");
        MyDataSet sorted = getDataSetFromFile("stats10MillionSorted.txt");
        MyDataSet reversed = getDataSetFromFile("stats10MillionReversed.txt");
        MyDataSet almostSorted = getDataSetFromFile("stats10millionAlmostSorted.txt");
        LinkedList<MyDataSet> dataList = new LinkedList<MyDataSet>();
        dataList.add(random);
        dataList.add(sorted);
        dataList.add(reversed);
        dataList.add(almostSorted);
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
    static void generateAndSerialize(){
        HeapSortTester random = new HeapSortTester();
        HeapSortTester reversed = new HeapSortTester();
        HeapSortTester sorted = new HeapSortTester();
        HeapSortTester almostSorted = new HeapSortTester();
        almostSorted.sortAlmostSortedArrays((int)1e4, (int)1e7);
        random.sortRandomArrays((int)1e4, (int)1e7);
        reversed.sortReversedArrays((int)1e4, (int)1e7);
        sorted.sortSortedArrays((int)1e4, (int)1e7);
        try {
            almostSorted.serialize("stats10millionAlmostSorted.txt");
            random.serialize("stats10millionRandom.txt");
            reversed.serialize("stats10MillionReversed.txt");
            sorted.serialize("stats10millionSorted.txt");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
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
