#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)

int n, L[1010101], R[1010101], A[1010101];
int res = 0;

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    rep(i, 1, n) cin >> A[i];
}

void updateRes(int i) {
    int edge = R[i] - L[i] + 1;
    if (edge >= A[i]) res = max(res, A[i]);
}

void Compute() {
    vector<int> st;
    rep(i, 1, n) {
        while(!st.empty() && A[st.back()] >= A[i]) st.pop_back();
        L[i] = st.empty() ? 1 : st.back() + 1;
        st.push_back(i);
    }
    st.clear();
    rep2(i, n, 1) {
        while(!st.empty() && A[st.back()] >= A[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back() - 1;
        st.push_back(i);
    }

    rep(i, 1, n) updateRes(i);
    cout << res;
}

int main() {
   Input();
   Compute();
   return 0;
}
