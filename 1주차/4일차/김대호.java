package algorithm;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {	
	public static int isHasCycle(List<List<Integer>> adjList, int left, int right) { // 사이클 있으면 -1, 없다면 leftNodeNum 반환
		boolean[] visited = new boolean[adjList.size() + 1];
		Queue<Integer> q = new LinkedList<>();
		q.offer(left);
		visited[left] = true;
		visited[right] = true;
		
		int count = 0;
		while(!q.isEmpty()) {
			int now = q.poll();

			for (int i = 0; i < adjList.get(now).size(); i++) {
				int next = adjList.get(now).get(i);
				
				if (next == right && now != left) {
					return -1;
				} else {
					if (!visited[next]) {
						q.offer(next);
						visited[next] = true;
						count++;
					}
				}
			}
		}
		
		return count;
	}
	
	public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] NMK = br.readLine().split(" ");
        int N = Integer.parseInt(NMK[0]);
        int M = Integer.parseInt(NMK[1]);
        int K = Integer.parseInt(NMK[2]);
        
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i <= N; i++) {
        	adjList.add(new ArrayList<>());
        }
        int left = 0;
        int right = 0;
        for (int i = 0; i < M; i++) {
        	String[] fromTo = br.readLine().split(" ");
        	int from = Integer.parseInt(fromTo[0]);
        	int to = Integer.parseInt(fromTo[1]);
        	adjList.get(from).add(to);
        	adjList.get(to).add(from);
        	if (i + 1 == K) {
        		left = from;
        		right = to;
        	}
        }

        int isHasCount = isHasCycle(adjList, left, right);
        if (isHasCount == -1) {
        	System.out.println("0");
        } else {        	
        	System.out.println(((long) isHasCount + 1) * (N - isHasCount - 1));
        }
    }
}