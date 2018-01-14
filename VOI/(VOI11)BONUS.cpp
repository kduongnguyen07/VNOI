#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

int n, k, ans = 0;
int adj[1010][1010], F[1010][1010];

int tinhS(int u, int v, int x, int y) {
	return F[x][y] - F[x][v - 1] - F[u - 1][y] + F[u - 1][v - 1];
}

void maximize(int &a, int b) {
	if (b > a) a = b;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	memset(adj, 0, sizeof(adj));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			cin >> adj[i][j];
	/* prepare */
	F[1][1] = adj[1][1];
	for (int i = 2; i <= n; i++) {
		F[1][i] = F[1][i - 1] + adj[1][i]; F[i][1] = F[i - 1][1] + adj[i][1];
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= n; j++)
			F[i][j] = F[i - 1][j] + F[i][j - 1] + adj[i][j] - F[i - 1][j - 1];
	}
	/*--------*/
	for (int u = 1; u <= n; u++) 
	    for (int v = 1; v <= n; v++)
	    	if (u + k - 1 <= n && v + k - 1 <= n) 
	    		maximize(ans, tinhS(u, v, u + k - 1, v + k - 1));
	cout << ans;
	return 0;
}