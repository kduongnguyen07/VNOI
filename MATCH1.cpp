#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, m, ans = 0, trace[110], visit[110], ML[110], MR[110];
vector<int> adj[110];

void Init() {
    memset(ML, 0, sizeof(ML));
    memset(MR, 0, sizeof(MR));
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("MATCH1.INP", "r", stdin);
    cin >> m >> n;
    while(!cin.eof()) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
}

int bfs() {
     memset(trace, 0, sizeof(trace));
     queue<int> Q;
     rep(i, 1, m) if (!ML[i]) Q.push(i);
     while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        vector<int>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++) {
            if (!trace[*it]) {
                trace[*it] = u;
                if (!MR[*it]) return *it;
                Q.push(MR[*it]);
            }
        }
     }
     return 0;
}

void enlager(int v) {
    int u, next;
    while(v != 0) {
        u = trace[v];
        next = ML[u];
        ML[u] = v;
        MR[v] = u;
        v = next;
    }
}

void Compute() {
    while(1) {
        int u = bfs(); if (!u) break;
        enlager(u);
    }
    rep(i, 1, m) if (ML[i]) ans++;
    cout << ans << '\n';
    rep(i, 1, m) if (ML[i]) cout << i << " " << ML[i] << '\n';
}

int main() {
    Input();
    Compute();
    return 0;
}
