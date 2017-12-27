#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
string s, t; int j;
int F[1010101];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t >> s; 
	t = " " + t;
	s = " " + s;
	//----------------------
	j = F[1] = 0;
	rep(i, 2, s.size() - 1) {
		while(j > 0 && s[j + 1] != s[i]) j = F[j];
		if (s[j + 1] == s[i]) j++;
		F[i] = j;
	}
	j = 0;
	rep(i, 1, t.size() - 1) {
		while(j > 0 && s[j + 1] != t[i]) j = F[j];
		if (s[j + 1] == t[i]) j++;
		if (j == s.size()) {
			cout << i - j + 1 << " "; j = F[j];
		}
	}
	return 0;
}
