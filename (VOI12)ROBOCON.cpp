#include <iostream>
#include <stdio.h>
#include <cstring>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int rbx[] = {0, 1, 1};
int rby[] = {1, 0, 1};
int n, k, x, y, t = 0;
bool adj[510][510]; 
int d1[510][510], d2[510][510];
typedef pair<int,int> pii;
typedef pair<int, pii> piii;
queue<piii> R1, R2;
piii cur, tmp;

void BFS2(int tt) {
	while(!R2.empty()) {
		tmp = R2.front();
		if (tmp.first > tt) return;
		R2.pop();
		for (int i = 0; i < 3; i++) {
			x = tmp.second.first + rbx[i]; y = tmp.second.second - rby[i];
			if (adj[x][y] && d2[x][y] != tt + 1) {
				d2[x][y] = tt + 1;
				R2.push(make_pair(tt + 1, pii(x,y)));
			}
		}
	}
}

int BFS1() {
	R1.push(make_pair(0,pii(1,1)));
	R2.push(make_pair(0,pii(1,n)));
	d1[1][1] = 0; d2[1][n] = 0;
	while(!R1.empty()) {
		cur = R1.front(); R1.pop();
		if (cur.first == t) BFS2(t++);	
		for (int i = 0; i < 3; i++) {
			x = cur.second.first + rbx[i]; y = cur.second.second + rby[i];
			if (adj[x][y] && d1[x][y] != cur.first + 1) {
				d1[x][y] = cur.first + 1;
				if (d2[x][y] == d1[x][y]) return d2[x][y];
				R1.push(make_pair(cur.first + 1, pii(x, y)));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
//	/freopen("ROBOCON.INP", "r", stdin);
	memset(adj, false,sizeof(adj));
	memset(d1,0x3f,sizeof(d1));
	memset(d2,0x3f,sizeof(d2));
	cin >> n >> k;
	for (int i =1 ; i <=n; i++) 
		for(int j = 1; j<=n;j++) adj[i][j] = true;
	for (int i = 1; i <= k; i++) {
		cin >> x >> y;
		adj[x][y] = false;
	}
  	cout << BFS1();
	return 0;
}
