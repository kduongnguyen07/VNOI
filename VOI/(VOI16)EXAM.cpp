#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <sstream>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long long int64;

int64 calVal(int64 A, char op, int64 B) {
    if (op == '+') return A + B;
    if (op == '-') return A - B;
    return A * B;
}

template <typename Type1, typename Type2>
string strBT(Type1 A, char op, Type2 B) {
    stringstream ss;
    ss << '(' << A << op << B << ')';
    return ss.str();
}

int n, dis[2020];
vector<int> adj[2020], matchX, matchY;
map<int64, int> F;
map<int, string> reF;
queue<int> Q;

bool bfs() {
    rep(i, 1, n) if (!matchX[i]) {
        dis[i] = 0;
        Q.push(i);
    } else dis[i] = 1e9;
    dis[0] = 1e9;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        if (dis[u] < dis[0]) {
            loop(v, adj[u]) if (dis[matchY[v]] == 1e9) {
                dis[matchY[v]] = dis[u] + 1;
                Q.push(matchY[v]);
            }
        }
    }
    return dis[0] < 1e9;
}

bool dfs(int u) {
    if (u != 0) {
        loop(v, adj[u]) {
            if (dis[matchY[v]] == dis[u] + 1 && dfs(matchY[v])) {
                matchX[u] = v;
                matchY[v] = u;
                return true;
            }
        }
        dis[u] = 1e9;
        return false;
    }
    return true;
}

void Matching() {
    int res = 0;
    matchX.assign(n + 2, 0);
    matchY.assign(F.size() + 2, 0);
    while(bfs()) {
        rep(i, 1, n) if (!matchX[i] && dfs(i)) res++;
    }
    if (res < n) cout << "NO SOLUTION";
    else rep(i, 1, n) cout << reF[matchX[i]] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("input.INP", "r", stdin);
    cin >> n; cin.ignore();
    //
    vector<vector<int64>> val(n + 2);
    vector<vector<string>> bthuc(n + 2);
    //
    rep(i, 1, n) {
        string s; getline(cin, s);
        int64 tmp[] = {0, 0, 0, 0};
        char oper[4];
        int idx = 0;
        loop(c, s) {
            if (c >= '0' && c <= '9') tmp[idx] = tmp[idx] * 10 + (c - 48);
            else oper[idx++] = c;
        }
        /* Tim tat ca cac cach tinh */
        // 1 toan tu
        if (idx == 1) {
            // A op B
            val[i].push_back(calVal(tmp[0], oper[0], tmp[1]));
            bthuc[i].push_back(s);
        }
        // 2 toan tu
        if (idx == 2) {
            // (A op B) op C
            val[i].push_back(calVal(calVal(tmp[0], oper[0], tmp[1]), oper[1], tmp[2]));
            bthuc[i].push_back(strBT(strBT(tmp[0], oper[0], tmp[1]), oper[1], tmp[2]));
            // A op (B op C)
            val[i].push_back(calVal(tmp[0], oper[0], calVal(tmp[1], oper[1], tmp[2])));
            bthuc[i].push_back(strBT(tmp[0], oper[0], strBT(tmp[1], oper[1], tmp[2])));
        }
        // 3 toan tu
        if (idx == 3) {
            // ((A op B) op C) op D
            val[i].push_back(calVal(calVal(calVal(tmp[0], oper[0], tmp[1]), oper[1], tmp[2]), oper[2], tmp[3]));
            bthuc[i].push_back(strBT(strBT(strBT(tmp[0], oper[0], tmp[1]), oper[1], tmp[2]), oper[2], tmp[3]));
            // (A op (B op C)) op D
            val[i].push_back(calVal(calVal(tmp[0], oper[0], calVal(tmp[1], oper[1], tmp[2])), oper[2], tmp[3]));
            bthuc[i].push_back(strBT(strBT(tmp[0], oper[0], strBT(tmp[1], oper[1], tmp[2])), oper[2], tmp[3]));
            // (A op B) op (C op D)
            val[i].push_back(calVal(calVal(tmp[0], oper[0], tmp[1]), oper[1], calVal(tmp[2], oper[2], tmp[3])));
            bthuc[i].push_back(strBT(strBT(tmp[0], oper[0], tmp[1]), oper[1], strBT(tmp[2], oper[2], tmp[3])));
            // A op ((B op C) op D)
            val[i].push_back(calVal(tmp[0], oper[0], calVal(calVal(tmp[1], oper[1], tmp[2]), oper[2], tmp[3])));
            bthuc[i].push_back(strBT(tmp[0], oper[0], strBT(strBT(tmp[1], oper[1], tmp[2]), oper[2], tmp[3])));
            // A op (B op (C op D))
            val[i].push_back(calVal(tmp[0], oper[0], calVal(tmp[1], oper[1], calVal(tmp[2], oper[2], tmp[3]))));
            bthuc[i].push_back(strBT(tmp[0], oper[0], strBT(tmp[1], oper[1], strBT(tmp[2], oper[2], tmp[3]))));
        }
    }
    int idx = 1;
    rep(i, 1, n) {
        for (int j = 0; j < val[i].size(); j++) {
            if (!F.count(val[i][j])) {
                F.insert({val[i][j], idx});
                reF.insert({idx++, bthuc[i][j]});
            }
            adj[i].push_back(F[val[i][j]]);
        }
    }
    if (idx - 1 < n) {
        cout << "NO SOLUTION"; return 0;
    }
    Matching();
    return 0;
}
