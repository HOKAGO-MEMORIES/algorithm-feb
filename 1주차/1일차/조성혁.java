package ps_baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
	
	static class Coor {
		int x;
		int y;
		
		Coor(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}
	
	static int[] dx = {-1, 0, 1, 0};
	static int[] dy = {0, 1, 0, -1};
	static char[][] arr;
	static int n, m;
	static int[][] visited;
	
	static int ans = 0;
	
	static void bfs(int x, int y) {
		visited = new int[n][m];
		Queue<Coor> q = new ArrayDeque<>();
		q.offer(new Coor(x, y));
		visited[x][y] = 1;
		
		while (!q.isEmpty()) {
			Coor cur = q.poll();
			int cx = cur.x;
			int cy = cur.y;
			
			for (int i = 0; i < 4; i++) {
				int nx = cx + dx[i];
				int ny = cy + dy[i];
				
				if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
				if (visited[nx][ny] > 0) continue;
				if (arr[nx][ny] == 'W') continue;
				
				visited[nx][ny] = visited[cx][cy] + 1;
				q.offer(new Coor(nx, ny));
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (visited[i][j] > 0) {
					ans = Math.max(ans, visited[i][j] - 1);
				}
			}
		}
	}

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		String line = br.readLine();
		StringTokenizer st = new StringTokenizer(line);
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		arr = new char[n][m];
		
		for (int i = 0; i < n; i++) {
			line = br.readLine();
			for (int j = 0; j < m; j++) {
				arr[i][j] = line.charAt(j);
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (arr[i][j] == 'L') {
					bfs(i, j);
				}
			}
		}
		
		sb.append(ans);
		System.out.println(sb);
	}
}
