import java.util.*;
import java.io.*;

public class Main {
    static final int INF = 100_000_000;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        for (int t = 0; t < T; t++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());

            int[][] dist = new int[N + 1][N + 1];

            for (int i = 1; i <= N; i++) {
                Arrays.fill(dist[i], INF);
                dist[i][i] = 0;
            }

            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine());
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
                int w = Integer.parseInt(st.nextToken());
                dist[u][v] = Math.min(dist[u][v], w);
                dist[v][u] = Math.min(dist[v][u], w);
            }

            // 플로이드-와셜
            for (int k = 1; k <= N; k++) {
                for (int i = 1; i <= N; i++) {
                    for (int j = 1; j <= N; j++) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }

            int K = Integer.parseInt(br.readLine());
            int[] roomNumbers = new int[K];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < K; i++) {
            	roomNumbers[i] = Integer.parseInt(st.nextToken());
            }

            int minTotalDist = Integer.MAX_VALUE;
            int resultRoom = -1;
            for (int i = 1; i <= N; i++) {
                int currentSum = 0;
                for (int friendPos : roomNumbers) {
                    currentSum += dist[friendPos][i];
                }

                if (currentSum < minTotalDist) {
                    minTotalDist = currentSum;
                    resultRoom = i;
                }
            }

            System.out.println(resultRoom);
        }
    }
}