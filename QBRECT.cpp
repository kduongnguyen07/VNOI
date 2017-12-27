#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef pair<int ,int> pii;

#define fi first
#define se second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)

int n, m;
bool adj[1010][1010];;

void Init() {
     memset(adj, 0, sizeof(adj));
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("QBRECT.INP", "r", stdin);
    cin >> m >> n;
    rep(i, 1, m) rep(j, 1, n) cin >> adj[i][j];
}

void Compute() {
     vector<int> L, R, F;
     deque<int> dq; L.assign(n + 1, 0); R.assign(n + 1, 0);
     F.assign(n + 1, 0);
     int ans = 0;
     rep(i, 1, m) {
         rep(j, 1, n) {
             if (!adj[i][j]) F[j] = 0;
             else F[j]++;
         }
         /*----------------*/
         dq = deque<int> ();
         rep(j, 1, n) {
              while(!dq.empty() && F[dq.back()] >= F[j]) dq.pop_back();
              L[j] = dq.empty() ? 0 : dq.back();
              dq.push_back(j);
         }
         /*----------------*/
         dq = deque<int> ();
         rep2(j, n, 1) {
             while(!dq.empty() && F[dq.back()] >= F[j]) dq.pop_back();
             R[j] = dq.empty() ? n + 1 : dq.back();
             dq.push_back(j);
         }
         /*-----Update-----*/
         rep(j, 1, n) ans = max(ans, F[j] * (R[j] - L[j] - 1));
     }
     cout << ans;
}

int main() {
    Init();
    Input();
    Compute();
    return 0;
}
