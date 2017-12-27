#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, int> pli;
vector<pii> adj[10101];
ll d[10101], f[10101];
int n, m, u, v, c, _f;
priority_queue<pli, vector<pli>, greater<pli> > pq;
 
ll dijsktra() {
	pq.push(pii(0, 1)); memset(d, 0x3f, sizeof(d));
	memset(f, 0, sizeof(f));
	f[1] = 1;
	d[1] = 0;
	while(!pq.empty()) {
		pli tmp = pq.top(); pq.pop();
		u = tmp.second; ll du = tmp.first;
		//if (d[u] != du) continue;
		if (u == n) return d[n];
		vector<pii>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			v = it->first; c= it->second;
			if (d[v] > d[u] + c) {
				d[v] = d[u] + c;
				f[v] = f[u];
				pq.push(pii(d[v], v));
			} else if (d[v] == d[u] + c) f[v] += f[u];
		}
	}
	return -1;
}
 
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
//	freopen("QBSCHOOL.INP", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> _f >> u >> v >> c;
		adj[u].push_back(pii(v, c));
		if (_f > 1) adj[v].push_back(pii(u, c));
	}
	ll path_min = dijsktra();
	cout << path_min << " " << f[n];
	return 0;
}