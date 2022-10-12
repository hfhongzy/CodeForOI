#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int L = 1e6;

struct SuffixArray {
   
char s[N];
int rk[N], sa[N], t[N], c[N], a[N], n;
// int h[N], lg[N], st[N][20];
void build() {
   int m = *max_element(s + 1, s + n + 1);
   fill(c + 1, c + m + 1, 0);
   rep(i, 1, n) c[rk[i] = s[i]] ++;
   rep(i, 1, m) c[i] += c[i - 1];
   rep(i, 1, n) sa[c[rk[i]] --] = i;
   for(int k = 1, num = 0; k <= n; k <<= 1, m = num, num = 0) {
      rep(i, n - k + 1, n) t[++ num] = i;
      rep(i, 1, n) if(sa[i] > k) t[++ num] = sa[i] - k;
      fill(c + 1, c + m + 1, 0);
      rep(i, 1, n) c[rk[i]] ++;
      rep(i, 1, m) c[i] += c[i - 1];
      per(i, n, 1) sa[c[rk[t[i]]] --] = t[i];
      copy(rk + 1, rk + n + 1, t + 1); num = rk[sa[1]] = 1;
      rep(i, 2, n) {
         int u = sa[i] + k <= n ? t[sa[i] + k] : 0;
         int v = sa[i - 1] + k <= n ? t[sa[i - 1] + k] : 0;
         rk[sa[i]] = t[sa[i]] == t[sa[i - 1]] && u == v ? num : ++ num;
      }
      if(num == n) break ;
   }
   // for(int i = 1, j = 0; i <= n; i ++) if(rk[i] != 1) {
   //    if(j) j --;
   //    for(int u = sa[rk[i] - 1]; s[u + j] == s[i + j]; j ++);
   //    h[rk[i]] = j;
   // }
   // rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
   // rep(i, 1, n) st[i][0] = h[i];
   // rep(j, 1, lg[n]) rep(i, 1, n - (1 << j) + 1)
   //    st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
// int LCP(int u, int v) {
//    if(u == v) return n - u + 1;
//    u = rk[u]; v = rk[v];
//    if(u > v) swap(u, v);
//    int k = lg[v - u];
//    return max(st[u + 1][k], st[v - (1 << k) + 1][k]); 
// }

} sa;
int n, m, s, A[L + 10];
char ra[N], rb[N], str[N];
void gen() {
   const int mod = 998244353, b = 100000005, r = 20150609;
   A[0] = s;
   rep(i, 1, L) {
      A[i] = (1ll * A[i - 1] * b + r) % mod;
   }
   rep(i, 1, n) str[i] = '0' + (A[i] & 1);
}
void solve(int l, int r, char *res) {
   int n = r - l + 1; sa.n = 2 * n;
   rep(i, 1, n) sa.s[i] = sa.s[n + i] = str[l + i - 1];
   sa.build(); int c = 0;
   rep(i, 1, sa.n) {
      int u = sa.sa[i];
      if(u > n) continue ;
      res[++ c] = sa.s[u + n - 1];
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &s); gen();
   rep(i, 1, m) {
      int *p = &A[n + 4 * (i - 1) + 1];
      int l1 = 1 + *p ++ % n;
      int r1 = 1 + *p ++ % n;
      int l2 = 1 + *p ++ % n;
      int r2 = 1 + *p ++ % n;
      if(l1 > r1) swap(l1, r1);
      if(l2 > r2) swap(l2, r2);
      solve(l1, r1, ra); solve(l2, r2, rb);
      int t = min(r1 - l1 + 1, r2 - l2 + 1), res = 0;
      rep(i, 1, t) if(ra[i] != rb[i]) { res = ra[i] < rb[i] ? -1 : 1; break; }
      if(!res) res = r1 - l1 == r2 - l2 ? 0 : (r1 - l1 > r2 - l2 ? 1 : -1) ;
      printf("%d\n", res);
   }
   return 0;
}