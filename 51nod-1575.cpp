#include <algorithm>
#include <cstdio>
using namespace std;

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;

const int N = 1e5 + 5;

int n, m, c, p[N], pos[N * 2], len, idx1[N], idx2[N];
uint sp[N], sp2[N], g0[N * 2], g1[N * 2], g2[N * 2];
bool tag[N];
void sieve(int n) {
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) {
         p[++ c] = i;
         sp[c] = sp[c - 1] + i;
         sp2[c] = sp2[c - 1] + i * i;
      }
      for(int j = 1; i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
uint S1(uint n) {
   return 1ull * n * (n + 1) / 2;
}
uint S2(uint n) {
   ull a = n, b = n + 1ull, c = 2ull * n + 1;
   if(!(a & 1)) a >>= 1; else b >>= 1;
   if(a % 3 == 0) a /= 3; else if(b % 3 == 0) b /= 3; else c /= 3;
   return a * b * c;
}
uint S(int n, int j) {
   if(n <= p[j]) return 0;
   int z = n <= m ? idx1[n] : idx2[::n / n];
   uint res = 3 * (g2[z] - g1[z]) + g0[z] - ( 3 * (sp2[j] - sp[j]) + j );
   for(int k = j + 1; k <= c && p[k] * p[k] <= n; k ++) {
      uint e = 1, la_p = 1, la_p2 = 1;
      for(ll x = p[k]; x <= n; x *= p[k], e ++) {
         uint cur_p = x, cur_p2 = cur_p * cur_p;
         uint f = (2 * e + 1) * (cur_p2 - la_p2 * p[k]) + la_p;
         res += f * (S(n / x, k) + (e > 1));
         la_p = cur_p; la_p2 = cur_p2;
      }
   }
   return res;
}
void mian() {
   scanf("%d", &n);
   for(m = 1; m * m <= n; m ++) ;
   len = 0;
   for(int l = 1, r; l <= n; l = r + 1) {
      int t = n / l; r = n / t;
      pos[++ len] = t;
      g0[len] = t - 1;
      g1[len] = S1(t) - 1;
      g2[len] = S2(t) - 1;
      if(t <= m) idx1[t] = len;
      else idx2[r] = len;
   }
   pos[len + 1] = 0;
   for(int i = 1; i <= c; i ++) {
      for(int j = 1, up = p[i] * p[i]; pos[j] >= up; j ++) {
         int t = pos[j] / p[i];
         int z = t <= m ? idx1[t] : idx2[n / t];
         g0[j] -= g0[z] - (i - 1);
         g1[j] -= (g1[z] - sp[i - 1]) * p[i];
         g2[j] -= (g2[z] - sp2[i - 1]) * p[i] * p[i];
      }
   }
   printf("%u\n", 1 + S(n, 0));
}
int main() {
   sieve(32000);
   int test; scanf("%d", &test);
   while(test --) mian();
   return 0;
}