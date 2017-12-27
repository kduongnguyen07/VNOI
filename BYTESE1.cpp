#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> piii;
priority_queue<piii, vector<piii>, greater<piii> > pq;
int adj[101][101], d[101][101];
int vtx[] = {0,-1,0,1};
int vty[] = {-1,0,1,0};
int K, m, n, a, b, T;

int main() {
    freopen("BYTESE1.INP", "r", stdin);
    freopen("BYTESE1.OUT", "w", stdout);
    cin >> K;
    while(K--) {
        cin >> m >> n;
        pq = priority_queue<piii, vector<piii>, greater<piii> >();
        memset(adj, 0, sizeof(adj));
        memset(d, 0x3f3f, sizeof(d));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) cin >> adj[i][j];
        }
        cin >> a >> b >> T;
        d[1][1] = adj[1][1];
        pq.push(make_pair(adj[1][1], pii(1,1)));
        while(!pq.empty()) {
            piii tmp = pq.top(); pq.pop();
            if (tmp.second == pii(a, b)) break;
            for (int i = 0; i < 4; i++) {
                int x = tmp.second.first + vtx[i];
                int y = tmp.second.second + vty[i];
                if (x < 1 || y < 1 || x > m || y > n) continue;
                if (d[x][y] > tmp.first + adj[x][y]) {
                    d[x][y] = tmp.first + adj[x][y];
                    pq.push(make_pair(d[x][y], pii(x,y)));
                }
            }
        }
        if (d[a][b] <= T) cout << "YES\n" << T - d[a][b] << endl;
        else cout << "NO\n";
    }
    return 0;
}
