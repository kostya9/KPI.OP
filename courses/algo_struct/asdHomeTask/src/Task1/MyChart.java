package Task1;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.*;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.DefaultCategoryItemRenderer;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.ui.ApplicationFrame;

import java.awt.*;
import java.util.List;

public class MyChart extends ApplicationFrame{
    public MyChart(List<MyDataSet> mySets)
    {
        super("MyChart");
        DefaultCategoryDataset dataSet = createDataset(mySets);
        String chartTitle = "Sorting arrays using Heap Sort";
        JFreeChart lineChart = ChartFactory.createLineChart(chartTitle,
                "Length", "Time",
                dataSet,
                PlotOrientation.VERTICAL,
                true,true,false);
        ChartPanel chartPanel = new ChartPanel( lineChart );
        /*CategoryPlot plot = lineChart.getCategoryPlot();
        CategoryAxis axis = plot.getDomainAxis();
        int max = getMaxLength(mySets.get(0));*/
        chartPanel.setPreferredSize( new java.awt.Dimension( 560 , 367 ) );
        setContentPane( chartPanel );

    }

    private int getMaxLength(MyDataSet myDataSet) {
        int max = Integer.MIN_VALUE;
        List<Integer> length = myDataSet.getLength();
        for(int i = 0; i < length.size(); i++)
        {
            if(length.get(i) > max)
                max = length.get(i);
        }
        return max;
    }

    private DefaultCategoryDataset createDataset(List<MyDataSet> sets) {
        DefaultCategoryDataset dataSet = new DefaultCategoryDataset();
        for(MyDataSet set : sets)
        {
            List<Double> time = set.getTime();
            List<Integer> length = set.getLength();
            assert(length.size() == time.size());
            for(int i = 0; i < length.size(); i++)
            {
                dataSet.addValue(time.get(i), set.getName(), length.get(i));
            }
        }

        return dataSet;
    }

}
