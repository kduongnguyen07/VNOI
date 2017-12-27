#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;
typedef pair<int,int> pii;
vector<pii> tree;
int n, a, b, ans = long(1e9);
int sa[303030], sb[3030300];
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> a >> b;
	tree.push_back(pii(0,0));
	for (int i = 0; i < n; i++) {
		int d, x; cin >> d >> x;
		tree.push_back(pii(d,x));
	}
	sort(tree.begin(), tree.end());
	sa[0] = sb[0] = 0;
	for (int i = 1 ; i <= n; i++) {
		sa[i] = sa[i - 1] + (tree[i].second == 1);
		sb[i] = sb[i - 1] + (tree[i].second == 2);
	}
	for (int i = 1, j = 1; i <= n; i++) {
		while(sa[i] - sa[j - 1] >= a && sb[i] - sb[j - 1] >= b) {
			ans = min(ans, tree[i].first - tree[j].first);
			j++;
		}
	}
	if (ans == long(1e9)) cout << -1;
	else cout << ans;
	return 0;
}
