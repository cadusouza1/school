package main;

import Compressor.Compressor14;
import Decompressor.Decompressor14;

public class Main {
    public static void main(String args[]) {
        Compressor14.compress("entrada.txt", "saida14.bin");
        Decompressor14.decompress("saida14.bin", "entrada14.txt");
    }
}
