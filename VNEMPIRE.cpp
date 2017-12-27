#include <iostream>
#include <vector>
#include <stdio.h>
#include <functional>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int, pii> piii;
struct PLANET {
	int x, y, z;
} A[101010];
int root[101010];
int n, u, v ,dem = 0;
ll ans = 0;
vector<piii> edge;

int getRoot(int p) {
	if (root[p] == p) return p;
	return root[p] = getRoot(root[p]);
} 

void join(int p, int q) {
	root[getRoot(p)] = getRoot(q);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//freopen("VNEMPIRE.INP", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) root[i] = i;
	for (int i = 1; i <= n; i++) cin >> A[i].x >> A[i].y >> A[i].z;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int c = min(abs(A[i].x - A[j].x), abs(A[i].y - A[j].y));
			c = min(c, abs(A[i].z - A[j].z));
			edge.push_back(make_pair(c, pii(i, j)));
		}
	}
	sort(edge.begin(), edge.end());
	vector<piii>::iterator it;
	for (it = edge.begin(); it != edge.end(), dem < n - 1; it++) {
		u = it->second.first; v = it->second.second;
		if(getRoot(u) != getRoot(v)) {
			join(u, v);
			ans += it->first;
			dem++;
		}
	}
	cout << ans;
	return 0;
}
