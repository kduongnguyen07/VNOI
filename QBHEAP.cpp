#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {
    //freopen("QBHEAP.INP", "r", stdin);
    priority_queue<int> pq;
    while(!cin.eof()) {
        string s; cin >> s; if (s.empty()) break;
        if (s[0] == '+') {
            s.erase(s.begin());
            istringstream ss(s); int n; ss >> n;
            if (pq.size() < 15000) pq.push(n);
        } else if (!pq.empty()){
            int u = pq.top();
            while(!pq.empty() && pq.top() == u) pq.pop();
        }
    }
    vector<int> A;
    if (pq.empty()) {
        cout << 0; return 0;
    }
    int ans = 1, u; u = pq.top(); pq.pop();
    A.push_back(u);
    while(!pq.empty()) {
        while(!pq.empty() && pq.top() == u) pq.pop();
        if (pq.empty()) break;
        ans++; u = pq.top(); pq.pop(); A.push_back(u);
    }
    cout << ans << endl;
    for (vector<int>::iterator it = A.begin(); it != A.end(); it++) cout << *it << endl;
    return 0;
}
