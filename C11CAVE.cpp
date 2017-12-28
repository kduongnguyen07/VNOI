#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)

vector<int> D, U;
int n, h;

void Init() {
    D.assign(h + 1, 0); U.assign(h + 1, 0);
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("C11CAVE.INP", "r", stdin);
    cin >> n >> h;
    int idexu, idexd;
    Init();
    rep(i, 1, n) {
        int tmp; cin >> tmp;
        if (i % 2) D[tmp]++;
        else U[tmp]++;
    }
}

void minimize(int &a, int b) {
    if(b < a) a = b;
}

void Compute() {
    int ans = long(1e9), res = 0;
    rep2(i, h - 1, 1) {
        D[i] += D[i + 1];
        U[i] += U[i + 1];
    }
    rep(i, 1, h) minimize(ans, D[i] + U[h - i + 1]);
    rep(i, 1, h) if (ans == D[i] + U[h - i + 1]) res++;
    cout << ans << " " << res;
}

int main() {
    Input();
    Compute();
    return 0;
}
