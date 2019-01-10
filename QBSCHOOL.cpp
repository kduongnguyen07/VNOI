#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <stdio.h>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef long long int64;

typedef pair<int32, int32> pii;
typedef pair<int64, int32> pii64;

int32 n, m;
int64 d[5050], F[5050];
vector<pii> adj[5050];
priority_queue<pii64, vector<pii64>, greater<pii64>> pq;

int main() {
    scanf("%ld %ld", &n, &m);
    rep(i, 1, m) {
        int32 u, v, c, t;
        scanf("%ld %ld %ld %ld", &t, &u, &v, &c);
        adj[u].push_back(pii(v, c));
        if (t > 1) adj[v].push_back(pii(u, c));
    }
    //Init
    memset(d, 0x3f3f3f3f3f3f3f3f, sizeof d);
    memset(F, 0, sizeof F);
    d[1] = 0, F[1] = 1;
    pq.push({0, 1});
    while(!pq.empty()) {
        pii64 top = pq.top(); pq.pop();
        int32 u; int64 du;
        u = top.se, du = top.fi;
        if (du > d[u]) continue;
        if (u == n) {
            printf("%ld %ld", d[u], F[u]);
            break;
        }
        loop(it, adj[u]) {
            int32 v; int64 c;
            v = it.fi, c = it.se;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                F[v] = F[u];
                pq.push({d[v], v});
            } else if (d[v] == d[u] + c) F[v] += F[u];
        }
    }
    return 0;
}
