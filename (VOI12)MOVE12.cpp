#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;
#define maxn long(1e4 + 10)
typedef pair<int, int> pii;
vector<pii> CA;
int n;

priority_queue<pii> Q;
bool check(int k) {
	vector<pii> a;
	for (int i = 0; i < n; i++) {
		int y = CA[i].first + (k / CA[i].second); // ben phai
		int x = CA[i].first - (k / CA[i].second); // ben trai
		a.push_back(pii(x, y));
	}
	sort(a.begin(), a.end());
	int i = 0;
	for (int j = 1; j <= n; j++) {
		while (a[i].first <= j && i < n) {
			Q.push(pii(-a[i].second, a[i].first));
			i++;
		}
		int d = 0;
		if (!Q.empty()){
			d = -Q.top().first;
			Q.pop();
		}
		if (d < j) {
			while (!Q.empty()) Q.pop();
			return false;
		}
	}
	while (!Q.empty()) Q.pop();
	return true;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int c, t; cin >> c >> t;
		CA.push_back(pii(c, t));
	}
	int l = 0, r = long (1e9);
	int mid = (l + r) / 2; int best = 0;
	while(l <= r) {
		if (check(mid)) {
			best = mid;
			r = mid - 1;
		} else l = mid + 1;
		mid = (l + r) / 2;
	}
	cout << best;
	return 0;
}
