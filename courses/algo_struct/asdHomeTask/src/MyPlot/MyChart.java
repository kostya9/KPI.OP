package MyPlot;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.ui.ApplicationFrame;

import java.util.List;

public class MyChart extends ApplicationFrame{
    public MyChart(List<MyDataSet> mySets, String title)
    {
        super("MyPlot");
        DefaultCategoryDataset dataSet = createDataset(mySets);

        JFreeChart lineChart = ChartFactory.createLineChart(title,
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
