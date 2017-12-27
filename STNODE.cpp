#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, u, v, s, t, ans = 0;
vector<int> adj[10101];
bool _free[10101];
queue<int> Q;
vector<int> findpath() {
	int trace[10101];
	memset(trace, 0, sizeof(trace));	
	vector<int> path;
	Q.clear(); Q.push(s);
	trace[s] = -1;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		if (u == t) break;
		vector<int>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			if (trace[*it] == 0) {
				trace[*it] = u;
				Q.push(*it);
			}
		}
	}
	u = trace[t];
	while (trace[u] != -1) {
		path.push_back(u);
		u = trace[u];
	}
	//reverse(path.begin(), path.end());
	return path;
}

bool bfs() {
	Q.clear();
	Q.push(s);
	bool check[10101];
	memset(check, true, sizeof(check));
	check[s] = false;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		if (u == t) return false;
		vector<int>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			if (_free[*it] && check[*it]) {
				Q.push(*it);
				check[*it] = false;
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v; adj[u].push_back(v);
	}
	vector<int> path = findpath();
	memset(_free, true, sizeof(_free));
	vector<int>::iterator it;
	for (it = path.begin(); it != path.end(); it++) {
		_free[*it] = false;
		if (bfs()) ans++; 
		_free[*it] = true;
	}
	cout << ans;
	return 0;
}
