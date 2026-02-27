#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e9

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin>>T;
    while (T--) {
        int n,m;
        cin>>n>>m;

        vector dist(n+1, vector<int>(n+1));

        for (int i=1;i<=n;i++) {
            for (int j=1;j<=n;j++) {
                if (i==j) dist[i][j]=0;
                else dist[i][j]=INF;
            }
        }

        for (int i=0;i<m;i++) {
            int a,b,c;
            cin>>a>>b>>c;

            dist[a][b]=c;
            dist[b][a]=c;
        }

        for (int k=1;k<=n;k++) {
            for (int i=1;i<=n;i++) {
                for (int j=1;j<=n;j++) {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }

        int k;
        vector<int> start;
        cin>>k;
        for (int i=0;i<k;i++) {
            int x;
            cin>>x;
            start.push_back(x);
        }

        int minDist=INF;
        int ans=INF;
        for (int i=1;i<=n;i++) {
            int tmp=0;
            for (auto e:start) {
                tmp+=dist[e][i];
            }

            if (tmp<minDist) {
                minDist=tmp;
                ans=i;
            }
        }

        cout<<ans<<"\n";
    }
}
