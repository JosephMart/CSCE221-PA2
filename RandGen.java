import java.io.File;
import java.io.IOException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

import java.io.BufferedWriter;
import java.io.FileWriter;

public class RandGen {
    
    private static interface Num {
        int get(int i);
    }

    public static void main(String[] args) {
        Random r = new Random();
        int max = Short.MAX_VALUE;
        int min = Short.MIN_VALUE;
        int del = max - min;
        int count = 10;
        int pow = 5; //maximum power of 10
        for(int i = 1; i <= pow; i++) {
            count *= 10;
            int[] nums = new int[count];
            int start = -(count / 2);
            for(int j = 0; j < count; j++) {
                nums[j] = start++;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_increasing");
            for(int j = 0; j < count; j++) {
                nums[j] = start--;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_decreasing");
            for(int j = 0; j < count; j++) {
                int dest = r.nextInt(count);
                int temp = nums[dest];
                nums[dest] = nums[j];
                nums[j] = temp;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_random");
        }
    }
    
    private static void out(int n, Num supplier, String s) {
        File f = new File("./input/");
        f = new File(f, s + ".txt");
        String[] values = new String[n + 1];
        values[0] = Integer.toString(n);
        for(int i = 1; i <= n; i++) {
            values[i] =  " " + Integer.toString(supplier.get(i - 1));
        }
        
        try {
            writeFileLines(f, values);
        } catch (IOException ex) {
            Logger.getLogger(RandGen.class.getName()).log(Level.SEVERE, "oops: " + s, ex);
        }
    }
    
    public static void writeFileLines(File file, String[] lines) throws IOException {
        BufferedWriter out = new BufferedWriter(new FileWriter(file, false));
        for(String s : lines) {
            out.write(s);
        }
        out.close();
    }
}