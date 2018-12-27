/* Nhan xet: voi canh (u, v) co trong so la w
   neu (u, v) khong thuoc cay khung thi voi cac canh con lai
   co trong so < w se tao dc 1 do thi ma co duong di tu u->v
*/
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int32, int32> pii;
typedef pair<int32, pii> piii;

int T, Q, S;
int32 n, m, k;
int32 root[1010101], level[1010101];
vector<piii> edges;

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
    scanf("%d", &T);
    while(T--) {
        scanf("%ld %ld %d", &n, &m, &Q);
        edges.clear();
        rep(i, 1, m) {
            int32 u, v, c;
            scanf("%ld %ld %ld", &u, &v, &c);
            edges.push_back({c, {u, v}});
        }
        while(Q--) {
            vector<piii> tmp = edges;
            scanf("%ld %d", &k, &S);
            //
            rep(i, 1, n) root[i] = i;
            memset(level, 0, sizeof level);
            rep(i, 1, S) {
                int32 t, c; scanf("%ld %ld", &t, &c);
                tmp[t - 1].first = c;
            }
            loop(it, tmp) {
                int32 u, v, c;
                u = it.second.first, v = it.second.second, c = it.first;
                if (tmp[k - 1].first > c) merge(u, v);
            }
            int32 u, v;
            u = tmp[k-1].second.first, v = tmp[k-1].second.second;
            if (getRoot(u) == getRoot(v)) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
