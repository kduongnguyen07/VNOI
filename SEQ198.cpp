#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
using namespace std;

int a[10101], _free[200];
int m, ans = 0;

int main() {
	cin >> m; for (int i = 1; i <= m; i++) cin >> a[i];
	memset(_free, true, sizeof(_free));
	for (int i = 1; i <= m; i++) {
		for (int j = i + 1; j <= m; j++) {
			if ((abs(float(a[i] - a[j])) == 8 || abs(float(a[i] - a[j])) == 9) && _free[j] && _free[i]) {
				ans++; _free[j] = false;
			}
		}
	}
	cout << ans;
	return 0;
}
