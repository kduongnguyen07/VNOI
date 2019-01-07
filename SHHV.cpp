#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long long int64;

int n, A[22]; int64 k, F[22];
string s;
bool exist[22];

int main() {
    getline(cin, s); cin >> k;
    istringstream ss(s); int cur = 0;
    while (ss >> A[++cur]) {}
    n = cur - 1;

    // Init
    F[0] = F[1] = 1;
    rep(i, 2, 20) F[i] = F[i - 1] * i;

    // Query 1
    memset(exist, false, sizeof exist);
    int64 pos = 0;
    rep(i, 1, n) {
        rep(j, 1, A[i] - 1) if (!exist[j]) pos += F[n - i];
        exist[A[i]] = true;
    }
    cout << pos + 1 << endl;

    // Query 2
    memset(exist, false, sizeof exist);
    k--;
    rep(i, 1, n) {
        int tmp = 0;
        rep(j, 1, n) {
            if (!exist[j]) tmp++;
            if (F[n - i] * tmp > k) {
                cout << j << " ", exist[j] = true;
                k -= F[n - i] * (tmp - 1); break;
            }
        }
    }
    return 0;
}
