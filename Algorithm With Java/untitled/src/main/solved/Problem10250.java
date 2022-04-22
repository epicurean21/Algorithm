package main.solved;

import java.io.*;
import java.util.StringTokenizer;

public class Problem10250 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        StringBuilder ans = new StringBuilder();

        for (int i = 0; i < T; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int H = Integer.parseInt(st.nextToken());
            int W = Integer.parseInt(st.nextToken());
            int N = Integer.parseInt(st.nextToken());

            if (N <= H) {
                ans.append(100 * N + 1).append('\n');
            } else {
                int count = 0;
                while (N > H) {
                    N -= H;
                    count++;
                }
                ans.append(100 * N + (count + 1)).append('\n');
            }
        }

        System.out.print(ans);
    }
}