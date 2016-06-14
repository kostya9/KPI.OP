package MyPlot;

import java.util.List;

/**
 * Created by kostya on 6/13/2016.
 */
public class MyDataSet{
    List<Double> time;
    List<Integer> length;
    String name;

    public MyDataSet(List<Integer> length, List<Double> time, String name) {
        this.length = length;
        this.time = time;
        this.name = name;
    }

    public List<Double> getTime() {
        return time;
    }

    public List<Integer> getLength() {
        return length;
    }

    public String getName() {
        return name;
    }
}
