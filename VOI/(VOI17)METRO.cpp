#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <bitset>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int32, int32> pii;
typedef pair<int64, int32> pii64;
typedef pair<int64, pii> piii;

struct edges {
    int32 v, k;
    int64 c;
    edges() {}
    edges(int32 v, int64 c, int32 k): v(v), c(c), k(k) {}
};

int32 n, m, s, t, delta;
int64 d[101010];
vector<edges> adj[101010];
priority_queue<pii64, vector<pii64>, greater<pii64>> pq;

void fulltask() {
    memset(d, 0x3f3f3f3f3f3f3f3f, sizeof d);
    d[s] = 0; pq.push({0, s});
    while(!pq.empty()) {
        pii top = pq.top(); pq.pop();
        int32 u; int64 du;
        u = top.second, du = top.first;
        if (du > d[u]) continue;
        if (u == t) {
            printf("%lld", d[u]);
            return;
        }
        loop(it, adj[u]) {
            if (d[it.v] > d[u] + it.c) {
                d[it.v] = d[u] + it.c;
                pq.push({d[it.v], it.v});
            }
        }
    }
    printf("-1");
}

int main() {
    freopen("METRO.INP", "r", stdin);
    freopen("METRO.OUT", "w", stdout);
    scanf("%ld %ld %ld %ld %ld", &n, &m, &s, &t, &delta);
    rep(i, 1, m) {
        int32 u, v; int64 c;
        scanf("%ld %ld %lld", &u, &v, &c);
        if (u != s) c += 1LL * i;
        if (v != t) c += 1LL * i * delta;
        adj[u].push_back(edges(v, c, i));
    }
    fulltask();
    return 0;
}
