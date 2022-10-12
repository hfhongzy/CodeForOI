#include <algorithm>
#include <cstring>
#include <cstdio>
#define mem(x, y) memset(x, y, sizeof x)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, s[N];
struct Node {
   ll fl[3], fr[3]; //c1 = 1, c0 = 0 / 1 / 2
   ll s1, s0, l0, r0, ans, gl[2][2], gr[2][2]; //g[c1 & 1][c0 = 0 / 1]
   void init(int x) {
      mem(fl, 0); mem(fr, 0); mem(gl, 0); mem(gr, 0);
      s1 = ans = x; s0 = l0 = r0 = !x;
      if(x) fl[0] = fr[0] = gl[1][0] = gr[1][0] = 1;
      else gl[0][1] = gr[0][1] = 1;
   }
} t[N << 2];
int range(int l, int r) {
   return l > r ? 0 : r - l + 1;
}
Node operator + (const Node &a, const Node &b) {
   Node u;
   u.s0 = a.s0 + b.s0; u.s1 = a.s1 + b.s1;
   u.l0 = a.s1 ? a.l0 : a.s0 + b.l0;
   u.r0 = b.s1 ? b.r0 : b.s0 + a.r0;
   for(int i = 0; i < 3; i ++) {
      u.fl[i] = a.fl[i];
      if(a.s1 == 1) {
         if(i == 2) u.fl[i] += range(2 - a.s0, b.l0);
         else u.fl[i] += (1 <= i - a.s0 && i - a.s0 <= b.l0);
      } else if(a.s1 == 0) {
         if(i == 2) {
            for(int j = 0; j < 3; j ++) if(a.s0 + j >= 2) {
               u.fl[i] += b.fl[j];
            }
         } else {
            for(int j = 0; j < 3; j ++) if(a.s0 + j == i) {
               u.fl[i] += b.fl[j];
            }
         }
      }
   }
   for(int i = 0; i < 3; i ++) {
      u.fr[i] = a.fr[i];
      if(b.s1 == 1) {
         if(i == 2) u.fr[i] += range(2 - b.s0, a.r0);
         else u.fr[i] += (1 <= i - b.s0 && i - b.s0 <= a.r0);
      } else if(b.s1 == 0) {
         if(i == 2) {
            for(int j = 0; j < 3; j ++) if(b.s0 + j >= 2) {
               u.fr[i] += a.fr[j];
            }
         } else {
            for(int j = 0; j < 3; j ++) if(b.s0 + j == i) {
               u.fr[i] += a.fr[j];
            }
         }
      }
   }
   for(int i = 0; i < 2; i ++) {
      for(int j = 0; j < 2; j ++) {
         u.gl[i][j] = a.gl[i][j];
         if(j >= a.s0) u.gl[i][j] += b.gl[i ^ (a.s1 & 1)][j - a.s0];
      }
   }
   for(int i = 0; i < 2; i ++) {
      for(int j = 0; j < 2; j ++) {
         u.gr[i][j] = b.gr[i][j];
         if(j >= b.s0) u.gr[i][j] += a.gr[i ^ (b.s1 & 1)][j - b.s0];
      }
   }
   u.ans = a.ans + b.ans;
   u.ans += (a.fr[2] + a.fr[1]) * b.l0;
   if(b.l0 >= 2) u.ans += a.fr[0] * (b.l0 - 1);
   u.ans += (b.fl[2] + b.fl[1]) * a.r0;
   if(a.r0 >= 2) u.ans += b.fl[0] * (a.r0 - 1);
   for(int i = 0; i < 2; i ++) {
      for(int j = 0; j < 2; j ++) {
         for(int k = 0; k < 2; k ++) if(j + k <= 1) {
            u.ans += a.gr[i][j] * b.gl[i ^ 1][k];
         }
      }
   }
   return u;
}
void build(int u, int l, int r) {
   if(l == r) {
      t[u].init(s[l]);
      return ;
   }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   t[u] = t[u << 1] + t[u << 1 | 1];
}
void modify(int u, int l, int r, int x) {
   if(l == r) {
      t[u].init(s[l]);
      return ;
   }
   int mid = (l + r) >> 1;
   if(x <= mid) modify(u << 1, l, mid, x);
   else modify(u << 1 | 1, mid + 1, r, x);
   t[u] = t[u << 1] + t[u << 1 | 1];
}
Node query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return t[u];
   int mid = (l + r) >> 1;
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) scanf("%d", s + i);
   build(1, 1, n);
   scanf("%d", &m);
   for(int i = 0; i < m; i ++) {
      int op, u, l, r;
      scanf("%d", &op);
      if(op == 1) {
         scanf("%d", &u); s[u] ^= 1; modify(1, 1, n, u);
      }
      if(op == 2) {
         scanf("%d%d", &l, &r);
         printf("%lld\n", (r - l + 1) * (r - l + 2ll) / 2 - query(1, 1, n, l, r).ans);
      }
   }
   return 0;
}