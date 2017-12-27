#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
vector< vector<int> > adj(401, vector<int>(401, 0));
int n, u, v, c;
long long ans = 0;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	while(n--) {
		cin >> u >> v >> c;
		adj[u + 200][v + 200] = 1 << (c - 1);
	}
	rep(i, 0, 400) {
		rep(j, i + 1, 400) {
			vector<long long> F(16, 0);
			rep(k, 0, 400) {
				if (adj[i][k] && adj[j][k] && adj[i][k] != adj[j][k]) {
					ans += F[15 - adj[i][k] - adj[j][k]];
					F[adj[i][k] + adj[j][k]]++;
				}
			}
		}
	}
	cout << ans;
	return 0;
}
