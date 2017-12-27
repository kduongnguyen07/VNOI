#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define fi first
#define se second
int root[10101], a[10101], b[10101];
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<int,piii> piiii;
vector<piiii> edge;
vector<piii> _free;
int n, m, u, v, c, T;
int cta, ctb, ans = 0, dem = 0;

int getR(int p) {
	if (root[p] == p) return p;
	return root[p] = getR(root[p]);
}

void join(int p, int q) {root[getR(p)] = getR(q);}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("AZNET.INP", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		edge.clear(); _free.clear();
		for (int i = 1; i <= n; i++) root[i] = i;
		for (int i = 1; i < n; i++) cin >> a[i];
		for (int i = 1; i < n; i++) cin >> b[i];
		for (int i = 1; i <= m; i++) {
			cin >> u >> v >> c;
			edge.push_back(make_pair((c == 1 ? a[1] : b[1]), make_pair(c, pii(u,v))));
		}
		cta = ctb = 0; a[0] = b[0] = 0;
		sort(edge.begin(), edge.end());
		for (int i = 0, x = 1; x < n - 1; i = 0) {
			u = edge[i].se.se.fi; v = edge[i].se.se.se;
			while (getR(u) == getR(v) && i < edge.size()) {
				i++;
				u = edge[i].se.se.fi; v = edge[i].se.se.se;
			}
			if (getR(u) != getR(v)) {
				join(u,v);
				cta += (edge[i].second.first == 1);
				ctb += (edge[i].second.first == 2);
				ans = a[cta] + b[ctb];
				for (int j = 0; j < edge.size() ; j++) {
					edge[j].first = (edge[j].second.first == 1 ? a[cta] : b[ctb]);
				}
				sort(edge.begin(), edge.end());
				x++;
			}
		}
		cout << ans << " ";
	}
	return 0;
}
