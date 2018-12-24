#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, Q, adj[550][550], A[550][550], B[550][550];

void Input() {
    cin >> n;
    rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
}

void Init() {
    memset(A, 0, sizeof A); memset(B, 0, sizeof B);
    B[1][1] = adj[1][1];
    rep(i, 2, n) if (i & 1) A[1][i] = A[1][i - 1], B[1][i] = B[1][i - 2] + adj[1][i]; 
        else A[1][i] = A[1][i - 2] + adj[1][i], B[1][i] = B[1][i - 1];
    rep(i, 2, n) if (i & 1) A[i][1] = A[i - 1][1], B[i][1] = B[i - 2][1] + adj[i][1];
        else A[i][1] = A[i - 2][1] + adj[i][1], B[i][1] = B[i - 1][1];
    rep(i, 2, n) rep(j, 2, n) {
        A[i][j] = A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
        B[i][j] = B[i - 1][j] + B[i][j - 1] - B[i - 1][j - 1];
        if (i & 1) {
            if (j & 1) B[i][j] += adj[i][j];
            else A[i][j] += adj[i][j];
        } else {
            if (!(j & 1)) B[i][j] += adj[i][j];
            else A[i][j] += adj[i][j];
        }
    }
}

int query(int u, int v, int x, int y) {
    int res1 = B[x][y] - B[x][v - 1] - B[u - 1][y] + B[u - 1][v - 1];
    int res2 = A[x][y] - A[x][v - 1] - A[u - 1][y] + A[u - 1][v - 1];
    return abs(res1 - res2);
}

void Compute() {
    cin >> Q;
    while(Q--) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        cout << query(u, v, x, y) << endl;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Input();
    Init();
    Compute();
    return 0;
}
