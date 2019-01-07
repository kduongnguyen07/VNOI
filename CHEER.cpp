#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <vector>
#include <functional>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;
typedef pair<int32, pii> piii;

int32 n, m, A[10101], root[10101], level[10101];
vector<vector<pii>> adj;
vector<piii> edges;

int32 getRoot(int32 u) { return root[u] == u ? u : root[u] = getRoot(root[u]); }

bool merge(int32 u, int32 v) {
    u = getRoot(u), v = getRoot(v);
    if (u == v) return false;
    if (level[u] == level[v]) level[u]++;
    if (level[u] > level[v]) root[v] = u;
    else root[u] = v;
    return true;
}

int32 dfs(int32 u, int32 p) {
    int32 res = 0;
    loop(it, adj[u]) {
        int32 v, c; v = it.first, c = it.second;
        if (v == p) continue;
        res += dfs(v, u) + c;
    }
    return res;
}

int main() {
    scanf("%ld %ld", &n, &m);
    rep(i, 1, n) scanf("%ld", A + i);
    adj.assign(n + 2, vector<pii>());
    rep(i, 1, m) {
        int32 u, v, c; scanf("%ld %ld %ld", &u, &v, &c);
        edges.push_back({c + c + A[u] + A[v], {u, v}});
    }
    //
    sort(edges.begin(), edges.end());
    rep(i, 1, n) root[i] = i;
    memset(level, 0, sizeof level);
    int start = 0; A[0] = 1e9;
    loop(it, edges) {
        int32 u, v, c;
        u = it.second.first, v = it.second.second; c = it.first;
        if (merge(u, v)) {
            //cout << u << " " << v << endl;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
            if (A[start] > A[u]) start = u;
            if (A[start] > A[v]) start = v;
        }
    }
    printf("%ld", dfs(start, -1) + A[start]);
    return 0;
}
