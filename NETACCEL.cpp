#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, double> pid;
typedef pair<double, pii> pdii;

#define fi first
#define se second
#define rep(i, a, b) for (int i = a; i <=b; i++)

int n, m, k;
double d[1010][11];
bool _free[1010][11];
vector<pid> adj[1010];
priority_queue< pdii, vector<pdii>, greater<pdii> > pq;

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("NETACCEL.INP", "r", stdin);
    cin >> n >> m >> k;
    rep(i, 1, m) {
        int u, v; double c;
        cin >> u >> v >> c;
        adj[u].push_back(pid(v, c));
        adj[v].push_back(pid(u, c));
    }
}

void Init() {
    memset(_free, true, sizeof(_free));
    rep(i, 1, n) rep(j, 0, k) d[i][j] = 1e9;
    rep(i, 0, k) d[1][i] = 0;
}

void Compute() {
    rep(i, 0, k) pq.push(make_pair(0, pii(1, i)));
    while(!pq.empty()) {
        pdii tmp = pq.top(); pq.pop();
        int u = tmp.se.fi;
        int x = tmp.se.se;
        if(x == k && u == n) {
            cout << fixed << setprecision(2) << d[n][k]; return;
        }
        _free[u][x] = false;
        vector<pid>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++) {
            int v = it->fi; double c = it->se;
            double update = 1;
            rep(i, x, k) {
                if(_free[v][i] && d[v][i] > d[u][x] + c / update) {
                    d[v][i] = d[u][x] + c / update;
                    pq.push(make_pair(d[v][i], pid(v, i)));
                }
                update *= 2;
            }
        }
    }
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
