#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define debug(x) fprintf(stderr, "%s = %d\n", #x, x);
using namespace std;
char gc() {
   return getchar();
   static char buf[1 << 20], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 20, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}

typedef double db;
typedef unsigned uint;
typedef long long ll;
typedef pair<ll, ll> pll;

const int N = 12010;
const int M = 1e6 + 10;
const int S = 12010;
const db eps = 1e-9;

struct node { ll x, y; int w; } a[N];
struct qnode { ll k, b; int id; } qn[M];
int n, q, ans[M], L[S], R[S];
struct inversion {
   int u, v; db k;
   bool operator < (inversion b) const {
      if(fabs(k - b.k) > eps) return k < b.k;
      return mp(a[u].x, a[v].x) < mp(a[b.u].x, a[b.v].x);
   }
};
vector<inversion> inv;
bool low(ll k, ll b, ll x, ll y) { return y <= k * x + b; }
int seq[N], pos[N], s;
struct BIT {

int bit[N], n;
void init(int _n) {
   n = _n; fill(bit + 1, bit + n + 1, 0);
}
void add(int u, int v) {
   for(; u <= n; u += u & (-u)) bit[u] += v;
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) ans += bit[u];
   return ans;
}

} bit;
void build(int u) {
   int l = L[u], r = R[u];
   inv.clear();
   rep(i, l, r) seq[i - l + 1] = i;
   s = r - l + 1;
   sort(seq + 1, seq + s + 1, [&](int u, int v) {
      return a[u].x < a[v].x || (a[u].x == a[v].x && a[u].y < a[v].y);
   });
   rep(i, 1, s) pos[seq[i]] = i;
   rep(i, l, r) rep(j, i + 1, r) {
      if(a[i].x != a[j].x) {
         db k = 1.0 * (a[i].y - a[j].y) / (a[i].x - a[j].x);
         if(a[i].x < a[j].x) inv.pb({i, j, k});
         else inv.pb({j, i, k});
      }
   }
   sort(inv.begin(), inv.end());
   uint p = 0;
   bit.init(s);
   rep(i, 1, n) bit.add(i, a[seq[i]].w);
   rep(i, 1, q) {
      while(p < inv.size() && inv[p].k <= qn[i].k) {
         int u = inv[p].u, v = inv[p].v, w = a[u].w - a[v].w;
         swap(pos[u], pos[v]);
         swap(seq[pos[u]], seq[pos[v]]);
         bit.add(pos[u], w);
         bit.add(pos[v], -w);
         p ++;
      }
      int lb = 1, rb = s, res = 0;
      while(lb <= rb) {
         int mid = (lb + rb) / 2;
         int u = seq[mid];
         if(low(qn[i].k, qn[i].b, a[u].x, a[u].y)) {
            lb = (res = mid) + 1;
         } else {
            rb = mid - 1;
         }
      }
      ans[qn[i].id] += bit.qry(res);
   }
}
int main() {
   read(n); read(q);
   int x, y; //z & r
   rep(i, 1, n) { read(x); read(y); a[i] = {y, (ll) x * x + (ll) y * y}; }
   rep(i, 1, q) { read(x); read(y); qn[i] = {2ll * x, (ll) y * y - (ll) x * x, i}; }
   sort(qn + 1, qn + q + 1, [&](qnode a, qnode b) { return a.k < b.k; });
   sort(a + 1, a + n + 1, [&](node a, node b) {
      return a.x < b.x || (a.x == b.x && a.y < b.y);
   });
   int t = n; n = 0;
   rep(i, 1, t) {
      if(i == 1 || !(a[i].x == a[n].x && a[i].y == a[n].y)) {
         a[++ n] = a[i]; a[n].w = 1;
      } else {
         a[n].w ++;
      }
   }
   int sz = max(1, (int)sqrt(q));
   // debug(sz); sz = 1;
   rep(i, 1, n) {
      x = (i + sz - 1) / sz;
      if(!L[x]) L[x] = i;
      R[x] = i;
   }
   rep(i, 1, x) build(i);
   rep(i, 1, q) printf("%d\n", ans[i]);
   return 0;
}