#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <bitset>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;
typedef pair<int32, pii> piii;

int32 n, m, ans;
int32 root[101010], level[101010], maxc[101010][20], minc[101010][20], lca[101010][20];
bitset<101010> visited;
vector<vector<pii>> adj;
vector<piii> _list;
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

void dfs(int32 u, int32 p) {
    loop(it, adj[u]) {
        int32 v, c; v = it.first, c = it.second;
        visited[v] = true;
        if (v == p) continue;
        level[v] = level[u] + 1;
        lca[v][0] = u;
        minc[v][0] = maxc[v][0] = c;
        rep(lg, 1, 19) {
            lca[v][lg] = lca[lca[v][lg - 1]][lg - 1];
            minc[v][lg] = min(minc[v][lg - 1], minc[lca[v][lg - 1]][lg - 1]);
            maxc[v][lg] = max(maxc[v][lg - 1], maxc[lca[v][lg - 1]][lg - 1]);
        }
        dfs(v, u);
    }
}

pii query(int32 u, int32 v) {
    int32 resMax, resMin; resMax = 0, resMin = 1e9;
    if (level[v] > level[u]) swap(u, v);
    int32 dis = level[u] - level[v];
    rep2(i, 19, 0) if (dis >> i & 1) {
        resMax = max(resMax, maxc[u][i]);
        resMin = min(resMin, minc[u][i]);
        u = lca[u][i];
    }
    if (u != v) {
        rep2(i, 19, 0) {
            if (lca[u][i] != lca[v][i]) {
                resMax = max(resMax, max(maxc[u][i], maxc[v][i]));
                resMin = min(resMin, min(minc[u][i], minc[v][i]));
                u = lca[u][i], v = lca[v][i];
            }
        }
        resMax = max(resMax, max(maxc[u][0], maxc[v][0]));
        resMin = min(resMin, min(minc[u][0], minc[v][0]));
    }
    return {resMin, resMax};
}
void initLCA() {
    memset(lca, 0, sizeof lca);
    memset(minc, 0x3f3f3f3f, sizeof minc);
    memset(maxc, 0, sizeof maxc);
    level[1] = 1;
    rep(i, 1, n) if (!visited[i]) {
        level[i] = 1, visited[i] = true;
        dfs(i, i);
    }
}

int main() {
    freopen("BGAME.INP", "r", stdin);
    freopen("BGAME.OUT", "w", stdout);
    scanf("%ld %ld", &n, &m);
    rep(i, 1, m) {
        int32 u, v, c;
        scanf("%ld %ld %ld", &u, &v, &c);
        edges.push_back({c, {u, v}});
    }
    // Init
    ans = 0;
    adj.assign(n + 2, vector<pii>());
    memset(level, 0, sizeof level);
    rep(i, 1, n) root[i] = i;
    sort(edges.begin(), edges.end(), greater<piii>());
    //
    loop(it, edges) {
        int32 u, v, c;
        u = it.second.first, v = it.second.second, c = it.first;
        if (merge(u, v)) {
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        } else _list.push_back({c, {u, v}});
    }
    memset(level, 0, sizeof level);
    initLCA();
    loop(it, _list) {
        int32 u, v, c;
        c = it.first, u = it.second.first, v = it.second.second;
        pii tmp = query(u, v);
        ans = max(ans, min(tmp.first, c) + max(tmp.second, c));
    }
    printf("%ld", ans);
    return 0;
}
