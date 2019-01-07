#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <queue>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef pair<int, int> pii;

int m, n, timer[1505][1505];
char grid[1505][1505];
pii des[2];
queue<pii> Q, subQ;
bool visited[1505][1505];

const int movex[] = {0, - 1, 0, 1};
const int movey[] = {-1, 0, 1, 0};

bool check(int i, int j) {
    return i >= 1 && i <= m && j >= 1 && j <= n && !visited[i][j];
}

int main() {
    memset(timer, 0, sizeof timer);
    memset(visited, false, sizeof visited);
    scanf("%d %d", &m, &n);
    int cnt = 0;
    rep(i, 1, m) {
        rep(j, 1, n) {
            char x; scanf(" %c", &x);
            //cout << x;
            grid[i][j] = x;
            if (x != 'X') {
                timer[i][j] = 0;
                visited[i][j] = true;
                Q.push({i, j});
                if (x == 'L') des[cnt++] = {i, j};
            } else timer[i][j] = 1e9;
        }
        //cout << endl;
    }
    // Bang tan
    while(!Q.empty()) {
        pii top = Q.front(); Q.pop();
        int x, y; x = top.first, y = top.second;
        rep(i, 0, 3) {
            int u, v; u = x + movex[i], v = y + movey[i];
            if (check(u, v)) {
                if (grid[u][v] == 'X') {
                    visited[u][v] = true;
                    timer[u][v] = min(timer[u][v], timer[x][y] + 1);
                    Q.push({u, v});
                }
            }
        }
    }
    // Move move move !
    int ans = 0;
    memset(visited, false, sizeof visited);
    visited[des[0].first][des[0].second] = true;
    Q.push({des[0].first, des[0].second});
    bool OK = false;
    while(!Q.empty()) {
        pii top = Q.front(); Q.pop();
        int x, y; x = top.first, y = top.second;
        rep(i, 0, 3) {
            int u, v; u = x + movex[i], v = y + movey[i];
            if (check(u, v)) {
                visited[u][v] = true;
                if (u == des[1].first && v == des[1].second) {
                    OK = true; break;
                }
                if (timer[u][v] <= ans) Q.push({u, v});
                else subQ.push({u, v});
            }
        }
        if (OK) break;
        if (Q.empty()) {
            ans++; swap(Q, subQ);
        }
    }
    printf("%ld", ans);
    return 0;
}
