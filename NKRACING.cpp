#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;
typedef pair<int32, pii> piii;

int32 n, m, root[10101], level[10101];
vector<piii> edges;
int32 ans = 0;

int32 getRoot(int32 u) { return root[u] == u ? u : root[u] = getRoot(root[u]); }

bool merge(int32 u, int32 v) {
    u = getRoot(u), v = getRoot(v);
    if (u == v) return false;
    if (level[u] == level[v]) level[u]++;
    if (level[u] > level[v]) root[v] = u;
    else root[u] = v;
    return true;
}

int main() {
    scanf("%ld %ld", &n, &m);
    rep(i, 1, m) {
        int32 u, v, c;
        scanf("%ld %ld %ld", &u, &v, &c);
        edges.push_back({c, {u, v}});
        ans += c;
    }
    sort(edges.begin(), edges.end(), greater<piii>());
    memset(level, 0, sizeof level);
    rep(i, 1, n) root[i] = i;
    loop(it, edges) {
        int32 u, v, c;
        c = it.fi, u = it.se.fi, v = it.se.se;
        if (merge(u, v)) ans -= c;
    }
    printf("%ld", ans);
    return 0;
}
