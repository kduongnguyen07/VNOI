#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

typedef unsigned long long ll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
vector<pil> adj[110];
priority_queue<pli, vector<pli>, greater<pli> > pq;
pli d[110];
int n, m, u, v;
ll c, res;
double ans = 1e23;

ll disktra(int s) {
	bool first_visit = true;
	pq = priority_queue<pli, vector<pli>, greater<pli> > ();
	for(int i = 1; i <= n; i++) d[i].first = ll(1e23);
	d[s].first = 0; d[s].second = 1;
	pq.push(pli(0, s));
	while(!pq.empty()) {
		pli tmp = pq.top(); pq.pop();
		u = tmp.second;
		if (u == s) return d[u].first;
		vector<pil>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++) {
			v = it->first; c = it->second;
			if (double(d[v].first) / d[v].second > double(d[u].first + c) / (d[u].second + 1)) {
				d[v].first = d[u].first + c;
				d[v].second = d[u].second + 1;
				pq.push(pli(d[v].first, v));
 			}
		}
		if (first_visit) {
			first_visit = false;
			d[s].first = ll(1e23);
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("QBTRANS.INP", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> c;
		adj[u].push_back(pil(v, c));
		adj[v].push_back(pil(u, c));
	}
	for (int i = 1; i <= n; i++) {
		c = disktra(i);
		cout << c << " ";
		if (c != -1 && double(c) / d[i].second  < ans) 
			ans = double(c) / d[i].second;
	}
	cout << fixed << setprecision(2) << ans;
	return 0;
}
