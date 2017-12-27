#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int n, m, u, v, ans = 0, id;
vector<int> adj[1010101], topo;
vector<bool> _free;

void toposort(int u) {
	_free[u] = false;
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++)
		if (_free[*it]) toposort(*it);
	topo[id] = u;
	id--;
}

void dfs(int u) {
	_free[u] = false;
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++)
		if (_free[*it]) dfs(*it);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("MESSAGE.INP", "r", stdin);
	cin >> n >> m; id = n;
	_free.assign(n + 1, true); topo.assign(n + 1, 0);
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
	}
	for (int i = 1; i <= n; i++) if (_free[i]) toposort(i);
	_free.assign(n + 1, true);
	for (int i = 1; i <= n; i++) 
		if (_free[topo[i]]) {
			ans++;
			dfs(topo[i]);
		}
	cout << ans;
	return 0;
}
