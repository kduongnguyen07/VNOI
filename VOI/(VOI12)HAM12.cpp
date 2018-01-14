#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

string gen, sample;
int n, m, k, ans = 0, res = long(2e9);

void minimize(int &a, int b) {if (b < a) a = b;}

int main() {
	cin >> n >> m >> k;
	cin >> gen;
	while(k--) {
		cin >> sample;
		for (auto it = gen.begin(); it != gen.end(); it++) {
			auto i = it;
			ans = 0;
			for (auto j = sample.begin(); j != sample.end(); j++) {
				if (*i != *j) ans++;
				i++; if (i == gen.end()) i = gen.begin();
			}
			minimize(res, ans);
		}
	}
	cout << res;
	return 0;
}
