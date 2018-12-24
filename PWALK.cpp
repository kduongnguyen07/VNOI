#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)
typedef pair<int, int> pii;

int lca[1010][20], dis[1010][20], h[1010];
int n, Q;
vector<pii> adj[1010];

void Init() {
    memset(lca, 0, sizeof lca);
    memset(dis, 0, sizeof dis);
}

void Input() {
    cin >> n >> Q;
    rep(i, 1, n -1) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back(pii(v, c));
        adj[v].push_back(pii(u, c));
    }
}

void dfs(int u, int p) {
    vector<pii>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = it->first, c = it->second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        lca[v][0] = u;
        dis[v][0] = c;
        rep(lg, 1, 19) {
            lca[v][lg] = lca[lca[v][lg - 1]][lg - 1];
            dis[v][lg] = dis[v][lg - 1] + dis[lca[v][lg - 1]][lg - 1];
        }
        dfs(v, u);
    } 
}

int query(int u, int v) {
    int d, res = 0;
    if (h[v] > h[u]) swap(u, v);
    d = h[u] - h[v];
    rep2(lg, 19, 0) if (d >> lg & 1) {
         res += dis[u][lg]; u = lca[u][lg];
    }
    if (u != v) {
        rep2(lg, 19, 0) 
            if (lca[u][lg] != lca[v][lg]) {
                res += dis[u][lg] + dis[v][lg];
                u = lca[u][lg]; v = lca[v][lg];
            }
        res += dis[u][0] + dis[v][0]; 
    }
    return res;
}

void Compute() {
    h[1] = 1;
    dfs(1,1);
    rep(i, 1, Q) {
        int u, v; cin >> u >> v;
        cout << query(u, v) << endl;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Init();
    Input();
    Compute();
    return 0;
}
