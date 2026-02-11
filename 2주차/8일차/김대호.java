import java.util.*;
import java.io.*;

public class Main {
    static int N, M;
    static List<Integer>[] adj, revAdj;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        adj = new ArrayList[N + 1]; // bottom-up
        revAdj = new ArrayList[N + 1]; // top-down
        for (int i = 1; i <= N; i++) {
            adj[i] = new ArrayList<>();
            revAdj[i] = new ArrayList<>();
        }

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            adj[a].add(b);
            revAdj[b].add(a);
        }

        int answer = 0;
        for (int i = 1; i <= N; i++) {
            if (bfs(i, adj) + bfs(i, revAdj) == N - 1) {
                answer++;
            }
        }

        System.out.println(answer);
    }

    static int bfs(int start, List<Integer>[] graph) {
        Queue<Integer> queue = new LinkedList<>();
        boolean[] visited = new boolean[N + 1];
        queue.add(start);
        visited[start] = true;

        int count = 0;
        while (!queue.isEmpty()) {
            int curr = queue.poll();

            for (int next : graph[curr]) {
                if (!visited[next]) {
                    visited[next] = true;
                    queue.add(next);
                    count++;
                }
            }
        }
        return count;
    }
}