#include <functional>
#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
#define pii pair<int, int>
#define fs first
#define sc second
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int n, q, cnt, ans[N], bit[N];
pii b[N], c[N * 2];
pair<pii, int> qu[N];
void add(int u, int v) {
   for(; u <= n; u += u & (-u)) {
      bit[u] += v;
   }
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1)
      ans += bit[u];
   return ans;
}
int main() {
   scanf("%d%d", &n, &q);
   if(n == 1) { puts("0"); return 0; }
   rep(i, 1, n) scanf("%d", &b[i].fs), b[i].sc = i;
   sort(b + 1, b + n + 1);
   rep(i, 1, n) {
      if(i == 1) c[++ cnt] = pii(b[i].sc, b[i + 1].sc);
      else if(i == n) c[++ cnt] = pii(b[i].sc, b[i - 1].sc);
      else {
         if(b[i].fs - b[i - 1].fs <= b[i + 1].fs - b[i].fs) c[++ cnt] = pii(b[i].sc, b[i - 1].sc);
         if(b[i].fs - b[i - 1].fs >= b[i + 1].fs - b[i].fs) c[++ cnt] = pii(b[i].sc, b[i + 1].sc);
      }
   }
   rep(i, 1, cnt) if(c[i].fs > c[i].sc) swap(c[i].fs, c[i].sc); 
   sort(c + 1, c + cnt + 1, greater<pii>());
   rep(i, 1, q) {
      scanf("%d%d", &qu[i].fs.fs, &qu[i].fs.sc);
      qu[i].sc = i;
   }
   sort(qu + 1, qu + q + 1, greater< pair<pii, int> >());
   int p = 1, p2 = 1;
   per(l, n, 1) {
      for(; p2 <= cnt && c[p2].fs == l; p2 ++) {
         add(c[p2].sc, 1);
      }
      for(; p <= q && qu[p].fs.fs == l; p ++) {
         ans[qu[p].sc] = qry(qu[p].fs.sc);
      }
   }
   ll res = 0;
   rep(i, 1, q) {
      res += (ll) i * ans[i];
   }
   printf("%lld\n", res);
   return 0;
}