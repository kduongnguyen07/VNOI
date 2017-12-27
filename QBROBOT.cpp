#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> piii;
priority_queue<piii, vector<piii>, greater<piii> > pq;
vector<piii> adj[550];
int d[550], e[550], tram[550];
int n, m, u, v, l, t;

int dijsktra(int w) {
	memset(d, 0x3f, sizeof(d));
	memset(e, 0, sizeof(e));
	e[1] = w; d[1] = 0;
	pq = priority_queue<piii, vector<piii>, greater<piii> >();
	pq.push(make_pair(0, pii(e[1], 1)));
	while(!pq.empty()) {
		piii tmp = pq.top(); pq.pop();
		u = tmp.second.second;
		l = tmp.first;
		if (u == n) return d[n];
		for (int i = 0; i < adj[u].size(); i++) {
			tmp = adj[u][i]; v = tmp.first; int ll = tmp.second.first, tt = tmp.second.second;
			if (e[u] - tt >= 0) {
				if (d[v] > d[u] + ll) {
					d[v] = d[u] + ll;
					e[v] = tram[v] ? w : e[u] - tt;
					pq.push(make_pair(d[v], pii(e[v], v)));
				} else if (d[v] == d[u] + ll) e[v] = max(e[v], e[u]-tt);
			}
		}
	}
	return -1;
}

int main() {
	//freopen("QBROBOT.INP", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> tram[i];
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> l >> t;
		adj[u].push_back(make_pair(v, pii(l, t)));
		adj[v].push_back(make_pair(u, pii(l, t)));
	}
	int t_min = dijsktra(long(1e9));
	int ll = 0, rr = long(1e9);
	int mid = ll+rr>>1, best = 0, temp;
	while(ll <= rr) {
		temp = dijsktra(mid);
		if (temp == t_min) {
			best = mid;
			rr = mid - 1;
		} else ll = mid + 1;
		mid = ll+rr>>1;
	}
	cout << best;
	return 0;
}
