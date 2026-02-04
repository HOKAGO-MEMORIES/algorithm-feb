import java.util.*;
import java.io.*;

public class Main {
    static    List<Integer> arr = new ArrayList<>();
    public static void main (String[] args)throws Exception{
        int n, k;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken()); k = Integer.parseInt(st.nextToken());
        int s=2147483647, e = 0;
        st = new StringTokenizer(br.readLine());
        for(int i=0;i<n;i++){
            int x = Integer.parseInt(st.nextToken());
            e+=x;
            s = Math.min(s, x);
            arr.add(x);
        }
        if(k==1){
            System.out.println(e);
            return;
        }
        int answer = 0;
        while(s<=e){
            int m = (s+e)/2;
            int sum = 0;
            int nowk=0;
            for(int i=0;i<n;i++){
                int x = arr.get(i);
                sum+=x;
                if(sum>=m){
                    sum=0;
                    nowk++;
                }
            }
            if(nowk>=k){
                answer = m;
                s = m+1;
            }else{
                e = m-1;
            }
        }
        System.out.println(answer);
    }
}
