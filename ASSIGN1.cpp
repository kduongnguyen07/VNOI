#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, adj[220][220], trace[220], matchL[220], matchR[220];

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
}

int bfs(int mid) {
     memset(trace, 0, sizeof(trace));
     queue<int> Q;
     rep(i, 1, n) if (!matchL[i]) Q.push(i);
     while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        rep(v, 1, n) if (adj[u][v] <= mid && !trace[v]) {
            trace[v] = u;
            if (!matchR[v]) return v;
            Q.push(matchR[v]);
        }
     }
     return false;
}

void enlager(int v) {
    int u, next;
    while (v != 0) {
        u = trace[v];
        next = matchL[u];
        matchL[u] = v;
        matchR[v] = u;
        v = next;
    }
}

bool check(int mid) {
    memset(matchL, 0, sizeof(matchL));
    memset(matchR, 0, sizeof(matchR));
    while(1) {
        int v = bfs(mid); if (!v) break;
        enlager(v);
    }
    rep(i, 1, n) if (!matchL[i]) return false;
    return true;
}

void Compute() {
    int ll, rr, mid, res;
    ll = 0; rr = 1e9; mid = (ll + rr) >> 1;
    while(ll <= rr) {
        if (check(mid)) {
            res = mid;
            rr = mid - 1;
        } else ll = mid + 1;
        mid = (ll + rr) >> 1;
    }
    cout << res;
}

int main() {
    Input();
    Compute();
    return 0;
}
