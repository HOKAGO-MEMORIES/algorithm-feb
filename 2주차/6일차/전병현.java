import java.io.*;
import java.util.*;

public class Main {
	
	static BufferedReader br;

    static boolean tc(int day) throws Exception {
        StringTokenizer st = new StringTokenizer(br.readLine());
    	int n = Integer.parseInt(st.nextToken());
    	if(n==0)return false;
    	List<int[]> arr  =new ArrayList<>();
    	for(int i=0;i<n;i++) {
    		int a, b;
    		st = new StringTokenizer(br.readLine());
    		a = Integer.parseInt(st.nextToken());
    		b = Integer.parseInt(st.nextToken());
    		arr.add(new int[] {a, b});
    	}
    	arr.sort((a, b)->Integer.compare(a[0], b[0]));
    	int idx=0;
    	PriorityQueue<Integer> pq = new PriorityQueue<>();
    	int cnt=0;
    	for(int i=8;i<=24;i++) {
    		while(idx<arr.size() && arr.get(idx)[0]<=i) {
    			pq.add(arr.get(idx)[1]);
    			idx++;
    		}
    		while(!pq.isEmpty() && pq.peek()<=i)pq.poll();
    		if(!pq.isEmpty() && pq.peek() > i) {
    			pq.poll();
    			cnt++;
    		}
    		if(!pq.isEmpty() && pq.peek() > i) {
    			pq.poll();
    			cnt++;
    		}
    	}
    	System.out.printf("On day %d Emma can attend as many as %d parties.\n", day, cnt);
    	return true;
    }

    public static void main(String[] args) throws Exception {
    	br = new BufferedReader(new InputStreamReader(System.in));
    	for(int i=1;;i++) {
    		if(!tc(i))return;
    	}
    }
}