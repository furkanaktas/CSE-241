/**
 *
 * @author furkan
 */
//import java.lang.String;
import java.io.*;
import java.rmi.UnexpectedException;
import java.lang.Exception;
public interface Bigram<T> {
    
    
    public abstract void readFile(String name) throws IOException;
    public abstract int numGrams();
    public abstract int numOfGrams(T a,T b);
    
    @Override
    public abstract String toString();
}


