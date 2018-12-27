#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

int n;
string A, B, C, revA, revB, best = " ";
char maxS[202020], minS[202020];
bool lock[202020];

bool check(string k) {
    string revk = k;
    rep(i, 1, n) revk[i] = k[n - i + 1];
    return k > A && k > B && revk < revA && revk < revB;
}

bool solve(int u, string tmp, bool OK) {
    rep(i, 1, n) {
        if (lock[i]) continue;
        if (OK) {
            tmp[u] = C[i];
            lock[i] = true;
            if (u < n) solve(u + 1, tmp, true);
            else if (check(tmp) && tmp < best) best = tmp;
            lock[i] = false;
        } else if (C[i] >= maxS[u]) {
            tmp[u] = C[i];
            lock[i] = true;
            if (u < n) solve(u + 1, tmp, C[i] > maxS[u]);
            else if (check(tmp) && tmp < best) best = tmp;
            lock[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("input.INP", "r", stdin);
    cin >> n >> A >> B >> C;

    // Init
    string tmp;
    revA = A, revB = B;
    reverse(revA.begin(), revA.end());
    reverse(revB.begin(), revB.end());
    rep(i, 1, n) best += '9';
    tmp = best;
    A = " " + A, revA = " " + revA;
    B = " " + B, revB = " " + revB;
    C = " " + C;
    rep(i, 1, n)
        maxS[i] = max(A[i], B[i]),
        minS[i] = min(revA[i], revB[i]);
    memset(lock, false, sizeof lock);

    // Solve
    solve(1, C, false);
    if (best == tmp) {
        cout << -1; return 0;
    }
    best.erase(best.begin());
    cout << best;
    return 0;
}
