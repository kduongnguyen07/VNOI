#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
#define rep(i, a, b) for (ll i = a; i <= b; i++)

ll n, adj[20][20], F[101010][20];

void Input() {
    //freopen("LEM3.INP", "r", stdin);
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    rep(i, 1, n) rep(j, 1, n) adj[i][j] = -1;
    rep(i, 1, n) rep(j, 1, n) cin >> adj[i][j];
}

ll toggle_bit(ll val, ll i) {
    return val ^ (1 << i);
}

bool getbit(ll val, ll i) {
    return val >> i & 1;
}

void Compute() {
    ll high = (1 << n) - 1;
    memset(F, 0, sizeof(F));
    rep(i, 1, high) {
        rep(k, 1, n) {
            F[i][k] = ll(1e16);
            ll prev_ = toggle_bit(i, k - 1); //trang thai trc la trang thai ko co dinh k
            if (prev_ == 0) F[i][k] = 0; //first vertex
            else {
                rep(j, 1, n) if (j != k && adj[j][k] >= 0 && getbit(i, j - 1)) {
                    F[i][k] = min(F[i][k], F[prev_][j] + adj[j][k]);
                }
            }
        }
    }
    ll res = ll(1e16);
    rep(i, 1, n) res = min(res, F[high][i]);
    cout << res;
 }

int main() {
    Input();
    Compute();
    return 0;
}
