#include <iostream>
#include <cstring>
#include <stdio.h>
#include <queue>
#include <vector>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

struct node {
    int32 x, y, t;
    node() {}
    node(int32 x, int32 y): x(x), y(y) {}
    node(int32 x, int32 y, int32 t) : x(x), y(y), t(t) {}
};

const int32 movex[] = {0, 1, 0, 1, 1};
const int32 movey[] = {-1, 0, 1, 1, -1};

int32 n, k;
bool cell[550][550];
int32 A[550][550], B[550][550];
queue<node> Q1, Q2;

void BFS2(int32 timer) {
    while(!Q2.empty()) {
        node top = Q2.front();
        if (top.t > timer) return;
        Q2.pop();
        rep(i, 0, 4) {
            if (i == 2 || i == 3) continue;
            int32 u, v;
            u = top.x + movex[i], v = top.y + movey[i];
            if (cell[u][v] || u > n || v < 1 || B[u][v] == top.t + 1) continue;
            B[u][v] = timer + 1;
            Q2.push(node(u, v, timer + 1));
        }
    }
}

int main() {
    memset(cell, false, sizeof cell);
    scanf("%ld %ld", &n, &k);
    rep(i, 1, k) {
        int32 u, v; scanf("%ld %ld", &u, &v);
        cell[u][v] = true;
    }
    //Solve
    int32 ans = 1e9;
    memset(A, 0, sizeof A);
    memset(B, 0, sizeof B);
    Q1.push(node(1, 1, 0)); Q2.push(node(1, n, 0));
    int32 timer = 0;
    //
    while(!Q1.empty()) {
        node top = Q1.front(); Q1.pop();
        if (top.t == timer) BFS2(timer++);
        rep(i, 0, 4) {
            if (i == 0 || i == 4) continue;
            int32 u, v;
            u = top.x + movex[i], v = top.y + movey[i];
            if (cell[u][v] || u > n || v > n || A[u][v] == top.t + 1)  continue;
            A[u][v] = top.t + 1;
            if (A[u][v] == B[u][v]) {
                printf("%ld", A[u][v]);
                return 0;
            }
            Q1.push(node(u, v, top.t + 1));
        }
    }
    printf("%ld", -1);
    return 0;
}
