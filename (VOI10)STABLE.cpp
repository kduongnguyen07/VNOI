#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <queue>

using namespace std;

#define fora(i, a, b) for(int i = a; i <= b; i++)

int n, m, s, u, v, ans = 0;
vector<bool> stable;
vector<int> trace, d, adj[101010];
queue<int> q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("STABLE.INP", "r", stdin);
	cin >> n >> m >> s;
	fora(i, 1, m) {
		cin >> u >> v;
		adj[u].push_back(v);
	}
	trace.assign(n + 1, -1); stable.assign(n + 1, false); d.assign(n + 1, 0);
	trace[s] = s;
	q.push(s);
	while(!q.empty()) {
		u = q.front(); q.pop();
		vector<int>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++) 
			if (trace[*it] != u) {
				if (trace[*it] < 0) {
					q.push(*it);
					trace[*it] = u;
					d[*it] = d[u] + 1;
					stable[*it] = stable[u];
				} else if (d[u] + 1 == d[*it]) stable[*it] = true;
			}
	}
	fora(i, 1, n) if (stable[i]) ans++;
	cout << ans;
	return 0;
}
