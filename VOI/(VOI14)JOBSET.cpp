#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <bitset>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int s, t, n, m, maxC = 0;
int F[550][550], G[550][550], trace[550], D[550];
vector<int> adj[550];

void Init() {
    memset(F, 0, sizeof(F));
    memset(G, 0, sizeof(G));
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("JOBSET.INP", "r", stdin);
    cin >> n;
    s = n + 1; t = n + 2;
    rep(i, 1, n) {
        int c; cin >> c;
        if (c > 0) {
            G[s][i] = c;
            maxC += c;
            adj[s].push_back(i); adj[i].push_back(s);
        } else {
            G[i][t] = -c;
            adj[i].push_back(t); adj[t].push_back(i);
        }
    }
    cin >> m;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        G[u][v] = maxC + 1;
        adj[u].push_back(v); adj[v].push_back(u);
    }
}

bool bfs() {
    memset(trace, 0, sizeof(trace));
    queue<int> Q;
    Q.push(s);
    trace[s] = s;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        vector<int>::iterator v;
        for(v = adj[u].begin(); v != adj[u].end(); v++) {
            if (!trace[*v]) {
                if (G[u][*v] > F[u][*v]) {
                    D[*v] = min(D[u], G[u][*v] - F[u][*v]);
                    trace[*v] = u;
                }
                else if (F[*v][u] > 0) {
                    D[*v] = min(D[u], F[*v][u]);
                    trace[*v] = -u;
                } else continue;
                if (*v == t) return true;
                Q.push(*v);
            }
        }
    }
    return false;
}

void update_flow() {
    int v = t;
    while(v != s) {
        int u = trace[v];
        if (u > 0) F[u][v] += D[t];
        else {
            u = -u;
            F[v][u] -= D[t];
        }
        v = u;
    }
}

void Compute() {
    D[s] = 1e9;
    int res = 0;
    while(bfs()) {
        res += D[t];
        update_flow();
    }
    cout << maxC - res;
}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}
