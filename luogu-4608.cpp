#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef long long ll;
const int N = 3015, S = 52;
inline int dir(char c) {
   return c >= 'A' && c <= 'Z' ? c - 'A' : c - 'a' + 26;
}
inline char rid(int x) {
   return x < 26 ? x + 'A' : x - 26 + 'a';
}
const ll base = 1e18;
struct LL {
   ll a[20]; int n;
   LL() { n = 1; }
   void clr() { fill(a, a + 20, 0); }
   void operator = (ll x) { clr(); a[0] = x; n = 1; }
   LL operator + (LL x) {
      LL ans; ans.n = 1 + max(n, x.n); ans.clr();
      rep(i, 0, ans.n - 2) {
         ans.a[i] += a[i] + x.a[i];
         ans.a[i + 1] += ans.a[i] / base;
         ans.a[i] %= base;
      }
      while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
      return ans;
   }
   void operator += (LL x) { *this = *this + x; }
   void print() {
      printf("%lld", a[n - 1]);
      per(i, n - 2, 0) printf("%018lld", a[i]);
   }
} f[N], g[N];
struct SeqAM {
   int nxt[N][S];
   void build(char *s, int n) {
      fill(nxt[n], nxt[n] + S, -1);
      per(i, n - 1, 0) {
         copy(nxt[i + 1], nxt[i + 1] + S, nxt[i]);
         nxt[i][dir(s[i + 1])] = i + 1;
      }
   }
} a, b;
int n, m, ty;
char s[N], t[N], out[N];
void dfs(int u, int v, int len = 0) {
   rep(i, 1, len) putchar(out[i]);
   putchar('\n');
   rep(i, 0, S - 1) if(~ a.nxt[u][i] && ~ b.nxt[v][i]) {
      out[len + 1] = rid(i);
      dfs(a.nxt[u][i], b.nxt[v][i], len + 1);
   }
}
int main() {
   // freopen("qoq.in", "r", stdin);
   scanf("%d%d%s%s%d", &n, &m, s + 1, t + 1, &ty);
   a.build(s, n); b.build(t, m);
   if(ty) {
      dfs(0, 0);
   }
   per(i, n, 0) {
      per(j, m, 0) g[j] = f[j];
      per(j, m, 0) if(s[i] == t[j]) {
         f[j] = 1;
         rep(c, 0, S - 1) if(~ b.nxt[j][c]) {
            f[j] += g[b.nxt[j][c]];
         }
      }
   }
   f[0].print(); putchar('\n');
   return 0;
}