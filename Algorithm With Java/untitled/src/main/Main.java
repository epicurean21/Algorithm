package main;

import java.io.*;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) {

        int[][] rc = { { 8, 6, 3 }, { 3, 3, 7 }, { 8, 4, 9 } };

        int row = rc.length;
        int col = rc[0].length;
        String[] operations = { "Rotate", "ShiftRow", "ShiftRow" };

        for (String opr : operations) {
            if (opr.equals("Rotate")) {
                rc = Rotate(rc);
            } else if (opr.equals("ShiftRow")) {
                rc = ShiftRow(rc);
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                System.out.print(rc[i][j]);
            }
            System.out.println();
        }
    }

    static int[][] Rotate(int[][] mat) {
        int row = mat.length;
        int col = mat[0].length;

        int tmp = mat[0][0];

        // 왼쪽 세로줄
        for (int i = 0; i < row - 1; i++) {
            mat[i][0] = mat[i + 1][0];
        }

        // 아래쪽 가로줄
        for (int i = 0; i < col - 1; i++) {
            mat[row - 1][i] = mat[row - 1][i + 1];
        }

        // 오른쪽 세로줄
        for (int i = row - 1; i > 0; i--) {
            mat[i][col - 1] = mat[i - 1][col - 1];
        }

        //위쪽 가로줄
        for (int i = col - 1; i > 0; i--) {
            mat[0][i] = mat[0][i - 1];
        }

        mat[0][1] = tmp;
        return mat;
    }

    static int[][] ShiftRow(int[][] mat) {
        int row = mat.length;

        int[] tmp = mat[row - 1];
        for (int i = row - 1; i > 0; i--) {
            mat[i] = mat[i - 1];
        }
        mat[0] = tmp;

        return mat;
    }

}