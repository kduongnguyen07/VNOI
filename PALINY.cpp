#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)
typedef long long ll;
const ll MOD = 1000000007;

int n, ans = 0;
string s;
ll hashS[50505], rashS[50505], powS[50505];

void Input() {
	cin >> n >> s;
}

void Init() {
	s = " " + s;
	powS[0] = 1; hashS[0] = rashS[n + 1] = 0;
	rep(i, 1, n) powS[i] = (powS[i - 1] * 31) % MOD;
	rep(i, 1, n) hashS[i] = ((s[i] - 'a') + hashS[i - 1] * 31) % MOD;
    rep2(i, n, 1) rashS[i] = ((s[i] - 'a') + rashS[i + 1] * 31) % MOD;
}

ll gethash(int i, int j) {
	return (hashS[j] - hashS[i - 1] * powS[j - i + 1] + MOD * MOD) % MOD;
}

ll getrash(int i, int j) {
	return (rashS[i] - rashS[j + 1] * powS[j - i + 1] + MOD * MOD) % MOD;
}

bool check(int len) {
	for (int i = 1; i + len - 1 <= n; i++) 
		if (gethash(i, i + len - 1) == getrash(i, i + len - 1)) return true;
	return false;
}

void Compute() {
    int ll, rr, mid, best = 0;
    /*------Even Palindrome-------*/
    ll = 1; rr = n - (n % 2); mid = (ll + rr) >> 1;
    while (ll <= rr) {
        if (mid % 2) mid++;
    	if (check(mid)) {
    		if(mid > best) best = mid;
    		ll = mid + 2;
    	} else rr = mid - 2;
    	mid = (ll + rr) >> 1; 
    }
    ans = best;
    /*------Odd Palindrome-------*/
    ll = 1; rr = n - (n % 2 == 0); mid = (ll + rr) >> 1;
    while(ll <= rr) {
        if (mid % 2 == 0) mid++;
    	if (check(mid)) {
    		if(mid > best) best = mid;
    		ll = mid + 2;
    	} else rr = mid - 2;
    	mid = (ll + rr) >> 1; 
    }
    if (best > ans) ans = best;
}

void Output() {
	cout << ans;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	Input();
	Init();
	Compute();
	Output();
	return 0;
}
