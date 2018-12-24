//start 10;12
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i>= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int32, int32> pii;

struct money{
    int32 a, b, idx;
    money() {}
    money(int32 a, int32 b): a(a), b(b) {}
};

int32 n;
vector<money> T;

bool cmp(money A, money B) {
    return A.a > B.a;
}

void solve() {
    sort(T.begin() + 1, T.begin() + n + 1, cmp);
    //Chac chan khong chon T co a lon nhat
    //Chac chan chon T co a nho nhat
    int32 ans = 0;
    priority_queue<pii> pq;
    bool check[5050];
    memset(check, false, sizeof check);
    rep2(i, n, 1) {
        pq.push(pii(T[i].b, i));
        if (i % 2 == 0) {
            pii top = pq.top(); pq.pop();
            ans += top.first;
            check[top.second] = true;
        }
    }
    queue<int32> res;
    rep(i, 1, n) if (check[i]) res.push(T[i].idx);
    printf("%ld\n", ans);
    rep(i, 1, n) if (!check[i]) {
        printf("%ld %ld\n", T[i].idx, res.front());
        res.pop();
    }
}

int main() {
    scanf("%ld", &n);
    T.assign(n + 2, money());
    rep(i, 1, n) {
        int32 x; scanf("%ld", &x);
        T[i].a = x;
        T[i].idx = i;
    }
    rep(i, 1, n) {
        int32 x; scanf("%ld", &x);
        T[i].b = x;
    }
    //
    solve();
    return 0;
}
