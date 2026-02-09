import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int day = 1;

        while (true) {
            int p = Integer.parseInt(br.readLine());
            if (p == 0) break;

            int[][] parties = new int[p][2]; // {시작 시간, 종료 시간}
            for (int i = 0; i < p; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                parties[i][0] = Integer.parseInt(st.nextToken());
                parties[i][1] = Integer.parseInt(st.nextToken());
            }

            // 종료 시간 기준으로 정렬
            Arrays.sort(parties, (a, b) -> {
                if (a[1] == b[1]) return Integer.compare(a[0], b[0]);
                return Integer.compare(a[1], b[1]);
            });

            // 30분 단위 슬롯(8시~24시, 총 32개 슬롯)
            boolean[] usedSlots = new boolean[32];
            int count = 0;

            for (int[] party : parties) {
                int startIdx = (party[0] - 8) * 2;
                int endIdx = (party[1] - 8) * 2 - 1;

                for (int i = startIdx; i <= endIdx; i++) {
                    if (i >= 0 && i < 32 && !usedSlots[i]) {
                        usedSlots[i] = true;
                        count++;
                        break;
                    }
                }
            }

            System.out.println("On day " + day + " Emma can attend as many as " + count + " parties.");
            day++;
        }
    }
}