#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> piii;
vector<pii> adj[1010];
int d[1010];
priority_queue<pii, vector<pii>, greater<pii> > pq;
int T, n, m, u, v, c;

int dijsktra(int s) {
	bool f_v = true;
	pq = priority_queue<pii, vector<pii>, greater<pii> > ();
	memset(d, 0x3f, sizeof(d)); d[s] = 0;
	pq.push(pii(0, s));
	while(!pq.empty()) {
		pii tmp = pq.top(); pq.pop();
		vector<pii>::iterator it;
		u = tmp.second; 
		if (u == s && d[u]) return d[s]; 
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			v = it->first; c = it->second;
			if (d[v] > d[u] + c) {
				d[v] = d[u] + c;
				pq.push(pii(d[v], v));
			}
		}
		if (u == s && f_v) {
			d[u] = long(1e9); f_v = false;
		}
	}
	return -1;
}

int main() {
	//freopen("TOURS13.INP", "r", stdin);
	ios::sync_with_stdio(0), cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) adj[i].clear();
		for (int i = 1; i <= m; i++) {
			cin >> u >> v >> c;
			adj[u].push_back(pii(v, c));
		}
		for (int i = 1; i <= n; i++) cout << dijsktra(i) << endl;
	}
	return 0;
}
