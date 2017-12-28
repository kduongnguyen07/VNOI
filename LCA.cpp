#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i<=b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)
int n, m, Q, T;
bool adj[1010][1010];
int h[1010], p[1010], lca[1010][20];

void Init() {
    memset(h, 0, sizeof(h));
    memset(p, 0, sizeof(p));
    memset(lca, 0, sizeof(lca));
    memset(adj, 0, sizeof(adj));
    p[1] = 0;
    h[1] = 1;
}



void Input() {
    int tmp, child;
    cin >> n;
    rep(i, 1, n) {
        cin >> tmp;
        rep(j, 1, tmp) {
            cin >> child; p[child] = i;
            adj[i][child] = 1;
        }
    }
    cin >> Q;
}

void dfs(int u, int par) {
    rep(v, 1, n) {
        if (adj[u][v] && v != par) {
            h[v] = h[u] + 1;
            p[v] = u;
            dfs(v, u);
        }
    }
}

int getbit(int x, int i) {
    return (x >> i & 1);
}

int find_lca(int u, int v) {
    if (h[v] > h[u]) swap(u, v);
    int dis = h[u] - h[v];
    rep2(lg, 19, 0) {
        if(getbit(dis, lg)) u = lca[u][lg];
    }

    if (u == v) return u;

    rep2(lg, 19, 0) {
        if (lca[u][lg] != lca[v][lg]) {
            u = lca[u][lg]; v = lca[v][lg];
        }
    }
    return p[u] /*return lca[u][0] */ ;
}

void Compute() {
    dfs(1, -1);
    rep(i, 1, n) lca[i][0] = p[i];
    rep(lg, 1, 19) {
        rep(u, 1, n)
            lca[u][lg] = lca[lca[u][lg - 1]][lg - 1];
    }
    while (Q--) {
        int u, v; cin >> u >> v;
        cout << find_lca(u, v) << "\n";
    }
}

int main() {
    //freopen("LCA.INP", "r", stdin);
    cin >> T;
    int index = 1;
    while(T--) {
        cout << "Case " << index << ":\n"; index++;
        Init();
        Input();
        Compute();
    }
    return 0;
}
