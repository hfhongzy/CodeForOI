#include <bits/stdc++.h>
// #include <bits/extc++.h>
//// __gnu_pbds::gp_hash_table<int, int> cnt;
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
using uint = unsigned;

namespace PR {

mt19937 mt(time(0));
uniform_int_distribution<int> ran(0, 1 << 30);
int rnd() { return ran(mt); }
int qpow(int a, int b, int mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
      if(b & 1) ans = (ll)ans * a % mod;
   return ans;
}

const int base[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, S = 10;
bool check(int a, int x, int t, int n) {
   int tmp = qpow(a, x, n), last;
   while(t --) {
      last = (ll)tmp * tmp % n;
      if(last == 1 && tmp != 1 && tmp != n - 1) return false;
      tmp = last;
   }
   return tmp == 1;
}
bool MR(int n) {
   for(int i = 0; i < S; i ++)
      if(n % base[i] == 0) return n == base[i];
   int t = 0, m = n - 1;
   while(!(m & 1)) m >>= 1, t ++;
   for(int i = 0; i < S; i ++)
      if(!check(base[i], m, t, n)) return false;
   return true;
}

int gcd(int a, int b) {
   return !b ? a : gcd(b, a % b);
}
int PR(int n) {
   const int c = rnd() & 1023;
   auto f = [&](int x) { return int(((ll)x * x + c) % n); };
   int a = rnd() % n, b = f(a), tmp;
   while(1) {
      int prod = 1, s = a, t = b;
      for(int i = 0; i < 64; i ++) {
         prod = (ll)prod * abs(s - t) % n;
         s = f(s); t = f(f(t));
      }
      int d = gcd(n, prod);
      if(d == 1) { a = s; b = t; continue ; }
      for(int i = 0; i < 64; i ++) {
         d = gcd(n, abs(a - b));
         if(d > 1) return d;
         a = f(a); b = f(f(b));
      }
   }
   return n;
}
int calc(int n) {
   if(MR(n)) return n;
   int d = 0;
   while(n == (d = PR(n))) ;
   return d;
}

}
using PR::calc;
struct discrete {
   vector<int> v;
   vector<int>::iterator ep;
   void push(int x) { v.pb(x); }
   int size() { return ep - v.begin(); }
   void build() { sort(v.begin(), v.end()); ep = unique(v.begin(), v.end()); }
   int get(int x) { return lower_bound(v.begin(), ep, x) - v.begin() + 1; }
} ds;
const int mod = 19260817, N = 1e5 + 10, M = 1024;
int n, m, v, p[M], pc, a[N], b[N], c[N], inv[N * 2];
bool tag[M];
void sieve(int n) {
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) p[++ pc] = i;
      for(int j = 1; j <= pc && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
int blo, ans[N], cnt[N * 2], cur = 1;
struct node {
   int l, r, l2, id;
   bool operator < (const node &b) const {
      return l2 == b.l2 ? ((l2 & 1) ? r < b.r : r > b.r) : l2 < b.l2;
   }
} q[N];
void insert(int x, int v) {
   if(!x) return ;
   int c = cnt[x];
   cur = (ll)cur * inv[c + 1] % mod;
   cnt[x] = (c += v);
   cur = (ll)cur * (c + 1) % mod;
}
void ins(int x) { insert(b[x], 1); insert(c[x], 1); }
void del(int x) { insert(b[x], -1); insert(c[x], -1); }
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", a + i);
   sieve(v = (int)ceil(pow(*max_element(a + 1, a + n + 1), 1.0 / 3)));
   //sieve(v = 1000);
   inv[1] = 1;
   rep(i, 2, 2 * n + 1) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
   rep(i, 1, n) b[i] = a[i], c[i] = 1;
   vector<vector<int>> s;
   s.resize(pc + 1);
   rep(i, 1, pc) {
      s[i].resize(n + 1);
      rep(j, 1, n) {
         int z = 0;
         while(b[j] % p[i] == 0) b[j] /= p[i], z ++;
         s[i][j] = s[i][j - 1] + z;
      }
   }
   rep(i, 1, n) if(b[i] > 1) {
      int d = calc(b[i]);
      if(d < b[i]) { b[i] /= d; c[i] = d; }
      if(b[i] > 1) ds.push(b[i]);
      if(c[i] > 1) ds.push(c[i]);
   }
   ds.build();
   rep(i, 1, n) {
      if(b[i] > 1) b[i] = ds.get(b[i]); else b[i] = 0;
      if(c[i] > 1) c[i] = ds.get(c[i]); else c[i] = 0;
   }
   blo = max(1, int(n / sqrt(m)));
   rep(i, 1, m) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i, q[i].l2 = q[i].l / blo;
   sort(q + 1, q + m + 1);
   int ql = q[1].l, qr = ql - 1;
   rep(i, 1, m) {
      while(qr < q[i].r) ins(++ qr);
      while(ql > q[i].l) ins(-- ql);
      while(qr > q[i].r) del(qr --);
      while(ql < q[i].l) del(ql ++);
      int res = cur;
      rep(j, 1, pc) res = res * (1ll + s[j][qr] - s[j][ql - 1]) % mod;
      ans[q[i].id] = res;
   }
   rep(i, 1, m) printf("%d\n", ans[i]);
   return 0;
}
