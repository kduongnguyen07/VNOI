#include <iostream>
#include <cstring>
#include <bitset>
#include <stdio.h>
#include <vector>
#include <queue>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 n, m, s, ans, d[10101], L[10101];
vector<vector<int32>> adj;
bitset<10101> F[10101], visited;

int main() {
	scanf("%ld %ld %ld", &n, &m, &s);
	adj.assign(n + 2, vector<int32>());
	rep(i, 1, m) {
		int32 u, v; scanf("%ld %ld", &u, &v);
		if (!F[u][v]) {
			F[u][v] = true;
			adj[u].push_back(v);
		}
	}
	//
	queue<int32> q;
	q.push(s); d[s] = 0;
	visited[s] = true;
	memset(d, 0, sizeof d);
	while(!q.empty()) {
		int32 u = q.front(); q.pop();
		loop(v, adj[u]) {
			if (visited[v]) continue;
			d[v] = d[u] + 1;
			visited[v] = true;
			q.push(v);
		}
	}
	q = queue<int32>();
	memset(L, 0, sizeof L);
	visited.reset();
	q.push(s); L[s] = 1;
	visited[s] = true;
	while(!q.empty()) {
		int32 u = q.front(); q.pop();
		loop(v, adj[u]) {
			if (L[v] < 2 && d[v] == d[u] + 1) L[v] += L[u];
			if (!visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
	rep(i, 1, n) if (i != s && L[i] >= 2) ans++;
	printf("%ld", ans);
	return 0;
}
