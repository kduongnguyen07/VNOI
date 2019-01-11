#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;

int32 T, n, m, s, t, k, d1[10101], d2[10101];
vector<pii> adj[10101], radj[10101];

void solve(int32 s, int32 *d, vector<pii> adj[]) {
    memset(d, 0x3f3f3f3f, sizeof d * (n + 10));
    d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    while(!pq.empty()) {
        pii top = pq.top(); pq.pop();
        int32 u, du; du = top.fi, u = top.se;
        if (du > d[u]) continue;
        loop(it, adj[u]) {
            int32 v, c; v = it.fi, c = it.se;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                pq.push({d[v], v});
            }
        }
    }
}

int main() {
    scanf("%ld", &T);
    while(T--) {
        scanf("%ld %ld %ld %ld %ld", &n, &m, &k, &s, &t);
        rep(i, 1, n) adj[i].clear();
        rep(i, 1, n) radj[i].clear();
        rep(i, 1, m) {
            int32 u, v, c;
            scanf("%ld %ld %ld", &u, &v, &c);
            adj[u].push_back({v, c});
            radj[v].push_back({u, c});
        }
        //
        solve(s, d1, adj); solve(t, d2, radj);
        int32 res = d1[t];
        rep(i, 1, k) {
            int32 u, v, c;
            scanf("%ld %ld %ld", &u, &v, &c);
            res = min(res, min(d1[u] + c + d2[v], d1[v] + c + d2[u]));
        }
        if (res < 1e9) printf("%ld\n", res);
        else printf("-1\n");
    }
    return 0;
}
