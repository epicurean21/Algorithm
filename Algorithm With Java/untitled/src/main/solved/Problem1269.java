package main.solved;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

public class Problem1269 {
    static Set<Integer> set_a = new HashSet<>();
    static Set<Integer> set_b = new HashSet<>();

    public static void main(String[] args) throws Exception {
        input();
        solve();
    }

    static void input() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        final int size_a = Integer.parseInt(st.nextToken());
        final int size_b = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());

        for (int i = 0; i < size_a; i++) {
            set_a.add(Integer.parseInt(st.nextToken()));
        }

        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < size_b; i++) {
            int new_b = Integer.parseInt(st.nextToken());
            if (set_a.contains(new_b)) {
                set_a.remove(new_b);
            } else {
                set_b.add(new_b);
            }
        }

    }

    static void solve() {
        System.out.println(getAnswer(set_a, set_b));
    }

    static int getAnswer(final Set<Integer> set_a, final Set<Integer> set_b) {
        return set_a.size() + set_b.size();
    }
}