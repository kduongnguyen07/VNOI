#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)

typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef long long ll;

ll ans = 0;
int n, m, u, v, c;
pii ancestor[101010][20];
vector<piii> edge;
vector<int> root, h;
vector<bool> inTree;
vector<pii> adj[101010];

int getRoot(int p) {
    if (root[p] == p) return p;
    return root[p] = getRoot(root[p]);
}

void join(int p, int q) {root[getRoot(p)] = getRoot(q);}

void dfs(int u, int p) {
	vector<pii>::iterator it;
	for (it = adj[u].begin(); it != adj[u].end(); it++) {
		v = it->first; c = it->second;
		if (v == p) continue;
		h[v] = h[u] + 1;
		ancestor[v][0] = pii(u, c);
		rep(i, 1, trunc(log2(h[v])) + 1) {
			ancestor[v][i].first = ancestor[ancestor[v][i - 1].first][i - 1].first;
			ancestor[v][i].second = min(ancestor[ancestor[v][i - 1].first][i - 1].second, ancestor[v][i - 1].second); 
		}
		dfs(v, u);
	}
}

pii lca(int u, int v) {
	pii res; res.second = long(1e9);
	if (h[v] > h[u]) swap(v, u);
	ll dis = h[u] - h[v];
	rep2(i, trunc(log2(h[u])) + 1, 0) {
		if ((dis >> i) & 1) {
			res.second = min(res.second, ancestor[u][i].second);
			u = ancestor[u][i].first;
		}
	}
	res.first = u;
	if (u == v) return res;
	rep2(i, trunc(log2(h[u])) + 1, 0) {
		if (ancestor[u][i].first != ancestor[v][i].first) {
    		res.second = min(res.second, min(ancestor[u][i].second, ancestor[v][i].second));
    		u = ancestor[u][i].first; v = ancestor[v][i].first;
		}
	}
	res.first = ancestor[u][0].first;
	res.second = min(res.second, min(ancestor[u][0].second, ancestor[v][0].second));
	return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    root.assign(n + 1, 0); inTree.assign(m + 1, false); h.assign(n + 1, 0);
    rep(i, 1, n) root[i] = i;
    rep(i, 1, m) {
    	cin >> u >> v >> c;
    	edge.push_back(make_pair(c, pii(u, v)));
    }
    sort(edge.begin(), edge.end(), greater<piii>());
    /*----------Kruskal-----------*/
    rep(i, 0, m - 1) {
    	u = edge[i].second.first; v = edge[i].second.second; c = edge[i].first;
    	if(getRoot(u) != getRoot(v)) {
    		join(u, v);
    		inTree[i] = true;
    		adj[u].push_back(pii(v, c));
    		adj[v].push_back(pii(u, c));
    	}
    }
    //-----------Query-------------//
    h[1] = 1;
    dfs(1, 1);
    rep(i, 0, m - 1) {
        if (!inTree[i]) {
            pii tmp = lca(edge[i].second.first, edge[i].second.second);
            ans += max(0, tmp.second - edge[i].first);
        }
    }
    cout << ans;
    //-----------End--------------//
    return 0;
}
