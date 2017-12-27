#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
int n, r[510][510], c[510][510], tmp, T;
bool F[510][510];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	while(T--) {
		cin >> n;
		memset(r, 0, sizeof(r)); memset(c, 0, sizeof(c)); memset(F, false, sizeof(F));
		rep(i, 1, n) 
	    	rep(j, 1, n) {
           		cin >> tmp; r[i][j] = r[i][j - 1] + tmp; c[i][j] = c[i - 1][j] + tmp;
            	if (r[i][j] % 2 == 0) F[i][j] = !F[i - 1][j];
            	if (c[i][j] % 2 == 0 && !F[i][j]) F[i][j] = !F[i][j - 1];
		}
		cout << (F[n][n] ? "YES" : "NO") << endl;
	}
	return 0;
}
