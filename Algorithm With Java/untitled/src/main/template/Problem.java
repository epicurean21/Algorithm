package main.template;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class Problem {
    static int T;
    static int size_a;
    static int size_b;
    static int[] a;
    static int[] b;

    public static void main(String[] args) throws Exception {
        input();
        print();
    }

    static void input() throws Exception {
        /**
         * T = 5
         * a = 1 2 3 4
         * b = 5 6 7
         */
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine()); // T

        T = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine()); // size_a
        size_a = Integer.parseInt(st.nextToken());

        a = new int[size_a];

        st = new StringTokenizer(br.readLine()); // input a
        for (int i = 0; i < size_a; i++) {
            a[i] = Integer.parseInt(st.nextToken());
        }

        st = new StringTokenizer(br.readLine()); // size_b
        size_b = Integer.parseInt(st.nextToken());

        b = new int[size_b];

        st = new StringTokenizer(br.readLine()); // input b
        for (int i = 0; i < size_b; i++) {
            b[i] = Integer.parseInt(st.nextToken());
        }

    }

    static void print() {
        for (int i : a) {
            System.out.print(i + " ");
        }
        System.out.println();

        for (int i : b) {
            System.out.print(i + " ");
        }
    }
}
