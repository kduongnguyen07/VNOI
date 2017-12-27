#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <cstring>

using namespace std;

typedef long long ll;
#define base long(1e9)
#define fora(i, a, b) for(int i = a; i <= b; i++)
#define forb(i, a, b) for(int i = b; i >= a; i--)
int n, h, ans = 2;
vector<int> tree;

int find(int x, int k) {
	int res = 0;
	while(x % k == 0) {
		res++;
		x /= k;
	}
	return res;
}

ll fast_power(ll a, int b) {
	if (b == 0) return 1;
	ll tmp = fast_power(a, b / 2); tmp = tmp * tmp % base;
	if (b % 2 == 1) return tmp * a % base;
	return tmp;
}
//Cong thuc Catalan: (2n!)/((n + 1)! * n!) =>> ((n + 2) * .. * 2n) / n!
ll catalan(int k) {
	vector<int> _COUNT(2 * k + 1, 0);
	vector<bool> prime(2 * k + 1, true);
	fora(i, 2, 2 * k) {
		if (prime[i]) {
			int c = 0;
			for (int j = i; j <= 2 * k; j += i) {
				prime[j] = false;
				int tmp = find(j, i);
				if (k + 2 <= j) c += tmp;
				if (j <= k) c -= tmp;
			}
			_COUNT[i] = c;
		}
	}
	ll res = 1;
	fora(i,1,2*k) res = res * fast_power(i, _COUNT[i]) % base;
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> h; tree.assign(n + 1, 0);
	fora(i,1,n) cin >> tree[i];
	forb(i,1,n-1) if (tree[i] < tree[i + 1]) ans++; else break;
	cout << ans << " " << catalan(n + 1);
	return 0;
}
