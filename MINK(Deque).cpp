#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i>=b; i--)
int n, k, T;
ll A[171717], R[171717];
vector<int> st;

void Compute() {
    st.clear();
    rep2(i, n, 1) {
        while(!st.empty() && A[st.back()] > A[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back() - 1;
        st.push_back(i);
    }
    int index, next, pivot; index = next = pivot = 1;
    while(pivot <= n - k + 1) {
        next = R[index];
        if (next - pivot + 1 >= k) {
            pivot++;
            cout << A[index] << " "; index = pivot - 1;
        }
        index++;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while(T--) {
        cin >> n >> k;
        rep(i, 1, n) cin >> A[i];
        Compute();
    }
    return 0;
}
