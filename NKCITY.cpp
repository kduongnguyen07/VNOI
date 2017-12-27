#include <iostream>
#include <stdio.h>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;
int root[1010];
vector<piii> edge;
int n, m, u, v, c, ans = 0, dem = 0;

int getR(int p) {
	if (root[p] == p) return p;
	return root[p] = getR(root[p]);
}

void join(int p, int q) {
	root[getR(p)] = getR(q);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> c;
		edge.push_back(make_pair(c, pii(u,v)));
	}
	for (int i = 1; i <= n; i++) root[i] = i;
	sort(edge.begin(), edge.end());
	vector<piii>::iterator it;
	for (it = edge.begin(); it != edge.end(), dem < n - 1; it++) {
		if (getR(it->second.first) != getR(it->second.second)) {
			dem++;
			join(it->second.first, it->second.second);
			ans = max(ans, it->first);
		}
	}
	cout << ans;
	return 0;
}