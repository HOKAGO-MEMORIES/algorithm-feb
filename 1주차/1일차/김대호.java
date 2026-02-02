package algorithm_study;

import java.io.*;
import java.util.*;

public class Main {
    static int N, M;
    static char[][] map;
    static final int[][] DIRS = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int[] NM = Arrays.stream(br.readLine().split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();

        N = NM[0];
        M = NM[1];

        map = new char[N][M];

        for (int i = 0; i < N; i++) {
            String line = br.readLine();
            for (int j = 0; j < M; j++) {
                map[i][j] = line.charAt(j);
            }
        }

        int maxDistance = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] == 'L') {
                    maxDistance = Math.max(maxDistance, bfs(i, j));
                }
            }
        }

        System.out.println(maxDistance);
    }

    public static int bfs(int startY, int startX) {
        Queue<int[]> queue = new LinkedList<>(); // {y, x, distance}
        queue.offer(new int[] {startY, startX, 0});

        boolean[][] visited = new boolean[N][M];
        visited[startY][startX] = true;

        int localMaxDist = 0;
        while (!queue.isEmpty()) {
            int[] current = queue.poll();

            if (current[2] > localMaxDist) {
                localMaxDist = current[2];
            }

            for (int[] dir : DIRS) {
                int ny = current[0] + dir[0];
                int nx = current[1] + dir[1];

                if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                    if (!visited[ny][nx] && map[ny][nx] == 'L') {
                        visited[ny][nx] = true;
                        queue.offer(new int[] {ny, nx, current[2] + 1});
                    }
                }
            }
        }
        return localMaxDist;
    }
}