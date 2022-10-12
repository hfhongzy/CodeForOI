#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1 << 6;
const int mod = 998244853;

int p[N], c;
void sieve(int n) {
   static bool tag[1 << 8];
   rep(i, 2, n) {
      if(!tag[i]) p[++ c] = i;
      rep(j, 1, c) {
         if(i * p[j] > n) break ;
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
struct node {
   int h[2], id;
   bool operator == (const node &b) const {
      return *h == *b.h && h[1] == b.h[1];
   }
   bool operator < (const node &b) const {
      if(*h ^ *b.h) return *h < *b.h;
      if(h[1] ^ b.h[1]) return h[1] < b.h[1];
      return id < b.id;
   }
} a[N];
int m, n, fm, sz[N], f[N], ans[N];
vector<int> G[N];
void findrt(int u, int fa = 0) {
   f[u] = 0; sz[u] = 1;
   for(int v : G[u]) if(v ^ fa) {
      findrt(v, u);
      sz[u] += sz[v];
      f[u] = max(f[u], sz[v]);
   }
   f[u] = max(f[u], n - sz[u]);
   fm = min(fm, f[u]);
}
int calc(int u, int fa = 0) {
   int h = 1; sz[u] = 1;
   for(int v : G[u]) if(v ^ fa) {
      h = (h + (ll) calc(v, u) * p[sz[v]]) % mod;
      sz[u] += sz[v];
   }
   return h;
}
int main() {
   sieve(233);
   scanf("%d", &m);
   rep(i, 1, m) {
      a[i].id = i;
      scanf("%d", &n);
      rep(j, 0, n) G[j].clear();
      rep(j, 1, n) {
         int f; scanf("%d", &f);
         G[f].pb(j);
         if(f) G[j].pb(f);
      }
      fm = n; findrt(G[0][0]);
      int c = 0;
      rep(j, 1, n) if(fm == f[j]) {
         a[i].h[c ++] = calc(j);
         if(c == 2) break ;
      }
      if(c == 1) a[i].h[1] = a[i].h[0];
      else if(a[i].h[1] < a[i].h[0]) swap(a[i].h[0], a[i].h[1]);
   }
   sort(a + 1, a + m + 1);
   for(int i = 1, j; i <= m; i = j + 1) {
      j = i; ans[a[i].id] = a[i].id;
      while(j < m && a[j + 1] == a[i]) {
         ans[a[++ j].id] = a[i].id;
      }
   }
   rep(i, 1, m) printf("%d\n", ans[i]);
   return 0;
}