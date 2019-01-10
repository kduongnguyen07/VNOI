#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;

int32 T, n, m, w, d[110];
vector<pii> adj[110];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main() {
    scanf("%ld", &T);
    while(T--) {
        scanf("%ld %ld %ld", &n, &m, &w);
        rep(i, 1, n) adj[i].clear();
        rep(i, 1, m) {
            int32 u, v, c;
            scanf("%ld %ld %ld", &u, &v, &c);
            adj[u].push_back(pii(v, c));
            adj[v].push_back(pii(u, c));
        }
        pq = priority_queue<pii, vector<pii>, greater<pii>>();
        memset(d, 0x3f3f, sizeof d);
        d[n] = 0; pq.push(pii(0, n));
        while(!pq.empty()) {
            pii top = pq.top(); pq.pop();
            int32 du, u; u = top.se, du = top.fi;
            //if (du > d[u]) continue;
            if (u == 1) {
                printf("%ld\n", d[1]);
                break;
            }
            loop(it, adj[u]) {
                int32 v, c; v = it.fi, c = it.se;
                if (d[u] + c <= w) { //Co the mang 1 lan
                    if (d[v] > d[u] + c) {
                        d[v] = d[u] + c;
                        pq.push(pii(d[v], v));
                    }
                } else { //Khong the di het 1 lan
                    if (2 * c > w) continue;
                    // du - (w - c): so nuoc con lai de di vong
                    // w - 2 * c: chi phi moi lan di roi ve la 2 * c => chi co them dem w - 2 * c nuoc theo
                    int32 t = (d[u] + c - w) / (w - 2 * c);
                    if ((d[u] + c - w) % (w - 2 * c) != 0) t++;
                    int32 f = d[u] + c + t * (c * 2);
                    if (d[v] > f) {
                        d[v] = f;
                        pq.push(pii(f, v));
                    }
                }
            }
        }
    }
    return 0;
}
