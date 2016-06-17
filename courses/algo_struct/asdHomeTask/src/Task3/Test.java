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
        generateAndSerialize();
        DictionaryTester testerBest = new DictionaryTester();
        DictionaryTester testerWorst = new DictionaryTester();
        DictionaryTester testerAverage = new DictionaryTester();
        try {
            testerBest.deserialize("10MillionFindBestCase.txt");
            testerWorst.deserialize("10MillionFindWorstCase.txt");
            testerAverage.deserialize("10MillionFindAverageCase.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
        List<MyDataSet> setsBest = testerBest.getDataSets();
        List<MyDataSet> setsWorst = testerWorst.getDataSets();
        List<MyDataSet> setsAverage = testerAverage.getDataSets();
        MyChart chartBest = new MyChart(setsBest, "Dictionary find testing(best case)");
        chartBest.pack();
        RefineryUtilities.centerFrameOnScreen(chartBest);
        chartBest.setVisible(true);
        MyChart chartWorst = new MyChart(setsWorst, "Dictionary find testing(worst case)");
        chartWorst.pack();
        RefineryUtilities.centerFrameOnScreen(chartWorst);
        chartWorst.setVisible(true);
        MyChart chartAverage = new MyChart(setsAverage, "Dictionary find testing(average case)");
        chartAverage.pack();
        RefineryUtilities.centerFrameOnScreen(chartAverage);
        chartAverage.setVisible(true);
    }
    static void generateAndSerialize(){
        //DictionaryTester testerBest = new DictionaryTester();
        //DictionaryTester testerWorst = new DictionaryTester();
        DictionaryTester testerAverage = new DictionaryTester();
        //testerBest.testBestCase((int)1e4, (int)1e7);
        //testerWorst.testWorstCase((int)1e4, (int)1e7);
        testerAverage.testAverageCase((int)1e4, (int)1e7);
        try {
            //testerBest.serialize("10MillionFindBestCase.txt");
            //testerWorst.serialize("10MillionFindWorstCase.txt");
            testerAverage.serialize("10MillionFindAverageCase.txt");
        }
        catch (Exception e){
            e.printStackTrace();
        }
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
