#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <bitset>

#define fi first
#define se second
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef pair<int32, double> pid;
typedef pair<int32, int32> pii;
typedef pair<double, pii> pdii;

int32 n, m, k;
vector<pid> adj[1010];
priority_queue<pdii, vector<pdii>, greater<pdii>> pq;
double d[1010][20];
bitset<20> visited[1010];

int main() {
    scanf("%ld %ld %ld", &n, &m, &k);
    rep(i, 1, m) {
        int32 u, v; double c;
        scanf("%ld %ld %lf", &u, &v, &c);
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    //
    rep(i, 1, n) rep(j, 0, k) d[i][j] = 1e9;
    rep(i, 0, k) d[1][i] = 0;
    rep(i, 0, k) pq.push({0 ,{1, i}});
    while(!pq.empty()) {
        pdii top = pq.top(); pq.pop();
        int32 u, t; double du;
        du = top.fi, u = top.se.fi, t = top.se.se;
        if (du > d[u][t]) continue;
        if (t == k && u == n) {
            printf("%.2f", d[u][t]);
            break;
        }
        visited[u][t] = true;
        loop(it, adj[u]) {
            int32 v = it.fi; double c = it.se;
            double moderm = 1;
            rep(j, t, k) {
                if (!visited[v][j] && d[v][j] > d[u][t] + (c / moderm)) {
                    d[v][j] = d[u][t] + (c / moderm);
                    pq.push({d[v][j], {v, j}});
                }
                moderm *= 2;
            }
        }
    }
    return 0;
}
