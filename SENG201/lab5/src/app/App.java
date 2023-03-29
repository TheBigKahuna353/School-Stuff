package app;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class App {


    public int divideBy(String a, Integer b) { 

        return Integer.parseInt(a) / b; 
    
    }

    public List<Integer> listDivide(List<String> values, Integer dividend) {
        // Your code goes here
        List<Integer> result = new ArrayList<>();
        for (String value : values) {
            try {
                result.add(divideBy(value, dividend));
            } catch (Exception e) {
                System.out.println(e);
            }
        }
        return result;
    }

    public Integer addLastTwo(ArrayList<Integer> values) throws ArrayProcessingException {
        try {
            return values.get(values.size() - 1) + values.get(values.size() - 2);
        } catch (Exception e) {
            throw new ArrayProcessingException(e);
        }
    }

    void test() {
        ArrayList<Integer> l = new ArrayList<>(Arrays.asList(1, 2));

        try {
            System.out.println(addLastTwo(l));
        } catch (ArrayProcessingException e) {
            System.out.println(e.getMessage());
        }

         	

        ArrayList<Integer> h = new ArrayList<>(Arrays.asList(1));

        try {
            System.out.println(addLastTwo(h));
        } catch (ArrayProcessingException e) {
            System.out.println(e.getCause() instanceof IndexOutOfBoundsException);
        }
    }

    public static void main(String[] args) throws Exception {
        App app = new App();
        app.test();
    }
}
