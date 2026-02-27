import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();

        if (s == null || s.length() == 0) {
            System.out.println(0);
            return;
        }

        int n = s.length();
        int[] prefixK = new int[n + 1]; // 누적 합 : 인덱스까지 K가 몇 개 있는지
        ArrayList<Integer> rPos = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            prefixK[i + 1] = prefixK[i];
            if (s.charAt(i) == 'K') {
                prefixK[i + 1]++;
            } else {
                rPos.add(i);
            }
        }

        if (rPos.isEmpty()) {
            System.out.println(0);
            return;
        }

        int totalK = prefixK[n];
        int left = 0;
        int right = rPos.size() - 1; // r에 대해서만 투 포인트 수행
        int maxLen = 0;

        while (left <= right) {
            int leftRIdx = rPos.get(left);
            int rightRIdx = rPos.get(right);

            int leftKLen = prefixK[leftRIdx];
            int rightKLen = totalK - prefixK[rightRIdx + 1];

            // 길이 = R의 개수 + 2 * min(왼쪽K, 오른쪽K)
            int currentRLen = (right - left + 1);
            int currentTotalLen = currentRLen + 2 * Math.min(leftKLen, rightKLen);

            maxLen = Math.max(maxLen, currentTotalLen);

            if (leftKLen < rightKLen) {
                left++;
            } else {
                right--;
            }
        }

        System.out.println(maxLen);
    }
}