#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
void read(int &x) {
    x = 0; char c = getchar();
    for(; !isdigit(c); c = getchar()) ;
    for(; isdigit(c); c = getchar())
        x = x * 10 + (c & 15);
}
struct point { int x, y, w; } a[N], p[N], cur;
int rt, id, ls[N], rs[N], xl[N], xr[N], yl[N], yr[N];
int sz[N], sum[N], st[N], top;
void delnode(int u) { st[++ top] = u; }
int newnode() { return top ? st[top --] : ++ id; }
void upd(int u) {
    xl[u] = xr[u] = a[u].x; yl[u] = yr[u] = a[u].y; sz[u] = 1; sum[u] = a[u].w;
    int t;
    if(t = ls[u]) {
        sz[u] += sz[t]; sum[u] += sum[t];
        xl[u] = xl[u] < xl[t] ? xl[u] : xl[t];
        xr[u] = xr[u] > xr[t] ? xr[u] : xr[t];
        yl[u] = yl[u] < yl[t] ? yl[u] : yl[t];
        yr[u] = yr[u] > yr[t] ? yr[u] : yr[t];
    }
    if(t = rs[u]) {
        sz[u] += sz[t]; sum[u] += sum[t];
        xl[u] = xl[u] < xl[t] ? xl[u] : xl[t];
        xr[u] = xr[u] > xr[t] ? xr[u] : xr[t];
        yl[u] = yl[u] < yl[t] ? yl[u] : yl[t];
        yr[u] = yr[u] > yr[t] ? yr[u] : yr[t];
    }
}
int ban, bd, len, x1, y1, x2, y2, A, cmpd;
bool operator < (const point &a, const point &b) {
    if(cmpd) return a.y < b.y || (a.y == b.y && a.x < b.x);
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
void rebuild(int &u, int l, int r, int d) {
    if(l > r) { u = 0; return ; }
    int mid = (l + r) >> 1; u = u == ban ? u : newnode();
    cmpd = d; nth_element(p + l, p + mid, p + r + 1);
    rebuild(ls[u], l, mid - 1, d ^ 1); rebuild(rs[u], mid + 1, r, d ^ 1);
    a[u] = p[mid]; upd(u);
}
void insert(int &u, int d = 0) {
    if(u == 0) {
        a[u = newnode()] = cur; upd(u); return ;
    }
    if(x1 == a[u].x && y1 == a[u].y) {
        a[u].w += A; upd(u); return ; 
    }
    cmpd = d;
    insert(cur < a[u] ? ls[u] : rs[u], d ^ 1); upd(u);
    if(max(sz[ls[u]], sz[rs[u]]) > 0.65 * sz[u] + 1) ban = u, bd = d;
}
void beat(int u) {
    if(u == 0) return ;
    if(u ^ ban) delnode(u);
    beat(ls[u]); p[++ len] = a[u]; beat(rs[u]);
}
void rebuild(int u) {
    if(u == 0) return ;
    len = 0; beat(u); rebuild(u, 1, len, bd); assert(top == 0);
}
int las;
void query(int u) {
    if(u == 0 || xr[u] < x1 || x2 < xl[u] || yr[u] < y1 || y2 < yl[u]) return ;
    if(x1 <= xl[u] && x2 >= xr[u] && y1 <= yl[u] && y2 >= yr[u]) { las += sum[u]; return ; }
    if(x1 <= a[u].x && x2 >= a[u].x && y1 <= a[u].y && y2 >= a[u].y) las += a[u].w;
    query(ls[u]); query(rs[u]);
}
int main() {
    read(las); las = 0;
    for(int op; read(op), op != 3; ) {
        if(op == 1) {
            read(x1), read(y1), read(A);
            x1 ^= las, y1 ^= las, A ^= las;
            cur = (point) {x1, y1, A};
            ban = 0; insert(rt); rebuild(ban);
        }
        if(op == 2) {
            read(x1), read(y1), read(x2), read(y2);
            x1 ^= las, y1 ^= las, x2 ^= las, y2 ^= las;
            las = 0; query(rt);
            printf("%d\n", las);
        }
    }
    return 0;
}
﻿