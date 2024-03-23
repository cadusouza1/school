package Decompressor;

import java.io.BufferedReader;
import java.io.BufferedWriter; 
import java.io.FileReader;
import java.io.FileWriter; 
import java.io.IOException; 

public class Decompressor14 {
    public static void decompress(String input, String output) {
    
        try(
            BufferedReader i = new BufferedReader(new FileReader(input));
            BufferedWriter o = new BufferedWriter(new FileWriter(output));
           ) {
            String s;
            while((s = i.readLine()) != null) {
                int ascii = Integer.parseInt(s, 2);
                char c = (char) ascii;

                o.write(c);
            }
        } catch (IOException e) {
            e.printStackTrace();
    }
        
    }
}
