#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <deque>
 
using namespace std;
 
#define rep(i, a, b) for (int i = a; i <= b; i++)
vector<int> adj[10101];
int num[10101], low[10101], danhdau[10101], root[10101];
int n, m, cnt = 0, tplt = 0;
deque<int> dq;
 
void Input() {
	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
	}
}
 
void Init() {
	memset(low, 0, sizeof(low));
	memset(num, 0, sizeof(num));
	memset(danhdau, 0, sizeof(danhdau));
}
 
void dfs(int u) {
	num[u] = low[u] = ++cnt;
	dq.push_back(u);
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++) {
		if (danhdau[*it]) continue;
		if(num[*it]) low[u] = min(low[u], num[*it]);
		else {
			dfs(*it);
			low[u] = min(low[u], low[*it]);
		}
	}
	if (num[u] == low[u]) {
		tplt++;
		int v = -1; root[tplt] = u;
		while(v != u) {
			v = dq.back(); dq.pop_back();
			danhdau[v] = tplt;
		}
	}
}
 
void Tarjan() {
	rep(i, 1, n) if (!num[i]) dfs(i);
}
 
void Compute() {
	int degin[10101], degout[10101];
	memset(degin, 0, sizeof(degin));
	memset(degout, 0, sizeof(degout));
	int u, v; u = v = 0;
	rep(i, 1, n) {
		if (!adj[i].empty()) {
			vector<int>::iterator it;
			for (it = adj[i].begin(); it != adj[i].end(); it++) {
				if (danhdau[*it] != danhdau[i]) {
					degin[danhdau[*it]]++;
					degout[danhdau[i]]--;
				}
			}
		}
	}
    rep(i, 1, tplt) {
    	if (!degout[i]) u = root[i];
    	if (!degin[i]) v = root[i];
    }
 
    if (u && v) cout << "YES\n" << u << " " << v;
    else cout << "NO";
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	Input();
	Init();
	Tarjan();
	Compute();
	return 0;
}
 