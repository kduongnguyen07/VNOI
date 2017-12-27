#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

vector<int> adj[101010];
int n, m, u, v, Count = 0, cnt = 0;
int low[101010], num[101010];
stack<int> s;

int minimize(int &a, int b) {
	if (b < a) a = b;
}

void visit(int u) {
	low[u]= num[u] = ++cnt;
	s.push(u);
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++) {
		if (num[*it]) minimize(low[u], num[*it]);
		else {
			visit(*it);
			minimize(low[u], low[*it]);
		}
	}
	if (low[u] == num[u]) {
		Count++; v = -1;
		while (v != u) {
			v = s.top(); s.pop();
			low[v] = num[v] = long(2e9);
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
	}
	memset(num, 0, sizeof(num));
	for (int i = 1; i <= n; i++) {
		if (!num[i]) visit(i);
	}
	cout << Count;
	return 0;
}
