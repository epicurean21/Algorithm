package main;

import java.io.*;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int count = 1;
        String input = br.readLine();
        for(int i = 0; i < input.length(); i++) {
            if(input.charAt(i) == ' ')
                count++;
        }
        if(input.charAt(0) == ' ')
            count--;
        if(input.charAt(input.length() -1)  == ' ')
            count--;
        System.out.println(count);
    }
}