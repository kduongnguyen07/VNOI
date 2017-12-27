#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;
#define fi "BWPOINTS.INP"
#define fo "BWPOINTS.OUT"
#define maxn long(2e5 + 10)
ifstream f; ofstream _f;
int n;
pair<int, int> a[maxn];
bool _free[maxn];

int main() {
	//f.open(fi); _f.open(fo);
	//f >> n;
	cin >> n;
	memset(_free, true, sizeof(_free));
	for (int i = 1; i <= n; i++) {cin >> a[i].first; a[i].second = 0;}
	for (int i = 1; i <= n; i++) {cin >> a[i + n].first; a[i + n].second = 1;}
	sort(a + 1, a + (2 * n) + 1);
	int k = 0;
	for (int i = 2; i <= 2 * n; i++) {
		if (a[i].second != a[i - 1].second && _free[i - 1]) {
			_free[i] = false;
			k++;
		}
	}
	//_f << k;
	cout << k;
	//f.close(); _f.close();
	return 0;
}
