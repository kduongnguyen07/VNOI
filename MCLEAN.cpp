#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
typedef pair<int, int> pii;

const int foot[4][2] = {{0, - 1}, {-1, 0}, {0, 1}, {1, 0}};

string adj[101010];
vector<pii> trash;
pii start;
int m, n;

void Input() {
	cin >> m >> n;
	rep(i, 1, m) {
		cin >> adj[i];
		adj[i] = " " + adj[i];
		rep(j, 1, n) 
		    if (adj[i][j] == 'x') trash.push_back(pii(i, j));
		    else if (adj[i][j] == 'o') start = pii(i, j);
	}
}
void Compute() {
	pii cur = start;
	vector<pii>::iterator it;
	rep(i, 1, trash.size() - 1) {
		pii tmp; int minres = 1e9;
		for (it = trash.begin(); it != trash.end(); it++) {
			int u = trash->first, v = trash->second;
			int distmp = dijsktra(cur.first, cur.second, u, v);
			if (distmp < minres) {
				
			}
		}
	}
}

int main() {
	Input();
	Compute();
	return 0;
}