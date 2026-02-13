import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        int[][] map = new int[N][M];
        long[][] dp = new long[N][M];

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 0; j < M; j++) {
                map[i][j] = Integer.parseInt(st.nextToken());
            }
        }

		// 첫 째 줄 초기화('왼 -> 오'로 밖에 진행 못 함)
        dp[0][0] = map[0][0];
        for (int j = 1; j < M; j++) {
            dp[0][j] = dp[0][j - 1] + map[0][j];
        }

        for (int i = 1; i < N; i++) {
            long[] leftToRight = new long[M];
            long[] rightToLeft = new long[M];

			// '왼 -> 오', '위 -> 아래' 비교
            leftToRight[0] = dp[i - 1][0] + map[i][0];
            for (int j = 1; j < M; j++) {
                leftToRight[j] = Math.max(dp[i - 1][j], leftToRight[j - 1]) + map[i][j];
            }

			// '오 -> 왼', '위 -> 아래' 비교
            rightToLeft[M - 1] = dp[i - 1][M - 1] + map[i][M - 1];
            for (int j = M - 2; j >= 0; j--) {
                rightToLeft[j] = Math.max(dp[i - 1][j], rightToLeft[j + 1]) + map[i][j];
            }

            for (int j = 0; j < M; j++) {
                dp[i][j] = Math.max(leftToRight[j], rightToLeft[j]);
            }
        }

        System.out.println(dp[N - 1][M - 1]);
    }
}