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
struct pairr { int x, y, w; } p[N], cur;
struct point { pairr pa; int ls, rs, xl, xr, yl, yr, sz, sum; } a[N];
int rt, id, st[N], top;
void delnode(int u) { st[++ top] = u; }
int newnode() { return st[top --]; }
void upd(int u, int t) {
    a[u].sz += a[t].sz; a[u].sum += a[t].sum;
    a[u].xl = a[u].xl < a[t].xl ? a[u].xl : a[t].xl;
    a[u].xr = a[u].xr > a[t].xr ? a[u].xr : a[t].xr;
    a[u].yl = a[u].yl < a[t].yl ? a[u].yl : a[t].yl;
    a[u].yr = a[u].yr > a[t].yr ? a[u].yr : a[t].yr;
}
void upd(int u) {
    a[u].sz = 1; a[u].sum = a[u].pa.w;
    a[u].xl = a[u].xr = a[u].pa.x;
     a[u].yl = a[u].yr = a[u].pa.y;
    if(a[u].ls) upd(u, a[u].ls);
    if(a[u].rs) upd(u, a[u].rs);
}
int ban, bd, len, x1, y1, x2, y2, A, cmpd;
bool fir;
bool operator < (const pairr &a, const pairr &b) {
    if(cmpd) return a.y < b.y || (a.y == b.y && a.x < b.x);
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator == (const pairr &a, const pairr &b) {
    return a.x == b.x && a.y == b.y;
}
void sett(point &a, const pairr &p) {
     a.pa = p; a.ls = a.rs = 0;
}
int rebuild(int l, int r, int d) {
    int mid = (l + r) >> 1, u = fir ? (fir = 0, ban) : newnode();
    cmpd = d; nth_element(p + l, p + mid, p + r + 1);
    sett(a[u], p[mid]);
    if(l < mid) a[u].ls = rebuild(l, mid - 1, d ^ 1);
    if(mid < r) a[u].rs = rebuild(mid + 1, r, d ^ 1);
    upd(u); return u;
}
void insert(int &u, int d = 0) {
    if(u == 0) { u = ++ id; sett(a[u], cur); upd(u); return ; }
    if(cur == a[u].pa) { a[u].pa.w += A; a[u].sum += A; return ;  }
    cmpd = d;
    if(cur < a[u].pa) insert(a[u].ls, d ^ 1);
    else insert(a[u].rs, d ^ 1);
    upd(u);
    if(max(a[a[u].ls].sz, a[a[u].rs].sz) > 0.65 * a[u].sz + 1) ban = u, bd = d;
}
void beat(int u) {
    if(u == 0) return ;
    if(u ^ ban) delnode(u);
    beat(a[u].ls); p[++ len] = a[u].pa; beat(a[u].rs);
}
void rebuild(int u) {
    if(u == 0) return ;
    len = 0; beat(u); fir = 1; rebuild(1, len, bd); //assert(top == 0);
}
int las;
void query(int u) {
    if(u == 0 || a[u].xr < x1 || x2 < a[u].xl || a[u].yr < y1 || y2 < a[u].yl) return ;
    if(x1 <= a[u].xl && x2 >= a[u].xr && y1 <= a[u].yl && y2 >= a[u].yr) { las += a[u].sum; return ; }
    if(x1 <= a[u].pa.x && x2 >= a[u].pa.x && y1 <= a[u].pa.y && y2 >= a[u].pa.y) las += a[u].pa.w;
    query(a[u].ls); query(a[u].rs);
}
int main() {
    read(las); las = 0;
    for(int op; read(op), op != 3; ) {
        if(op == 1) {
            read(x1), read(y1), read(A);
            cur = (pairr) {x1, y1, A};
            ban = 0; insert(rt); rebuild(ban);
        }
        if(op == 2) {
            read(x1), read(y1), read(x2), read(y2);
            las = 0; query(rt);
            printf("%d\n", las);
        }
    }
    return 0;
}