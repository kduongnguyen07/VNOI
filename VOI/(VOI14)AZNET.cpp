#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <functional>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int32, int32> pii;
typedef pair<int32, pii> piii;

struct node {
    int32 u, v, c, idx;
    node() {};
    node(int32 u, int32 v, int32 c, int32 idx): u(u), v(v), c(c), idx(idx) {}
};

int32 n, m, T, best, k;
int32 root[10101], level[10101], A[10101], B[10101];
vector<node> edges;
bool lock[10101], res[10101];

int32 getRoot(int u) { return root[u] == u ? u : root[u] = getRoot(root[u]); }

bool merge(int32 u, int32 v, int32 &k) {
    u = getRoot(u), v = getRoot(v);
    if (u == v) return false;
    k++;
    if (level[u] == level[v]) level[u]++;
    if (level[u] > level[v]) root[v] = u;
    else root[u] = v;
    return true;
}

bool merge(int32 u, int32 v) {
    u = getRoot(u), v = getRoot(v);
    if (u == v) return false;
    if (level[u] == level[v]) level[u]++;
    if (level[u] > level[v]) root[v] = u;
    else root[u] = v;
    return true;
}

int main() {
    //freopen("input.INP", "r", stdin);
    scanf("%ld", &T);
    while(T--) {
        edges.clear();
        scanf("%ld %ld", &n, &m);
        rep(i, 1, n - 1) scanf("%ld", A + i);
        rep(i, 1, n - 1) scanf("%ld", B + i);
        rep(i, 1, m) {
            int32 u, v, c; scanf("%ld %ld %ld", &u, &v, &c);
            edges.push_back(node(u, v, c, i));
        }
        int32 max1, max2; max1 = max2 = 0;
        //max1: so canh thuoc loai 1 toi da them vao cay khung
        //max2: so canh thuoc loai 1 toi thieu them vao cay khung
        /* - Tinh max1 */
        rep(i, 1, n) root[i] = i;
        memset(level, 0, sizeof level);
        memset(lock, false, sizeof lock);
        loop(it, edges) {
            int32 u, v, c;
            u = it.u, v = it.v, c = it.c;
            if (c == 1) merge(u, v, max1);
        }
        /* - Tinh max2 & Danh dau nhung canh loai 1 chac chan thuoc cay khung */
        rep(i, 1, n) root[i] = i;
        memset(level, 0, sizeof level);
        loop(it, edges) {
            int32 u, v, c;
            u = it.u, v = it.v, c = it.c;
            if (c == 2) merge(u, v);
        }
        loop(it, edges) {
            int32 u, v, c;
            u = it.u, v = it.v, c = it.c;
            if (c == 1 && merge(u, v, max2)) lock[it.idx] = true;
        }
        // Solve
        best = 2e9; int32 cur = max2;
        rep(i, 1, n) root[i] = i;
        memset(res, 0, sizeof res);
        memset(level, 0, sizeof level);
        rep(i, max2, max1) {
            if (best > A[i] + B[n - 1 - i]) {
                best = A[i] + B[n - 1 - i];
                k = i;
            }
        }
        loop(it, edges) {
            int32 u, v, c;
            u = it.u, v = it.v, c = it.c;
            if (lock[it.idx] && merge(u, v)) res[it.idx] = true;
        }
        if (cur < k) {
            loop(it, edges) {
                int32 u, v, c;
                u = it.u, v = it.v, c = it.c;
                if (!lock[it.idx] && c == 1 && merge(u, v, cur)) res[it.idx] = true;
                if (cur == k) break;
            }
        }
        loop(it, edges) {
            int32 u, v, c;
            u = it.u, v = it.v, c = it.c;
            if (c == 2 && merge(u, v)) res[it.idx] = true;
        }
        rep(i, 1, m) if (res[i]) printf("%ld ", i);
        printf("\n");
    }
    return 0;
}
