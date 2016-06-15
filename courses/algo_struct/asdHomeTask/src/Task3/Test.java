package Task3;

import MyPlot.MyChart;
import MyPlot.MyDataSet;
import org.jfree.ui.RefineryUtilities;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.List;

/**
 * Created by kostya on 6/14/2016.
 */
public class Test {
    public static void main(String[] args) {
        DictionaryTester tester = new DictionaryTester();
        tester.testAverageCase((int)1e3, (int)1e7);
        try {
            tester.serialize("100MillionFindAverageCase.txt");
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        /*try {
            tester.deserialize("100MillionFindWorstCase.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }*/
        List<MyDataSet> sets = tester.getDataSets();
        MyChart chart = new MyChart(sets, "Dictionary find testing(average case)");
        chart.pack();
        RefineryUtilities.centerFrameOnScreen(chart);
        chart.setVisible(true);
    }
    static void testDictArray(){
        DictionarySortedArray<Integer, String> dict = new DictionarySortedArray<Integer, String>();
        dict.insert(100, "Hey");
        dict.insert(101, "Hey1");
        dict.insert(99, "Hey-1");
        dict.insert(99, "Hey-1temp");
        System.out.println(dict.get(99));
    }
    static void testDictBST(){
        DictionaryBST<Integer, String> dict = new DictionaryBST<Integer, String>();
        dict.insert(100, "Hey");
        dict.insert(101, "Hey1");
        dict.insert(99, "Hey-1");
        dict.insert(99, "Hey-1temp");
        System.out.println(dict.get(100));
    }
}
