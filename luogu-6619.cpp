#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
char gc() {
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
const int N = 2e6 + 10;
struct node {
   int op, t, x, y;
} a[N];
int w[N], n, logn;
struct BIT {
   int bit[N], arr[N], sum;
   void add(int u, int v) {
      sum += v; arr[u] += v;
      for(; u <= n; u += u & (-u)) bit[u] += v;
   }
   int qry(int u) {
      int ans = 0;
      for(; u >= 1; u &= u - 1) ans += bit[u];
      return ans;
   }
} b[2];
int main() {
   int q; read(q);
   rep(i, 1, q) {
      read(a[i].op); read(a[i].t);
      if(a[i].op == 1) {
         read(a[i].x); read(a[i].y);
         w[++ *w] = a[i].x;
      }
   }
   sort(w + 1, w + *w + 1);
   n = unique(w + 1, w + *w + 1) - w;
   for(logn = 0; (1 << (logn + 1)) <= n; logn ++) ;
   rep(i, 1, q) if(a[i].op == 1) a[i].x = lower_bound(w + 1, w + n, a[i].x) - w + a[i].t;
   rep(i, 1, q) {
      if(a[i].op == 1) {
         b[a[i].t].add(a[i].x, a[i].y);
      } else {
         int id = a[i].t;
         b[a[id].t].add(a[id].x, - a[id].y);
      }
      int s0 = 0, s1 = b[1].sum, t = 0;
      per(k, logn, 0) if(t + (1 << k) <= n) {
         if(s0 + b[0].bit[t + (1 << k)] <= s1 - b[1].bit[t + (1 << k)]) {
            t += 1 << k; s0 += b[0].bit[t]; s1 -= b[1].bit[t];
         }
      }
      int ans = s0, a2 = s1 - b[1].arr[t + 1];
      if(a2 >= ans) {
         ans = a2; t = 0; s1 = b[1].sum;
         per(k, logn, 0) if(t + (1 << k) <= n) {
            if(s1 - b[1].bit[t + (1 << k)] >= ans) {
               t += 1 << k; s1 -= b[1].bit[t];
            }
         }
      }
      if(ans == 0) puts("Peace");
      else printf("%d %d\n", w[t], ans * 2);
   }
   return 0;
}