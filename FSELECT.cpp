#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)
#define fi first
#define se second

int n, K, root;
int lca[202020][20], h[202020];
vector<pii> house[202020];
vector<int> adj[202020];

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("FSELECT.INP", "r", stdin);
    int v, tmp;
    cin >> n >> K;
    rep(i, 1, n) {
        cin >> tmp >> v;
        house[tmp].push_back(pii(0, i));
        if(!v) root = i;
        else {
            adj[i].push_back(v);
            adj[v].push_back(i);
        }
    }
}

void Init() {
    memset(lca, 0, sizeof(lca));
    h[root] = 1; lca[root][0] = -1;
}

void dfs(int u, int p) {
    vector<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        if (*it == p) continue;
        h[*it] = h[u] + 1;
        lca[*it][0] = u;
        rep(i, 1, 19) if(lca[*it][i - 1] != -1) lca[*it][i] = lca[lca[*it][i - 1]][i - 1];
        dfs(*it, u);
    }
}

int getbit(int dis, int lg) {
    return dis >> lg & 1;
}

int find_lca(int u, int v) {
    if (h[v] > h[u]) swap(u, v);
    int dis = h[u] - h[v];
    rep2(lg, 19, 0) if (getbit(dis, lg) && lca[u][lg] != -1) u = lca[u][lg];
    if (u == v) return u;
    rep2(lg, 19, 0)
        if (lca[u][lg] != lca[v][lg]) {
            u = lca[u][lg]; v = lca[v][lg];
        }
    return lca[u][0];
}

void Compute() {
    vector<pii>::iterator it;
    int high_root = 0;
    dfs(root, -1);
    rep(i, 1, K) {
        for (it = house[i].begin(); it != house[i].end(); it++) it->fi = h[it->se];
        sort(house[i].begin(), house[i].end());
    }
    rep(i, 1, K) {
         int u = house[i].back().second;
         int res = 0;
         for (it = house[i].begin(); it != house[i].end() - 1; it++) {
            int v = it->second;
            high_root = h[find_lca(u, v)];
            res = max(h[u] - high_root + h[v] - high_root, res);
         }
         cout << res << '\n';
    }
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
