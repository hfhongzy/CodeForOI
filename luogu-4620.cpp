#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef unsigned long long ull;
typedef unsigned uint;
const int N = 2e7 + 10;
uint SA, SB, SC;
int n, m, k, p, A, B, a[N], b[N];
int L, len;
char lg[N];
uint rng61(){
   SA ^= SA << 16;
   SA ^= SA >> 5;
   SA ^= SA << 1;
   uint t = SA;
   SA = SB; SB = SC; 
   return SC ^= t ^ SA;
}
void gen(){
   scanf("%d%d%d%d%u%u%u%d%d", &n, &k, &m, &p, &SA, &SB, &SC, &A, &B);
   rep(i, 1, p) scanf("%d%d", a + i, b + i);
   rep(i, p + 1, n) {
      a[i] = rng61() % A + 1;
      b[i] = rng61() % B + 1;
   }
}
ull val[2055][205], tr1[2055], tr2[2055][205], dp[2055][205];
int main() {
   for(int i = 1; i < N; i ++) {
      lg[i] = i == 1 ? 0 : lg[i >> 1] + 1;
   }
   int test; scanf("%d", &test);
   while(test --) {
      gen();
      rep(i, 1, n) a[i] %= m;
      for(int i = 0; i < 28; i ++) if((1 << i) - 1 >= n) {
         L = i; len = (1 << L) - 1; break ;
      }
      int sz = (1 << (k + 1)) - 1;
      rep(i, 0, sz) {
         tr1[i] = val[i][0] = 0;
         rep(j, 0, m) tr2[i][j] = 0;
      }
      rep(i, 1, n) {
         int d = (lg[i] + 1 - 1) % (k + 1) + 1;
         int u = i >> (lg[i] + 1 - d);
         // pr(i); printf(" prefix %d = ", d); pr(u); puts("");
         val[u][0] += (m - a[i]) % m * 1ull * b[i];
         tr1[u] += b[i]; tr2[u][a[i]] += 1ull * b[i] * m;
      }
      rep(i, 1, sz) {
         rep(j, 1, m - 1) {
            val[i][j] = val[i][j - 1] + tr1[i] - tr2[i][j];
         }
      }
      per(i, sz, 1) {
         if(2 * i + 1 > sz) {
            rep(j, 0, m - 1)
               dp[i][j] = val[i][j];
         } else {
            rep(j, 0, m - 1) {
               dp[i][j] = 0; dp[i][j] --;
               rep(k, 0, m - 1) {
                  int x = (j - k + m) % m;
                  dp[i][j] = min(dp[i][j], val[i][k] + dp[i << 1][x] + dp[i << 1 | 1][x]);
               }
            }
         }
      }
      printf("%llu\n", dp[1][0]);
   }
   return 0;
}
/*
1
7 1 3 7 11111 22222 33333 1 1
6 9
4 5
3 7
5 2
2 4
1 7
9 6
i != a[i] (i - 1) -> i : b[i]
i = a[i] : - (m - 1) * b[i] = b[i] - m * b[i]
*/