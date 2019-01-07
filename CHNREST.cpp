#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 n, m, A[35];
bool menu[15][35];
int64 F[35][60000], p[15]; // 3 ^ 10

int64 solve(int32 u, int32 state) {
    if (u == m) {
        if (state == p[n] - 1) return 0;
        return 1LL * 1e15;
    }
    if (F[u][state] != -1) return F[u][state];
    int64 res = solve(u + 1, state);
    bool OK = true;
    rep(i, 1, n)
        if (menu[i][u + 1] && state / p[i - 1] % 3 == 2) {
            OK = false; break;
        }
    if (OK) { // Chon mon (u + 1)
        int32 nstate = state;
        rep(i, 1, n)
            if (menu[i][u + 1]) nstate += p[i - 1];
        res = min(res, A[u + 1] + solve(u + 1, nstate));
    }
    return F[u][state] = res;
}

int main() {
    cin >> m >> n;
    rep(i, 1, m) cin >> A[i];
    string del; getline(cin, del);
    memset(menu, 0, sizeof menu);
    rep(i, 1, n) {
        string s; getline(cin, s);
        istringstream ss(s);
        int32 x; while(ss >> x) menu[i][x] = true;
    }
    //Init
    memset(F, -1, sizeof F);
    p[0] = 1; rep(i, 1, 10) p[i] = p[i - 1] * 3;
    int64 ans = solve(0, 0);
    if (ans < 1e15) cout << ans << endl;
    else cout << -1 << endl;
    return 0;
}
