#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
typedef long long ll;
const ll INF = 1e18 + 50;
const int N = 53;
struct LL {
   ll x;
   void rd() { scanf("%lld", &x); }
   LL() {} LL(ll y) { x = y; }
   LL operator + (LL y) { return LL(x + y.x > INF ? INF : x + y.x); }
   LL operator - (LL y) { return LL(x - y.x); }
   LL operator * (LL y) {
      if(!y.x) return 0;
      if(x > INF / y.x) return INF;
      return LL(x * y.x);
   }
   void operator += (LL y) { *this = *this + y; }
   void operator -= (LL y) { *this = *this - y; }
   void operator *= (LL y) { *this = *this * y; }
   bool operator < (LL y) { return x < y.x; }
   bool operator <= (LL y) { return x <= y.x; }
   bool operator > (LL y) { return x > y.x; }
   bool operator >= (LL y) { return x >= y.x; }
} k, f[N][N][N];
int n, m, p[N];
bool use[N];
int main() {
   scanf("%d%d", &n, &m); k.rd();
   f[0][0][0] = LL(1);
   rep(_n, 1, n) {
      f[_n][0][0] = f[_n - 1][0][0] * LL(_n);
      rep(_m, 0, _n) {
         rep(_k, _m, _n) if(_k) {
            f[_n][_m][_k] = LL(_n - _k) * f[_n - 1][_m][_k - 1];
            if(_m) f[_n][_m][_k] += f[_n - 1][_m - 1][_k - 1];
            if(_k >= 2) f[_n][_m][_k] += LL(_k - 1) * f[_n - 1][_m][_k - 2];
         }
      }
   }
   rep(i, 1, n) {
      int fix = 0, ad = 0;
      rep(j, 1, i - 1) { fix += p[j] == j; ad += p[j] > i; }
      rep(j, 1, n) if(!use[j]) {
         LL cur = f[n - i][m - ( fix + (i == j) )][n - i - ( ad + (j > i) )];
         if(k <= cur) {
            p[i] = j; use[j] = 1; break ;
         } else {
            k -= cur;
         }
      }
      if(!p[i]) { puts("-1"); return 0; }
   }
   if(k.x != 1) { puts("-1"); return 0; }
   rep(i, 1, n) printf("%d ", *(p + i));
   return 0;
}
/*
f[n][m][k] : n位置，m个p[i] = i, 1 ~ k可以匹配。(m <= k)
*/