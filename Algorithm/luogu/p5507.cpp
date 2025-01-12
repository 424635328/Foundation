//P5507 机关
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

long long read() {
    long long n = 0; char c = getchar(); bool f = 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') { f = 1; c = getchar(); }
    while (c >= '0' && c <= '9') { n = n * 10 + c - '0'; c = getchar(); }
    return f ? -n : n;
}
void write(long long n) {
    if (n == 0) { putchar('0'); return; }
    if (n < 0) { putchar('-'); n = -n; }
    char res[25]; int t = 0;
    while (n) { res[t++] = n % 10 + '0'; n /= 10; }
    while (t--) putchar(res[t]);
}

const int l[] = {0, 3, 2, 1};
int dis1[1 << 12];
void pre() {
    for (int i = 0; i < 1 << 12; i++) {
        int ans = 0, t;
        for (int j = 0; j < 6; j++) {
            t = ((i & (3 << (j * 2))) >> (j * 2));
            t = -t;
            if (t < 0) t += 4;
            ans += t;
        }
        dis1[i] = ans;
    }
}

struct game {
    int st, move;
    int used;
    game(int s, int u) {
        st = s;
        used = u * 2;
        move = dis1[s >> 12] + dis1[s & 0xfff];
    }
    game() {}
};

bool operator>(const game &a, const game &b) {
    if (a.move + a.used == b.move + b.used) return a.move > b.move;
    return a.move + a.used > b.move + b.used;
}

priority_queue<game, vector<game>, greater<game>> heap;

int dp[1 << 24], fr[1 << 24], opt[1 << 24];
inline int nx(int st, int p) {
    int t = ((st & (3 << (p * 2))) >> (p * 2));
    st = (st ^ (t << (p * 2)));
    t++;
    t &= 3;
    st = (st ^ (t << (p * 2)));
    return st;
}

int mdf[12][4];
int t, stage, s, nxt;
int sol[1 << 24], c;

int main() {
    pre();
    for (int i = 0; i < 12; i++) {
        t = read();
        t--;
        stage |= (t << (i * 2));
        for (int j = 0; j < 4; j++) {
            t = read();
            t--;
            mdf[i][j] = t;
        }
    }
    s = stage;
    dp[stage] = 1;
    game p = game(stage, 1);
    if (p.move % 2) {
        write(0);
        return 0;
    }
    heap.push(p);
    while (!heap.empty()) {
        p = heap.top();
        heap.pop();
        if (p.st == 0) break;
        if (p.used != dp[p.st] * 2) continue;
        for (int i = 0; i < 12; i++) {
            t = ((p.st & (3 << (i * 2))) >> (i * 2));
            nxt = nx(nx(p.st, i), mdf[i][t]); 
            if (!dp[nxt] || dp[nxt] > dp[p.st] + 1) {
                dp[nxt] = dp[p.st] + 1;
                fr[nxt] = p.st;
                opt[nxt] = i;
                heap.push(game(nxt, dp[nxt])); 
            } 
        } 
    } 
    if (dp[0]) {
        for (int i = 0; i != s; i = fr[i]) {
            sol[c++] = opt[i] + 1;
        }
        write(c); putchar('\n'); 
        for (int i = c - 1; i >= 0; i--) { 
            write(sol[i]); putchar(' '); 
        }
    } else {
        write(0); putchar('\n'); 
    }
}