#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define fora(i, a, b) for(int i = a; i <= b; i++)

int m, n;
vector<int> a, b;
int F[1010][1010];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	a.assign(m + 1, 0); b.assign(n + 1, 0); memset(F, 0, sizeof(F));
	fora(i, 1, m) cin >> a[i];
	fora(i, 1, n) cin >> b[i];
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {
				if (i == 1 || j == 1) F[i][j] = 1;
				else F[i][j] = F[i - 2][j - 2] + 1;
			} else F[i][j] = max(F[i][j - 1], F[i - 1][j]);
		}
	}
	cout << F[m][n];
	return 0;
}
