#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define rep(i, a, b) for (int i = a;i <= b; i++)
#define coso 31

typedef long long ll;
const ll base = 1000000007;
string s, t;
ll pow[1010101], hasht[1010101];
ll hashs = 0;

ll gethash(int i, int j) {
	return (hasht[j] - hasht[i - 1] * pow[j - i + 1] + base * base) % base;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t >> s;
	int m, n; m = t.size(); n = s.size();
	t = " " + t;
	s = " " + s;
	pow[0] = 1;
	//-----------------------------
	rep(i, 1, n) hashs = ((s[i] - 'a') + coso * hashs) % base;
	rep(i, 1, m) pow[i] = (pow[i - 1] * coso) % base;
	rep(i, 1, m) hasht[i] = (hasht[i - 1] * coso + (t[i] - 'a')) % base;
	rep(i, 1, m - n + 1) 
		if (hashs == gethash(i, i + n - 1)) {
			cout << i << " ";
		}
	return 0;
}
