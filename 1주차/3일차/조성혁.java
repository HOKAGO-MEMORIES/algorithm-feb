package ps_baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
	
	static int n, m;
	static int[] arr;
	
	// 그룹 만들기
	// 모든 그룹의 합이 최소 x 이상일 때 그릅의 수가 m 이상인가 ?
	static boolean calc(int x) {
		int cnt = 0; // 생성된 그룹의 수
		int sum = 0; // 그룹 합
		
		for (int i = 0; i < n; i++) {
			sum += arr[i];
			
			if (sum >= x) {
				sum = 0;
				cnt++;
			}
		}
		
		return cnt >= m;
	}

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		String line = br.readLine();
		StringTokenizer st = new StringTokenizer(line);
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		arr = new int[n];
		line = br.readLine();
		st = new StringTokenizer(line);
		for (int i = 0; i < n; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}
		
		int ans = 0;
		int left = 0;
		int right = Arrays.stream(arr).sum();
		while (left <= right) {
			int mid = (left + right) / 2;
						
			if (calc(mid)) {
				ans = Math.max(ans, mid);
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		
		sb.append(ans);
		System.out.println(sb);
	}
}
