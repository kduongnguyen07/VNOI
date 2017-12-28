#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rep2(i, a, b) for(int i = a; i >= b;i--)
typedef pair<int, int> pii;

vector<pii> edge;
int root[101010], roads[101010];
bool del_road[101010];
int n, m, Q;

int getRoot(int p) {
    return (root[p] == p ? p : root[p] = getRoot(root[p]));
}

void join(int p, int q, int &component) {
    if(getRoot(p) != getRoot(q)) {
        root[getRoot(p)] = getRoot(q);
        component--;
    }
}

void Input() {
    //freopen("QHROAD.INP", "r", stdin);
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> Q;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        edge.push_back(pii(u, v));
    }
}

void Init() {
    rep(i, 1, n) root[i] = i;
    memset(del_road, 0, sizeof(del_road));
    rep(i, 1, Q) {
        cin >> roads[i];
        del_road[--roads[i]] = true;
    }
}

void Compute() {
    int component = n;
    int res[Q + 1];
    rep(i, 0, m - 1) {
        int u = edge[i].first;
        int v = edge[i].second;
        if(!del_road[i]) join(u, v, component);
    }
    rep2(i, Q, 1) {
        res[i] = component;
        join(edge[roads[i]].first, edge[roads[i]].second, component);
    }
    rep(i, 1, Q) cout << res[i] << endl;
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
