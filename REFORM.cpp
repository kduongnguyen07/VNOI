#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
int n, m, u, v, solt = 0, cnt = 0, c1 = 0, cr_edge = 0;
ll res;
vector<int> adj[1010101], low, num, child;
vector<bool> visited;

void visit(int u, int p) {
	if (solt == 1) c1++;
	low[u] = num[u] = ++cnt;
	visited[u] = true;
	child[u] = 1;
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++) {
		if (*it != p) {
			if (num[*it]) low[u] = min(low[u], num[*it]);
			else {
				visit(*it, u);
				low[u] = min(low[u], low[*it]);
				child[u] += child[*it];
				if (low[*it] >= num[*it]) cr_edge++;
			}
		}
	}
}

int main() {
	//freopen("REFORM.INP", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		adj[u].push_back(v); adj[v].push_back(u);
	}
	visited.assign(n + 1, false); low.assign(n + 1, 0); num.assign(n + 1, 0);
	child.assign(n + 1, 0);
	for (int i = 1; i <= n; i++) 
		if (!visited[i]) {
			solt++;
			visit(i, i);
		}
	if (solt > 2) {
		cout << 0; return 0;
	}
	if (solt == 2) {
		res = ll(c1) * ll(n - c1) * ll(m - cr_edge);
	} else {
		res = ll(m - cr_edge) * (ll(n) * ll(n - 1) / 2 - ll(m));
		for (int i = 2; i <= n; i++) if (low[i] == num[i])
			res += ll(child[i]) * ll(n - child[i]) - 1;
	}
	cout << res;
	return 0;
}
