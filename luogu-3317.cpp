#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef double db;

const int N = 64;
const db eps = 1e-10;

int n, f[N];
db a[N][N], mat[N][N];
int find(int u) {
   return u == f[u] ? u : f[u] = find(f[u]);
}
bool unite(int u, int v) {
   u = find(u); v = find(v);
   if(u ^ v) return f[u] = v, 1;
   return 0;
}
db gauss(int n, db a[N][N]) {
   db ans = 1;
   rep(i, 2, n) {
      int k = i;
      rep(j, i, n) if(fabs(a[j][i]) > fabs(a[k][i])) k = j;
      if(k != i) {
         ans = -ans;
         rep(j, i, n) swap(a[i][j], a[k][j]);
      }
      if(fabs(a[i][i]) < eps) return 0;
      ans *= a[i][i];
      rep(j, i + 1, n) {
         for(int k = n; k >= i; k --) {
            a[j][k] -= a[i][k] * a[j][i] / a[i][i];
         }
      }
   }
   return ans;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) f[i] = i;
   rep(i, 1, n) rep(j, 1, n) scanf("%lf", a[i] + j);
   db prod = 1;
   rep(i, 1, n) rep(j, i + 1, n) {
      if(fabs(1 - a[i][j]) < eps) {
         if(!unite(i, j)) {
            puts("0.000");
            return 0;
         }
      }
   }
   static int ID[N];
   int c = 0;
   rep(i, 1, n) if(find(i) == i) ID[i] = ++ c;

   rep(i, 1, n) rep(j, i + 1, n) {
      if(a[i][j] > eps && a[i][j] < 1 - eps) {
         if(f[i] == f[j]) {
            prod *= 1 - a[i][j];
            continue ;
         }
         int u = ID[f[i]], v = ID[f[j]];
         db w = a[i][j] / (1.0 - a[i][j]);
         mat[u][u] += w; mat[v][v] += w;
         mat[u][v] -= w; mat[v][u] -= w;
         prod *= 1 - a[i][j];
      }
   }
   printf("%.8f\n", prod * gauss(c, mat));
   return 0;
}