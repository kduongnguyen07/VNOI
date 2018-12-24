#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 n, m, tplt, cnt, numV, crE;
int64 ans;
vector<vector<int32>> adj;
vector<int32> num, low, child;
bool visited[101010];

void dfs(int32 u, int32 p) {
    if (tplt == 1) numV++;
    visited[u] = true;
    num[u] = low[u] = cnt++;
    loop(v, adj[u]) {
        if (v == p) continue;
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            dfs(v, u);
            child[u] += child[v];
            low[u] = min(low[u], low[v]);
            if (low[v] > num[u]) crE++;
        }
    }
}

int main() {
    scanf("%ld %ld", &n, &m);
    adj.assign(n + 2, vector<int32>());
    rep(i, 1, m) {
        int32 u, v; scanf("%ld %ld", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //
    tplt = numV = crE = 0, cnt = 1;
    memset(visited, false, sizeof visited);
    num.assign(n + 2, 0); low.assign(n + 2, 0); child.assign(n + 2, 1);
    rep(i, 1, n) {
        if (!visited[i]) {
            tplt++;
            dfs(i, i);
        }
        if (tplt > 2) {
            printf("0"); return 0;
        }
    }

    if (tplt == 2) {
        //numV so dinh cua tplt 1
        ans = 1LL * numV * (n - numV) * (m - crE);
    } else { //chi co 1 tplt
        // m - crE: so canh co the bo
        //n * n-1 / 2 - m: so canh co the them ( - so canh da co san)
        ans = 1LL * (m - crE) * (1LL * n * (n - 1) / 2 - m);
        rep(i, 2, n) if (num[i] == low[i])
            ans += 1LL * child[i] * (n - child[i]) - 1; // tru di canh cau
    }
    printf("%lld", ans);
    return 0;
}
