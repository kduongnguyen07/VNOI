#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> piii;
typedef vector<piii> viii;
int T, n, m, k, u, v, l, t;

priority_queue<piii, viii, greater<piii> > pq;
viii adj[101];

int main() {
	cin >> T;
	while(T--) {
		bool OK = false;
		cin >> k >> n >> m;
		for (int i = 0; i <= n; i++) adj[i].clear();
		for (int i = 1; i <= m; i++) {
			cin >> u >> v >> l >> t;
			adj[u].push_back(make_pair(v, pii(l, t)));
		}
		pq = priority_queue<piii, viii, greater<piii> >();
		pq.push(make_pair(0, pii(0, 1)));
		while(!pq.empty()) {
			piii tmp = pq.top(); pq.pop();
			l = tmp.first;
			t = tmp.second.first;
			u = tmp.second.second;
			if (u == n) {
				OK = true;
				break;
			}
			for (int i = 0; i < adj[u].size(); i++) {
				tmp = adj[u][i]; v = tmp.first; int vl = tmp.second.first, vt = tmp.second.second;
				if (t + vt <= k) pq.push(make_pair(l + vl, pii(t + vt, v)));
			}
		}
		if (OK) printf("%d\n", l);
		else printf("%d\n", -1);
	}
	return 0;
}
