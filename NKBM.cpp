#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, m, k, ans = 0, trace[1100], visit[1100], ML[1100], MR[1100];
vector<int> adj[1100];

void Init() {
    memset(ML, 0, sizeof(ML));
    memset(MR, 0, sizeof(MR));
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n >> k;
    while(k--) {
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
}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}
