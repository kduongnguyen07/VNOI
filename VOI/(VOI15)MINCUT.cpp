#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
long long F[1010][1010]; 
int adj[1010][1010];
int m, n, u, v, x, y, T;
long long ans = 2e15;

long long get_val(int u, int v, int x, int y) {
	return F[x][y] - F[x][v - 1] - F[u - 1][y] + F[u - 1][v - 1];
}

void minimize(long long &a, long long b) {
	if (b < a) a = b;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> T;
	rep(i, 1, m) rep(j, 1, n) cin >> adj[i][j];
	/*-----Prepare------*/
	memset(F, 0, sizeof(F)); F[1][1] = adj[1][1];
	rep(i, 2, m) F[i][1] = F[i - 1][1] + adj[i][1];
	rep(j, 2, n) F[1][j] = F[1][j - 1] + adj[1][j];
	rep(i, 2, m) rep(j, 2, n) F[i][j] = F[i - 1][j] + F[i][j - 1] + adj[i][j] - F[i - 1][j - 1];
	/*------------------*/
	while(T--) {
		ans = 2e15;
		cin >> u >> v >> x >> y; 
		int left, right, mid; 
		long long base = get_val(u, v, x, y), tmp;
		/*-----Cut row----*/
		left = u; right = x - 1; mid = (left + right) >> 1;
		while(left <= right) {
			tmp = get_val(u, v, mid, y) * 2 - base;
			if (tmp >= 0) {
				minimize(ans, tmp); right = mid - 1;
			} else {
				minimize(ans, -tmp); left = mid + 1;
			}
			mid = (left + right) >> 1;
		}
		/*-----Cut col----*/
		left = v; right = y - 1; mid = (left + right) >> 1;
		while(left <= right) {
			tmp = get_val(u, v, x, mid) * 2 - base;
			if (tmp >= 0) {
				minimize(ans, tmp); right = mid - 1;
			} else {
				minimize(ans, -tmp); left = mid + 1;
			}
			mid = (left + right) >> 1;
		}
		cout << ans << endl;
	}
	return 0;
} 
