package Compressor;

import java.io.BufferedReader;
import java.io.BufferedWriter; 
import java.io.FileReader;
import java.io.FileWriter; 
import java.io.IOException; 


public class Compressor14 {
    public static void compress(String input, String output) {

        try (
            BufferedReader i = new BufferedReader(new FileReader(input));
            BufferedWriter o = new BufferedWriter(new FileWriter(output));
            ) {
            int c;
            while((c = i.read()) != -1) {
                String b = Integer.toBinaryString(c);
                System.out.println((char)c + ": " + b);

                o.write(b);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
