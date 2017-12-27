#include <cstring>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
int adj[101][101];
vector<int> path;
int n, m;

void Init() {
    memset(adj, 0x3f, sizeof(adj));
}

void Input() {
    cin >> n >> m;
    rep(i, 1, m) cin >> path[i];
    rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
}

void minimize(int &a, int b) {
    if (b < a) a = b;
}

void Compute() {
    rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) minimize(adj[i][j], adj[i][k] + adj[k][j]);

}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}
