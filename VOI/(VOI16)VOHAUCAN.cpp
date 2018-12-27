#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (auto i = a; i <= b; i++)

ll L, Q, D, K;
ll anpha, beta;
ll curQ, preQ;

int main() {
    cin >> L >> Q >> K >> D;
    //Init
    curQ = preQ = Q;
    anpha = K - 2*D;
    beta = K - D;
    //
    if (L > Q) {
        cout << -1;
        return 0;
    }
    if (K <= 2 * D || Q <= K) {
        if (min(Q, K) >= L) cout << min(Q, K) - L;
        else cout << -1;
        return 0;
    }
    rep(i, 1, L / D) {
        if (preQ < 0) {
            cout << -1; return 0;
        }
        if (preQ <= K) curQ = preQ - D;
        else curQ = (preQ / K - 1) * anpha + beta + max(((preQ % K) - 2 * D), 0ll);
        preQ = curQ;
    }
    if (L % D != 0) {
        D = L % D;
        if (preQ <= K) curQ = preQ - D;
        else curQ = (preQ / K - 1) * anpha + beta + max(((preQ % K) - 2 * D), 0ll);
    }
    if (curQ >= 0) cout << curQ;
    else cout << -1;
    return 0;
}
