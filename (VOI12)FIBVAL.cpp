#include <iostream>
#include <stdio.h>

using namespace std;

int fib[20] = {1, 1};
int T, u, v;

int cal_ans(int u, int v) {
	if (v - u + 1 >= 32) return (v - u + 1) / 16 * 16;
	for (int i = u; i < v; i++) {
		if (fib[i % 16] == fib[(i + 1) % 16]) return 2;
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	for (int i = 2; i < 17; i++)  fib[i] = (fib[i - 1] + fib[i - 2]) % 7;
	cin >> T;
	while(T--) {
		cin >> u >> v;
		cout << cal_ans(u, v) << endl;
	}
	return 0;
}
