import java.io.*;
import java.util.*;

public class Main {

    public static int p(StringTokenizer st){
        return Integer.parseInt(st.nextToken());
    }
        static int n ;
        // static int board[][] = new int[401][401];
        static int ba[][] = new int[401][401];
        static int bb[][] = new int[401][401];


    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n=p(st);
        for(int i=0;i<n;i++){
            st = new StringTokenizer(br.readLine());
            for(int j=0;j<n;j++){
                int x = p(st);
                // board[i][j] = x;
                if(i>0&&j>0){
                    ba[i][j] = ba[i-1][j-1]+x;
                }else{
                    ba[i][j] = x;
                }
                if(i>0 && j<n-1){
                    bb[i][j] = bb[i-1][j+1]+x;
                }else{
                    bb[i][j] = x;
                }
            }
        }
        int maxi = 0;
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-1;j++){
                for(int m=1;m<Math.min(n-i, n-j);m++){
                    int rb = ba[i+m][j+m];
                    int lb = bb[i+m][j];
                    int rt, lt;
                    if(i>0 && j+m+1<n){
                        rt = bb[i-1][j+m+1];
                    }else{
                        rt = 0;
                    }
                    if(i>0&&j>0){
                        lt = ba[i-1][j-1];
                    }else{
                        lt = 0;
                    }
                    maxi = Math.max(maxi, rb - lt - lb + rt);
                    // System.out.println(m + " "+ i + " " + j+" "+ rb+" "+ lt+" "+ lb+" "+ rt+" "+(rb - lt - lb + rt));
                }   
            }
        }
        System.out.println(maxi);
    }
}