#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define MOD 1000000007ll

int n, m, Q;
string s, t;
ll pow[1010101], hashS[1010101], hashT[1010101];

void Input() {
    //freopen("VOSTR.INP", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	cin >> s >> t;
	cin >> Q;
}

void Init() {
    s = " " + s; t = " " + t;
    hashS[0] = hashT[0] = 0; pow[0] = 1;
    rep(i, 1, n) hashS[i] = ((s[i] - 'a') + hashS[i - 1] * 31) % MOD;
    rep(i, 1, m) hashT[i] = ((t[i] - 'a') + hashT[i - 1] * 31) % MOD;
    rep(i, 1, max(m, n)) pow[i] = (pow[i - 1] * 31) % MOD;
}

ll gethashS(int i, int j) {
    return (hashS[j] - hashS[i - 1] * pow[j - i + 1] + MOD * MOD) % MOD;
}

ll gethashT(int i, int j) {
    return (hashT[j] - hashT[i - 1] * pow[j - i + 1] + MOD * MOD) % MOD;
}

void Compute() {
    int u, v, x, y;
    cin >> u >> v >> x >> y;
    /*-----------------*/
    if (v - u > y - x) {
        cout << '>'; return;
    } else if (v - u < y - x) {
        cout << '<'; return;
    }

    if (gethashS(u, v) == gethashT(x, y)) {
        cout << '='; return;
    } else {
        int l, r, mid;
        l = 0; r = v - u; mid = (l + r) >> 1;
        while(l <= r) {
            if (gethashS(u, u + mid - 1) == gethashT(x,x + mid - 1)) {
                if (s[u + mid] != t[x + mid]) {
                    if (s[mid + u] < t[mid + x]) cout << '<';
                    else cout << '>';
                    return;
                }
                l = mid + 1;
            } else r = mid - 1;
            mid = (l + r) >> 1;
        }
    }
}

int main() {
	Input();
	Init();
	while (Q--) Compute();
	return 0;
}
