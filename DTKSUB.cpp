#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define MOD 1000000007ll

ll pow[50505], hashS[50505];
int n, k, ans = 0;
string s;

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	cin >> s;
}

void Init() {
	s = " " + s;
	pow[0] = 1; hashS[0] = 0;
	rep(i, 1, n) {
		pow[i] = (pow[i - 1] * 31) % MOD;
		hashS[i] = (hashS[i - 1] * 31 + (s[i] - 'a')) % MOD;
	}
}

ll gethash(int i, int j) {
	return (hashS[j] - hashS[i - 1] * pow[j - i + 1] + MOD * MOD) % MOD;
}

void Compute() {
	int l, r, mid, dem; bool OK = false;
	l = 1; r = n; mid = (l + r) >> 1;
	while (l <= r) {
	    vector<ll> tmp; vector<ll>::iterator it;
		rep(i, 1, n - mid + 1) tmp.push_back(gethash(i, i + mid - 1));
		sort(tmp.begin(), tmp.end());
		dem = 1; OK = false;
		for (it = tmp.begin() + 1; it != tmp.end(); it++) {
			if (*it == *(it - 1)) dem++;
			else dem = 1;
			if (dem >= k) {
				OK = true; break;
			}
		}
		if (OK || dem == k) {
			if (mid > ans) ans = mid;
			l = mid + 1;
		} else r = mid - 1;
		mid = (l + r) >> 1;
	}
}

void Output() {
	cout << ans;
}

int main() {
	Input();
	Init();
	Compute();
	Output();
	return 0;
}
