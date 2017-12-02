/**
 *
 * @author furkan
 */
import java.io.*;
import java.lang.String;
import java.rmi.UnexpectedException;
import java.util.Scanner;
import java.util.HashMap;

@SuppressWarnings("unchecked")
public class BigramMap<T> implements Bigram<T> {
    
    private final int dataType;
    
    private final  HashMap<Integer,T> map;
    
    public BigramMap(int type){
        dataType = type;
        this.map = new HashMap();
    }
    
    @Override
    public  void readFile(String name) throws IOException
    {    
        Scanner input = null;
        try{
            input = new Scanner(new File(name)); 
        }
        catch(FileNotFoundException e){
            System.out.println("Dosya açılamadı !");
        } 
        
        if(dataType == 1)
        {   
            Integer a,i=0;
            while(input.hasNext())
            {   
                if (input.hasNextInt()) 
                {
                    a = input.nextInt();
                    
                    map.put(i, (T) a);
                    ++i;
                }
                else
                    throw new UnexpectedException("Farklı tiplerde veri var");
                
            }
            input.close();
        }
        else if(dataType == 2)
        {
            String a;
            int i=0;
            while(input.hasNext())
            {   
                if (input.hasNext()) {
                    
                    a = input.next();
                    map.put(i, (T) a);
                    ++i;
                }
                else
                    throw new UnexpectedException("Farklı tiplerde veri var");
                
            }
            input.close();
        }    
        else    
        {
            String text;
            int i=0;
            while(input.hasNext())
            {   
                text = input.next();
                try{
                    Double num = Double.parseDouble(text);
                    map.put(i, (T) num);
                    ++i;
                }
                catch(NumberFormatException e){
                    throw new UnexpectedException("Farklı tiplerde veri var");
                }
                
            }
            input.close();
        }
        
        if(map.size() <=1)
            throw new UnexpectedException("Bigram olabilecek sayıda(2) yeterli"
                                                        + "  veri bulunamadı.");
    }
    
    @Override
    public  int numGrams()
    {
        return map.size()-1;
    }
    
    @Override
    public  int numOfGrams(T first,T second)
    {
        int number=0;
        
        for(int i=0;i<map.size()-1;++i) 
            if((map.get(i).equals(first)) && (map.get(i+1).equals(second)))
                number++; //istenilen Bigramın kaç kez tekrarlandığı bulundu
        
        return number;
    }
    
    @Override
    public  String toString()
    {
        T arr[][]=  (T[][])new Object[map.size()-1][2];;
        
        for(int i=0;i< map.size()-1;++i)
        {    
            arr[i][0]= map.get(i); // bigramlar 2 dimensional vector'de tutuldu.
            arr[i][1]= map.get(i+1);
        }

        int repeat[]=new int[map.size()-1];

        for(int i=0; i<map.size()-1;++i)
            repeat[i]= numOfGrams(arr[i][0],arr[i][1]);
            // Bigram larla aynı index te , tekrar sayıları tutuldu

        int index[]= new int[map.size()-1];

        for(int i=0;i<map.size()-1;++i)
            index[i]=i;

        for(int i=0;i<map.size()-2;++i)    
        {                   //tekrar sayısına göre index bazlı sıralama yapıldı
            for(int j=i+1;j<map.size()-1;++j)
            {
                int temp;

                if(repeat[index[i]] < repeat[index[j]])
                {
                    temp=index[i];
                    index[i]=index[j];
                    index[j]=temp;
                }    
            }    
        }    
        String a=null;
        for(int i=0; i<map.size()-1;++i)
        {
            boolean type=true;

            for(int k=0;k<i;k++)
            {   // değerin önceden print edilip edilmediğinin kontrolü 
                if( arr[index[k]][0].equals(arr[index[i]][0]) && 
                                      arr[index[k]][1].equals(arr[index[i]][1]))
                {    
                    type=false;
                    k=i;
                }
                else
                    type=true;
            }
            
            if(type)
            {    
                if(i==0)
                    a=arr[index[i]][0]+ " , "+ arr[index[i]][1]+"  repeat: "
                                                        +repeat[index[i]]+"\n";
                else
                    a+=arr[index[i]][0]+ " , "+ arr[index[i]][1]+"  repeat: "
                                                        +repeat[index[i]]+"\n";
            }
       }
        
       return a;
    }

} // end of class

