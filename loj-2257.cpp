#include <algorithm>
#include <cstdio>
#include <vector>
#define pp(x) __builtin_popcount(x)
using namespace std;
const int N = 1 << 17 | 10, mod = 1e9 + 7;
int n, g, l, q, m, p[10], c[10], cl[10], ans[N], st[N], a[N], pw[N];
vector<int> vec, rv;
int ID(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin(); }
void work(int n) {
   for(int i = 2; i * i <= n; i ++) if(n % i == 0) {
      p[m] = i; c[m] = 0;
      while(n % i == 0) { c[m] ++; n /= i; }
      m ++;
   }
   if(n > 1) { p[m] = n; c[m] = 1; m ++; }
   n = g;
   for(int i = 0; i < m; i ++) {
      while(n % p[i] == 0) { n /= p[i]; cl[i] ++; }
   }
}
int getst(int x) {
   int res = 0;
   for(int i = 0; i < m; i ++) {
      int y = 0;
      while(x % p[i] == 0) { x /= p[i]; y ++; }
      if(y == cl[i]) res ^= 1 << i;
      if(y == c[i]) res ^= 1 << (m + i);
   }
   return res;
}
void fwt(int *a, int n) {
   for(int i = 1; i < n; i <<= 1)
      for(int j = 0; j < n; j += i << 1)
         for(int k = 0; k < i; k ++)
            a[j + k + i] += a[j + k];
}
int solve(int x) {
   int y = ID(x), z = st[y];
   if(~ ans[z]) return ans[z];
   int S0 = ((1 << (2 * m)) - 1) ^ z;
   ans[z] = pp(z) & 1 ? mod - pw[a[z] - 1] : pw[a[z] - 1];
   for(int S = S0; S; S = (S - 1) & S0) {
       int T = z | S;
      if(pp(T) & 1) (ans[z] += mod - pw[a[T] - 1]) %= mod;
      else (ans[z] += pw[a[T] - 1]) %= mod;
   }
   return ans[z] %= mod;
}
int main() {
   scanf("%d%d%d%d", &n, &g, &l, &q);
   if(l % g) {
      while(q --) puts("0");
      return 0;
   }
   for(int i = 1; i * i <= l; i ++) if(l % i == 0) {
      if(i % g == 0 && i <= n) vec.push_back(i);
      if(i != l / i && (l / i) % g == 0 && (l / i) <= n) rv.push_back(l / i);
   }
   for(int i = (int) rv.size() - 1; i >= 0; i --) vec.push_back(rv[i]);
   work(l);
   for(int i = 0; i < (int) vec.size(); i ++) {
      st[i] = getst(vec[i]); a[st[i]] ++; ans[st[i]] = -1;
   }
   pw[0] = 1;
   for(int i = 1; i <= (int) vec.size(); i ++)
      pw[i] = (pw[i - 1] + pw[i - 1]) % mod;
   fwt(a, 1 << (2 * m));
   while(q --) {
      int x; scanf("%d", &x);
      printf("%d\n", x > n || x % g || l % x ? 0 : solve(x));
   }
   return 0;
}