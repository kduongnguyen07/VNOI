#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long long int64;

const int64 BASE = 1e9 + 7;

int n, m,  F[3030][3030];
string T;

void QHD() {
    int k, ans;
    while(n--) {
        cin >> k; ans = 0;
        rep(i, 1, m / 2) { // do dai xau
            rep(j, 1, m - (i * 2) + 1) //phan tu dau tien
                if (F[j][j + i] - F[j + i][j + i * 2] <= k) ans = max(ans, i);
        }
        cout << ans << endl;
    }
}

void subtask1(vector<int> query) {
    loop(it, query) {
        /* 45/100 */
        int ans = 0;
        rep(k, 1, m / 2) { //do dai xau
            rep(i, 1, m - (k * 2) + 1) { //Phan tu dau
                int cnt = 0;
                rep(j, 1, k) {
                    if (T[i + j - 1] != T[(i + k) + j - 1]) cnt++;
                    if (cnt > it) break;
                }
                if (cnt <= it) {
                    ans = max(ans, k);
                    break;
                }
            }
        }
        cout << ans << endl;
    }
}

int64 getHash(int i, int j, int64 *hashT, int64 *powT) {
    return (hashT[j] - hashT[i - 1] * powT[j - i + 1] + BASE * BASE) % BASE;
}

void subtask2(vector<int> query) {
    int ans = 0;
    int64 powT[3030], hashT[3030];
    powT[0] = 1, hashT[0] = 0;
    rep(i, 1, m) powT[i] = (powT[i - 1] * 31) % BASE;
    rep(i, 1, m) hashT[i] = (hashT[i - 1] * 31 + (T[i] - 'a' + 1)) % BASE;
    //Solve
    rep(i, 1, m / 2) { //Do dai xau
        rep(j, 1, m - (i * 2) + 1) { //Phan tu bat dau
            if (getHash(j, j + i - 1, hashT, powT) == getHash(j + i, (j + i) + i - 1, hashT, powT)) {
                ans = max(ans, i); break;
            }
        }
    }
    loop(it, query) { //it == 0
        cout << ans << endl;
    }
}

void subtask3(vector<int> query) {
    loop(it, query) {
        int ans = 0;
        rep(i, 1, m / 2) { //Do dai xau
            int chiphi = 0;
            rep(j, 1, i) if (T[j] != T[j + i]) chiphi++;
            if (chiphi <= it) {
                //cout << "YEAH\n";
                ans = max(ans, i); continue;
            }
            rep(k, 2, m - (i * 2) + 1) {
                if (T[k - 1] != T[k - 1 + i]) chiphi--;
                if (T[i + k - 1] != T[k + i * 2 - 1]) chiphi++;
                if (chiphi <= it) {
                    ans = max(ans, i); break;
                }
            }
        }
        cout << ans << endl;
    }
}

void BruteForce() {
    vector<int> query;
    while(n--) {
        int x; cin >> x; query.push_back(x);
    }
    if (m <= 300) subtask1(query);
    else if (*max_element(query.begin(), query.end()) == 0) subtask2(query);
    else subtask3(query);
    //subtask3(query);
}

int main() {
    freopen("VIRUS.INP", "r", stdin);
    freopen("VIRUS.OUT", "w", stdout);
    cin >> n >> T;
    m = T.size(), T = " " + T;
    //QHD
    memset(F, 0, sizeof F); // Mang cong don
    rep2(i, m - 1, 1) {
        rep(j, i + 1, m)
            F[i][j] = (T[i] != T[j]) + F[i + 1][j + 1];
    }
    //Solve
    //QHD(); //100đ
    BruteForce();
    return 0;
}
