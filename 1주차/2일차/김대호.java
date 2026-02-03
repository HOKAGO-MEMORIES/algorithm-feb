import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int[][] matrix = new int[N][N];
        int[][][] prefixSum = new int[N + 1][N + 2][2]; // {오른 대각 합, 왼 대각 합}
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine()); // StringTokenizer 사용
            for (int j = 0; j < N; j++) {
                matrix[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        // 구간합 Algo.
        for (int i = 0; i < prefixSum.length; i++) {
            for (int j = 0; j < prefixSum[0].length; j++) {
                if ((i - 1) >= 0 && (j - 2) >= 0) {
                    prefixSum[i][j][0] = prefixSum[i - 1][j - 1][0] + matrix[i - 1][j - 2];
                }

                if ((i - 1) >= 0 && j < matrix.length) {
                    prefixSum[i][j][1] = prefixSum[i - 1][j + 1][1] + matrix[i - 1][j];
                }
            }
        }

        int max = 0; // 부분행렬의 크기가 1인경우, 0
        for (int i = 2; i <= N; i++) {
            for (int y = 0; y <= N - i; y++) {
                for (int x = 0; x <= N - i; x++) {
                    int tempSum = (prefixSum[y + i][x + 1 + i][0] - prefixSum[y][x + 1][0])
                            - (prefixSum[y + i][x][1] - prefixSum[y][x + i][1]);
                    if (tempSum > max) {
                        max = tempSum;
                    }
                }
            }
        }

        System.out.println(max);
    }
}