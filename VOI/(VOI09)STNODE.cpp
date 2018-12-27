#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
 
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define loop(i, a) for (auto i : a )
 
using namespace std;
 
long int n, m, s, t, ans;
int num[10101], trace[10101], lab[10101];
bool inF[10101], visited[10101];
vector<long int> adj[10101];
vector<int> F;
//bitset<10001> visited;
 
void bfs() {
    bool OK = false;
    //visited &= 0;
    memset(visited, 0, sizeof visited);
    memset(trace, 0, sizeof trace);
    queue<int> q; q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        if (u == t) {
            OK = true; break;
        }
        loop(v, adj[u]) {
            if (!visited[v]) {
                trace[v] = u;
                q.push(v);
            }
        }
    }
    if (!OK) return;
    //visited &= 0;
    memset(visited, 0, sizeof visited);
    int u = t;
    F.push_back(t);
    while(u != s) {
        F.push_back(trace[u]);
        u = trace[u];
    }
    int sizeF = F.size();
    loop(v, F) num[v] = sizeF--, visited[v] = true, inF[v] = true;
    reverse(F.begin(), F.end());
    loop(v, F) lab[++sizeF] = v;
}
 
void dfs(int u) {
    visited[u] = true;
    loop(v, adj[u]) {
        if (!visited[v]) dfs(v);
        if (v != s) num[u] = max(num[u], num[v]);
    }
}
 
int main() {
    scanf("%ld %ld %ld %ld", &n, &m, &s, &t);
    rep(i, 1, m) {
        long int u, v;
        scanf("%ld %ld", &u, &v);
        adj[u].push_back(v);
    }
    // Init
    ans = 0;
    memset(num, 0, sizeof num);
    bfs();
    if (F.empty()) {
        printf("0"); return 0;
    }
    rep(u, 1, n) if (!visited[u]) dfs(u);
    rep(i, 1, F.size()) {
        int u = lab[i];
        loop(v, adj[u]) {
            num[u] = max(num[u], num[v]);
        }
    }
 
    // Solve
    int maxNum = num[s];
    int cur = 2;
    loop(u, F) {
        if (u == s || u == t) continue;
        if(maxNum <= cur) ans++;
        maxNum = max(maxNum, num[u]);
        cur++;
    }
    printf("%ld", ans);
    return 0;
} 