#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;

int n, m, numbering = 0, u, v, res_node = 0, res_edge = 0;
vector<int> adj[101010];
int low[101010], num[101010];
bool CrNode[101010];

void minimize(int &a, int b) {
	if (b < a) a = b;
}

void visit(int u, int p) {
	int numChild = 0;
	low[u] = num[u] = ++numbering;
	vector<int>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++) {
		if (p != *it) {
			if (num[*it]) minimize(low[u], num[*it]);
			else {
				visit(*it, u);
				numChild++;
				minimize(low[u], low[*it]);
				if (low[*it] >= num[*it]) res_edge++;
				if (u == p) {
					if (numChild >= 2) CrNode[u] = true;
				} else {
					if (low[*it] >= num[u]) CrNode[u] = true;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u);
	}
	memset(num, 0, sizeof(num)); memset(CrNode, false, sizeof(CrNode));
	for (int i = 1; i <= n; i++)
		if (!num[i]) visit(i, i);
	for (int i = 1; i <= n; i++) if (CrNode[i]) res_node++;
	cout << res_node << " " << res_edge;
	return 0;
}
