#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <bitset>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std;

typedef pair<double, int> pdi;
typedef pair<double, double> pdd;
typedef bitset<110> bits;

#define rep(i, a, b) for (int i = a; i <= b; i++)
const double eps = 1e-6;
const double oo = 1e18;
vector<pdd> A(110);
vector<int> S(110);
vector<bool> visit(110, false);
int n, adj[110][110];
double d[110];

void Input() {
    cin >> n;
    rep(i, 1, n) {
        cin >> A[i].first >> A[i].second >> S[i];
        rep(j, 1, n - 1) cin >> adj[i][j];
    }
}

double get_dis(int u, int v) {
    return sqrt(pow(A[v].first - A[u].first, 2) + pow(A[v].second - A[u].second, 2));
}

void Compute() {
    d[1] = 0; rep(i, 2, n) d[i] = oo;
    priority_queue<pdi, vector<pdi>, greater<pdi> > pq; pq.push(pdi(0.0, 1));
    while(!pq.empty()) {
        pdi tmp = pq.top(); pq.pop();
        int u = tmp.second; double du = tmp.first;
        if (fabs(du - d[u]) > eps) continue;
        visit[u] = true;
        rep(i, 1, n - 1) {
            if (!S[u]) break;
            int v = adj[u][i];
            double c = get_dis(u, v);
            if (!visit[v]) {
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    pq.push(pdi(d[v], v));
                }
                S[u]--;
            }
        }
    }
    rep(i, 1, n) cout << fixed << setprecision(6) << d[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    Input();
    Compute();
    return 0;
}

