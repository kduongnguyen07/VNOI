#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define rep(i, a, b) for (int i= a; i <= b; i++)
typedef pair<int, int> pii;

int n;
bool _free[5050];
struct pack{ int a, b, index; };
vector<pack> coin;

bool cmp(const pack &a, const pack &b) {
    return a.a < b.a;
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    coin = vector<pack> (n);
    rep(i, 0, n - 1) coin[i].index = i + 1;
    rep(i, 0, n - 1) cin >> coin[i].a;
    rep(i, 0, n - 1) cin >> coin[i].b;
}

void Init() {
    sort(coin.begin(), coin.end(), cmp);
    memset(_free, 0, sizeof(_free));
}

void Compute() {
    int ans = 0;
    vector<int> st;
    priority_queue<pii> pq;
    rep(i, 0, n - 1) {
        pq.push(pii(coin[i].b, i));
        if (i % 2 == 0) {
            pii tmp = pq.top(); pq.pop();
            ans += tmp.first;
            _free[tmp.second] = true;
        }
    }
    cout << ans << endl;
    rep(i, 0, n - 1) {
        if (_free[i]) st.push_back(coin[i].index);
        else {
            cout << coin[i].index << " " << st.back() << '\n';
            st.pop_back();
        }
    }
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
