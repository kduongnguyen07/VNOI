#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;
#define rep(i, a, b) for (int i = a; i <= b; i++)
typedef pair<int, int> pii;
typedef pair<double, int> pdi;

const double eps = 0.000001;
pii dot[1010];
bool c[1010][1010];
double adj[1010][1010];
int n, m;
double maxdis;

void Init() {
    memset(c, false, sizeof c);
    memset(adj, 0, sizeof adj);
}

void Input() {
    cin >> n >> m >> maxdis;
    rep(i, 1, n) cin >> dot[i].first >> dot[i].second;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        c[u][v] = c[v][u] = true;
    }
}

double get_dis(int u, int v) {
    return sqrt(pow(dot[u].first - dot[v].first, 2) + pow(dot[u].second - dot[v].second, 2));
}

int dijsktra() {
    priority_queue<pdi, vector<pdi>, greater<pdi> > pq;
    double d[1010]; rep(i, 1, n) d[i] = 1e9;
    d[1] = 0;
    pq.push(make_pair(0, 1));
    while(!pq.empty()) {
        pdi tmp = pq.top(); pq.pop();
        int cur = tmp.second;
        double du = tmp.first; if (du - d[cur] > eps) continue;
        if (cur == n) return trunc(d[n] * 1000);
        rep(i, 1, n) {
            if (cur != i && adj[cur][i] != 1e9) {
                if (d[i] > d[cur] + adj[cur][i] + eps) {
                    d[i] = d[cur] + adj[cur][i] + eps;
                    pq.push(pdi(d[i], i));
                }
            }
        }
    }
    return -1;
}

void Compute() {
    rep(u, 1, n) {
        adj[u][u] = 1e9;
        rep(v, u + 1, n) {
            if (!c[u][v]) {
                double res = get_dis(u, v);
                if (maxdis - res >= eps) adj[u][v] = adj[v][u] = res;
                else adj[u][v] = adj[v][u] = 1e9;
            }
        }
    }
    cout << dijsktra() << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Init();
    Input();
    Compute();
    return 0;
}
