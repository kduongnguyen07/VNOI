#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

struct node {
    int x, y, stt;
    node() {}
    node(int64 x, int64 y): x(x), y(y) {}
    node(int64 x, int64 y, int64 stt): x(x), y(y), stt(stt) {}
    bool operator != (node A) { return this->x != A.x || this->y != A.y || this->stt != A.stt; }
};

const int32 movex[] = {-1, 0, 1, 0};
const int32 movey[] = {0, -1, 0, 1};

int32 n, S, x, y;
string maze[1010];
node trace[10];

void subtask1() {
    int32 stt = 1;
    rep(i, 1, S) {
        int64 u = movex[stt] + x, v = movey[stt] + y;
        if (u <= n && u >= 1 && v <= n && v >= 1) {
            //Trong Maze
            while(maze[v][u] == '#') {
                stt = stt - 1 < 0 ? 3 : stt - 1;
                u = movex[stt] + x, v = movey[stt] + y;
            }
            x = u, y = v;
        } else {
            //Ngoai Maze
            x = u, y = v;
        }
    }
    printf("%ld %ld", x, y);
}

void subtask2() {
    int32 stt = 1;
    int64 u, v;
    bool outMaze = false;
    if (x > n || x < 1) outMaze = true;
    if (x > n || x < 1 || y > n || y < 1) {
        S -= (y - (n + 1));
        if (S < 0) { printf("%ld %d", x, y - S); return; }
        u = movex[stt] + x, v = y - (y - n);
        if (maze[v][u] == '#') {
            printf("%ld %ld", x -= S, n + 1);
            return;
        }
    } else u = x, v = y;

    if(true) {
        int32 idx = 1, timer = 0;
        trace[1] = node(u, v, stt);
        x = u, y = v;
        while(trace[1] != trace[5] && S > 0 && !outMaze) {
            if (idx == 6) idx = 1, timer = 0;
            while(S > 0) {
                u = x + movex[stt], v = y + movey[stt];
                if (maze[v][u] == '#') break;
                x = u, y = v; if (idx != 1) timer++;
                S--;
                if (u > n || u < 1 || v > n || v < 1) {
                    outMaze = true; break;
                }
            }
            if(outMaze) break;
            trace[idx++] = node(u, v, stt);
            stt = stt - 1 < 0 ? 3 : stt - 1;
            if (S == 0) {
                printf("%ld %ld", x, y);
                return;
            }
        }
        if (outMaze) {
            S--;
            if (stt == 1) y -= S;
            if (stt == 0) x -= S;
            if (stt == 2) x += S;
            if (stt == 3) y += S;
            printf("%ld %ld", x, y);
            return;
        } else {
            if (S % timer == 0) {
                printf("%ld %ld", trace[1].x - movex[trace[1].stt], trace[1].y - movey[trace[1].stt]);
                return;
            } else {
                timer = S % timer;
                rep(i, 1, timer) {
                    u = movex[stt] + x, v = movey[stt] + y;
                    while (maze[v][u] == '#') {
                        stt = stt - 1 < 0 ? 3 : stt - 1;
                        u = movex[stt] + x, v = movey[stt] + y;
                    }
                    x = u, y = v;
                }
                printf("%ld %ld", x, y);
            }
        }
    }
}

int main() {
    freopen("ROBOT.INP", "r", stdin);
    freopen("ROBOT.OUT", "w", stdout);
    scanf("%ld %ld %ld %ld", &n, &x, &y, &S);
    rep(i, 1, n) {
        cin >> maze[i];
        maze[i] = " " + maze[i];
    }
    if (S <= 100000) subtask1();
    else subtask2();
    return 0;
}
