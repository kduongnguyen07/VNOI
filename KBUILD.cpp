#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b;i++)

int n, m, root[1010101], h[1010101], par[1010101], ans;
vector<int> adj[1010101];

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n; ans = n - 1;
    rep(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> m;
}

void Init() {
    rep(i, 1, n) root[i] = i;
    h[1] = 1; par[1] = -1;
}

int getRoot(int p) {
    return (root[p] == p ? p : root[p] = getRoot(root[p]));
}

void dfs(int u, int p) {
    vector<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        if (*it == p) continue;
        h[*it] = h[u] + 1; par[*it] = u;
        dfs(*it, u);
    }
}

void Compute() {
    dfs(1, -1);
    while(m--) {
        int u, v; cin >> u >> v;
        while(u != v) {
            u = getRoot(u); v = getRoot(v);
            int hu = h[u], hv = h[v];
            if (u == v) break;
            if (hv >= hu) {
                v = root[v] = par[v]; ans--;
            }
            if (hu >= hv) {
                u = root[u] = par[u]; ans--;
            }
        }
    }
    cout << ans;
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
