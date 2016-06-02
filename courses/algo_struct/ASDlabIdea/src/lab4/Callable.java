package lab4;

/**
 * Created by kostya on 6/1/2016.
 */
public interface Callable<T> {
    public void onStart();
    public void call(T input);
    public void onEnd();
}
