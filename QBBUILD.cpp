#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int adj[110][110];
vector<int> F;
int n, m, u, v, c, ans = long(1e9);

void minimize(int &a, int b) {
	if (b < a) a = b;
}

void maximize(int &a, int b) {
	if (b > a) a = b;
}

int main() {
	//freopen("QBBUILD.INP", "r", stdin);
	cin >> n;
	memset(adj, 0x3f3f3f, sizeof(adj));
	F.assign(n + 1, 0);
	for (int i = 1; i <= 4; i++) cin >> F[i];
	for (int i = 1; i <= n; i++) adj[i][i] = 0;
	while(!cin.eof()) {
		cin >> u >> v >> c;
	    adj[v][u] = adj[u][v] = c;
	}
	for (int k = 1; k <= n; k++) 
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				minimize(adj[i][j], adj[i][k] + adj[k][j]);
    //------------------------------
	for (int x = 1; x <= n; x++) {
		for(int y = 1; y <= n; y++) {
			for (int i = 1; i <= 4; i++) {
				for (int j = i + 1; j <= 4; j++) {
					int tmp = adj[F[i]][x] + adj[F[j]][x] + adj[x][y];
					for (int k = 1; k <= 4; k++) 
						if (k != i && k != j) tmp += adj[F[k]][y];
					minimize(ans, tmp);
				}			
			}
		}
	}
	cout << ans;
	return 0;
}
