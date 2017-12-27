#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef pair<int,int> pii;
typedef pair<int, pii> piii;
vector<piii> edge;
int T, n, m, Q, u, v, w, t, c, k, s;
int root[101010];

int getR(int p) {
	if (root[p] == p) return p;
	return root[p] = getR(root[p]);
}

void join(int p, int q) {root[getR(p)] = getR(q);}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	while(T--) {
		 memset(root, 0, sizeof(root));
		 edge.clear();
		 cin >> n >> m >> Q;
		 for (int i = 1; i <= m; i++) {
		 	cin >> u >> v >> w;
		 	edge.push_back(make_pair(w,pii(u,v)));
		 }
		 while(Q--) {
		 	for (int i = 1; i <= n; i++) root[i] = i;
		 	vector<piii> tmp = edge;
		 	cin >> k >> s; k--;
		 	while(s--) {
		 		cin >> t >> c;
		 		t--;
		 		tmp[t].first = c;
		 	}
		 	vector<piii>::iterator it;
		 	for (it = tmp.begin(); it != tmp.end(); it++) {
		 		if (it->first < tmp[k].first) {
		 			if (getR(it->second.first) != getR(it->second.second)) 
		 				join(it->second.first, it->second.second);
		 		}
		 	}
		 	int uk = tmp[k].second.first, vk = tmp[k].second.second;
		 	if (getR(uk) == getR(vk)) cout << "YES\n";
		 	else cout << "NO\n";
		 }
	}
	return 0;
}
