#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i < b; i++)

ll adj[4][10101], state[15], F[15][10101];
int n, cnt = 0;

void Init() {
    memset(F, 0, sizeof(F));
    rep(i, 0, 15) {
        bool OK = true;
        rep(j, 0, 3) if (((i >> j) & 3) == 3) {
            OK = false; break;
        }
        if (OK) state[cnt++] = i;
    }
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    rep(i, 0, 4) rep(j, 0, n) cin >> adj[i][j];
}

ll sum_col(int _state, int col) {
    ll res = 0;
    rep(i, 0, 4) res += (_state >> i & 1) * adj[i][col];
    return res;
}

void Compute() {
    rep(i, 0, cnt) F[state[i]][0] = sum_col(state[i], 0);
    rep(i, 1, n) {
        rep(j, 0, cnt) {
            ll sum = F[state[j]][i] = sum_col(state[j], i);
            rep(k, 0, cnt) if ((state[j] & state[k]) == 0) {
                F[state[j]][i] = max(F[state[j]][i], F[state[k]][i - 1] + sum);
            }
        }
    }
    ll ans = -1e9, res = adj[0][0];
    rep(i, 0, cnt) ans = max(ans, F[state[i]][n - 1]);
    rep(i, 0, 4) rep(j, 0, n) res = max(res, adj[i][j]);
    cout << (res < 0 ? res : ans);
}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}

