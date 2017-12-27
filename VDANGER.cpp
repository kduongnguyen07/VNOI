#include <cstring>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
int adj[101][101];
vector<int> path;
int n, m;

void Init() {
    //memset(adj, 0x3f, sizeof(adj));
}

void Input() {
    //freopen("VDANGER.INP", "r", stdin);
    cin >> n >> m; path.assign(m + 1, 0);
    rep(i, 1, m) cin >> path[i];
    rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
}

void minimize(int &a, int b) {
    if (b < a) a = b;
}

void Compute() {
    int ans = 0;
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) minimize(adj[i][j], adj[i][k] + adj[k][j]);
    if (path[1] != 1) ans += adj[1][path[1]];
    rep(i, 1, m - 1) ans += adj[path[i]][path[i + 1]];
    if (path[m] != n) ans += adj[path[m]][n];
    cout << ans;
}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}
