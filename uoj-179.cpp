#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 44;
const db eps = 1e-8;
const db INF = 1e88;
int n, m, op, idn[N], idm[N];
db a[N][N];
void pivot(int l, int e) {
   swap(idm[l], idn[e]);
   db t = -a[l][e]; a[l][e] = -1;
   rep(i, 0, n)
      if(fabs(a[l][i]) < eps) a[l][i] = 0;
      else a[l][i] /= t;
   rep(i, 0, m) if(i != l) {
      t = a[i][e]; a[i][e] = 0;
      rep(j, 0, n) a[i][j] += a[l][j] * t;
   }
}
db simplex() {
   while(1) {
      int l = m + 1, e = n + 1;
      idm[l] = idn[e] = n + m + 1;
      rep(i, 1, n) if(a[0][i] > eps && idn[i] < idn[e]) e = i;
      if(e == n + 1) return a[0][0];
      db mv = INF, t;
      rep(i, 1, m) if(a[i][e] < -eps) {
         t = - a[i][0] / a[i][e];
         if(t < mv - eps || (t < mv + eps && idm[i] < idm[l])) {
            l = i; mv = t;
         }
      }
      if(l == m + 1) { puts("Unbounded"); exit(0); }
      pivot(l, e);
   }
}
db LP() {
   db mv = 0; int l = 0;
   rep(i, 1, m) if(mv > a[i][0]) { mv = a[i][0]; l = i; }
   rep(i, 1, n) idn[i] = i;
   rep(i, 1, m) idm[i] = n + i;
   if(mv == 0) return simplex();
   static db z[N];
   copy(a[0], a[0] + n + 1, z);
   fill(a[0], a[0] + n + 1, 0);
   idn[++ n] = 0; a[0][n] = -1;
   rep(i, 1, m) a[i][n] = 1;
   pivot(l, n);
   if(simplex() < -eps) { puts("Infeasible"); exit(0); }
   rep(i, 1, m) if(!idm[i]) {
      rep(j, 1, n) if(fabs(a[i][j]) > eps) {
         pivot(i, j); break ;
      }
      break ;
   }
   int e = 0;
   rep(i, 1, n) if(!idn[i]) { e = i; break ; }
   if(e != n) {
      rep(i, 0, m) swap(a[i][e], a[i][n]);
      swap(idn[n], idn[e]);
   }
   n --;
   rep(i, 1, m) if(idm[i] <= n) {
      rep(j, 0, n) a[0][j] += a[i][j] * z[idm[i]];
   }
   rep(i, 1, n) if(idn[i] <= n) a[0][i] += z[idn[i]];
   return simplex();
}
int main() {
   scanf("%d%d%d", &n, &m, &op);
   int t;
   rep(i, 1, n) { scanf("%d", &t); a[0][i] = t; }
   rep(i, 1, m) {
      rep(j, 1, n) { scanf("%d", &t); a[i][j] = -t; }
      scanf("%d", &t); a[i][0] = t;
   }
   printf("%.10Lf\n", LP());
   if(op) {
      static db ans[N];
      rep(i, 1, m) if(idm[i] <= n) ans[idm[i]] = a[i][0];
      rep(i, 1, n) printf("%.10Lf%c", ans[i], " \n"[i == n]);
   }
   return 0;
}