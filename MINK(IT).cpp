#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long ll;

ll A[171717], ST[171717];
int T, n, k;

void build(int root, int start, int end) {
    if (start == end) ST[root] = A[start];
    else {
        int mid = start + end >> 1;
        build(root * 2, start, mid);
        build(root * 2 + 1, mid + 1, end);
        ST[root] = min(ST[root * 2], ST[root * 2 + 1]);
    }
}

ll query(int root, int start, int end, int u, int v) {
    if (start > end || start > v || end < u) return 2e9;
    if (start >= u && end <= v) return ST[root];
    int mid = start + end >> 1;
    ll p1 = query(root * 2, start, mid, u, v);
    ll p2 = query(root * 2 + 1, mid + 1, end, u, v);
    return min(p1, p2);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while(T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> A[i];
        build(1, 1, n);
        for (int i = 1; i + k - 1 <= n; i++) cout << query(1, 1, n, i, i + k - 1) << " ";
        cout << endl;
    }
    return 0;
}
