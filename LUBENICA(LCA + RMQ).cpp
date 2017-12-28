#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)

int n, K;
vector<pii> adj[101010];
int lca[101010][20], maxw[101010][20], minw[101010][20], h[101010];

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("LUBENICA.INP", "r", stdin);
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back(pii(v, c));
        adj[v].push_back(pii(u, c));
    }
    cin >> K;
}

void Init() {
     memset(lca, 0, sizeof(lca));
     h[1] = 1;
}

void dfs(int u, int p) {
    vector<pii>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = it->first; int w = it->second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        lca[v][0] = u;
        maxw[v][0] = minw[v][0] = w;
        rep(lg, 1, 19) {
            lca[v][lg] = lca[lca[v][lg - 1]][lg - 1];
            maxw[v][lg] = max(maxw[v][lg - 1], maxw[lca[v][lg - 1]][lg - 1]);
            minw[v][lg] = min(minw[v][lg - 1], minw[lca[v][lg - 1]][lg - 1]);
        }
        dfs(v, u);
    }
}

int getbit(int dis, int lg) {
    return dis >> lg & 1;
}

void query(int u, int v) {
    int resmin, resmax; resmin = long(1e9); resmax = 0;
    if (h[v] > h[u]) swap(u, v);
    int dis = h[u] - h[v];
    rep2(lg, 19, 0) if (getbit(dis, lg)) {
        resmin = min(resmin, minw[u][lg]);
        resmax = max(resmax, maxw[u][lg]);
        u = lca[u][lg];
    }
    if (u != v) {
        rep2(lg, 19, 0)
            if (lca[u][lg] != lca[v][lg]) {
                resmin = min(resmin, min(minw[u][lg], minw[v][lg]));
                resmax = max(resmax, max(maxw[u][lg], maxw[v][lg]));
                u = lca[u][lg]; v = lca[v][lg];
            }
        resmin = min(resmin, min(minw[u][0], minw[v][0]));
        resmax = max(resmax, max(maxw[u][0], maxw[v][0]));
    }
    cout << resmin << " " << resmax << '\n';
}

void Compute() {
    dfs(1, -1);
    while(K--) {
        int u, v; cin >> u >> v;
        query(u, v);
    }
}

int main() {
     Input();
     Init();
     Compute();
     return 0;
}
