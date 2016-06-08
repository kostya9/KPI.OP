package lab4;

import jdk.nashorn.internal.codegen.CompilerConstants;

/**
 * Created by kostya on 6/1/2016.
 */
public class PrintTree<T> implements Callable<T> {
    public void onStart()
    {
        System.out.println("\nStarting tree traversal...");
    }

    public void call(T input)
    {
        System.out.print(input.toString());
        System.out.print(" ");
    }
    public void onEnd()
    {
        System.out.println("\nEnded tree traversal.\n");
    }
}
