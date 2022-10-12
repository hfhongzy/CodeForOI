#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 5000 + 10;
const int M = 2e4 + 10;
const int mod = 998244353;

int n, q, p, g, phi_n, a[N], b[N], pw[N], d[M], dn, c[M];
int qpow(int a, int b, int mo = mod) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mo)
    if(b & 1) ans = (ll)ans * a % mo;
  return ans;
}
int getq(int x) {
  for(int i = 2; i * i <= x; i ++)
    if(x % i == 0) return i;
  return x;
}
int phi(int n) {
  int ans = n;
  for(int i = 2; i * i <= n; i ++) {
    if(n % i == 0) {
      ans = ans / i * (i - 1);
      while(n % i == 0) n /= i;
    }
  }
  if(n > 1) ans = ans / n * (n - 1);
  return ans;
}
int fc[N];
void work(int x) {
  *fc = 0;
  for(int i = 2; i * i <= x; i ++) {
    if(x % i == 0) {
      fc[++ *fc] = i;
      while(x % i == 0) x /= i;
    }
  }
  if(x > 1) fc[++ *fc] = x;
}
int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int minG(int n) {
  phi_n = phi(n); work(phi_n);
  for(int g = 2; g < n; g ++) if(qpow(g, phi_n, n) == 1) {
    bool tag = 1;
    for(int i = 1; i <= *fc; i ++) {
      if(qpow(g, phi_n / fc[i], n) == 1) {
        tag = 0; break ;
      }
    }
    if(tag) return g;
  }
  return 0;
}

namespace Map {
  
const int mod = 76543;
const int N = 1e5 + 10;
int cnt, hd[mod], nxt[N], fir[N], sec[N];
void clr() {
  fill(hd, hd + mod, -1); cnt = 0;
}
void ins(int x, int y) {
  int k = x % mod;
  fir[cnt] = x; sec[cnt] = y; nxt[cnt] = hd[k]; hd[k] = cnt ++; 
}
int find(int x) {
  for(int i = hd[x % mod]; ~ i; i = nxt[i])
    if(fir[i] == x) return sec[i];
  return -1;
}

}
void exgcd(int a, int b, int &x, int &y, int &g) {
  if(!b) x = 1, y = 0, g = a;
  else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
int inv(int a, int p) {
  int x, y, g; exgcd(a, p, x, y, g);
  return g == 1 ? (x % p + p) % p : -1;
}
int logM(int a, int b, int p) { //a^x = b (mod p), (a, p) = 1
  Map::clr();
  int m = (int) ceil(sqrt(p + 0.5));
  int aM = qpow(a, m, p), t = 1;
  for(int i = 0; i <= m; i ++) {
    if(-1 == Map::find(t)) Map::ins(t, i);
    t = (ll)t * aM % p;
  }
  int q = b, inv_a = inv(a, p), ans = -1;
  for(int i = 0; i < m; i ++) {
    if(~ (t = Map::find(q))) {
      int r = t * m + i;
      if(ans == -1 || ans > r) ans = r;
    }
    q = (ll)q * inv_a % p;
  }
  return ans;
}

int dfn[N], low[N], idx, bel[N], sz[N], scc;
vector<int> G[N], vec;
stack<int> st;
bool ins[N];
void tarjan(int u) {
  dfn[u] = low[u] = ++ idx; st.push(u); ins[u] = 1;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if(ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(low[u] == dfn[u]) {
    int v = 0; scc ++;
    do {
      v = st.top(); st.pop(); ins[v] = 0;
      bel[v] = scc; sz[scc] ++;
    } while(v != u);
  }
}
bool edge[N][N];
int solve(int lgn) {
  int c = int(vec.size());
  for(int i = 0; i < c; i ++) {
    int x = vec[i], z = 1;
    vector<int> out;
    out.pb(INT_MAX);
    rep(j, 1, lgn) {
      z = (ll)z * x % p;
      if(!z) break ;
      out.pb(z);
    }
    sort(out.begin(), out.end());
    for(int j = 0; j < c; j ++) if(i != j) {
      if(*lower_bound(out.begin(), out.end(), vec[j]) == vec[j]) {
        G[i + 1].pb(j + 1);
      }
    }
  }
  rep(i, 1, c) if(!dfn[i]) tarjan(i);
  rep(i, 1, c) for(int j : G[i]) edge[bel[i]][bel[j]] = 1;
  int ans = 0;
  rep(i, 1, scc) {
    int s = sz[i];
    rep(j, 1, scc) if(j != i && edge[j][i]) s += sz[j];
    ans = (ans + (pw[sz[i]] + mod - 1ll) * pw[n - s]) % mod;
  }
  return ans;
}
int main() {
  scanf("%d%d", &n, &p); q = getq(p); g = minG(p);
  int lgn = 1, x = q;
  while(x != p) x *= q, lgn ++;
  for(int i = 1; i * i <= phi_n; i ++) {
    if(phi_n % i == 0) {
      d[++ dn] = i;
      if(i * i != phi_n) d[++ dn] = phi_n / i;
    }
  }
  sort(d + 1, d + dn + 1);
  pw[0] = 1;
  rep(i, 1, n) pw[i] = (pw[i - 1] + pw[i - 1]) % mod;
  rep(i, 1, n) {
    scanf("%d", a + i);
    if(a[i] % q == 0) {
      // printf("%d!\n", a[i]);
      vec.pb(a[i]); continue ;
    }
    b[i] = logM(g, a[i], p);
    // printf("g = %d, b[%d] = %d\n", g, i, b[i]);
    // assert(a[i] == qpow(g, b[i], p));
    b[i] = gcd(b[i], phi_n);
    b[i] = lower_bound(d + 1, d + dn + 1, b[i]) - d;
    c[b[i]] ++;
  }
  static int pos[N];
  int top = 0, ans = 0;
  rep(i, 1, dn) if(c[i]) {
    int cnt = c[i];
    rep(j, 1, top)
      if(d[i] % d[pos[j]] == 0) cnt += c[pos[j]];
    ans = (ans + (pw[c[i]] + mod - 1ll) * pw[n - cnt]) % mod;
    pos[++ top] = i;
  }
  if(lgn > 1) ans = (ans + solve(lgn)) % mod;
  printf("%d\n", ans);
  return 0;
}