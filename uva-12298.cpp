#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef long double db;
typedef vector<ll> poly;

const int N = 524288 | 10;
const ll mod = 39582418599937ll, g = 5;

ll mul(ll a, ll b) {
   ll res = a * b - (ll)((db) a / mod * b + 1e-8) * mod;
   return res < 0 ? res + mod : res;
}
ll add(ll x, ll y) { return (x += y) >= mod ? x - mod : x; }
void ADD(ll &x, ll y) { (x += y) >= mod ? x -= mod : 0; }
ll qpow(ll a, ll b) {
   ll ans = 1;
   for(; b >= 1; b >>= 1, a = mul(a, a))
      if(b & 1) ans = mul(ans, a);
   return ans;
}

int rev[N];
ll W[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; }
void prework(int n) {
   for(int i = 1; i < n; i <<= 1) {
      W[i] = 1;
      ll w = qpow(g, (mod - 1) / (i << 1));
      for(int j = 1; j < i; j ++)
         W[i + j] = mul(W[i + j - 1], w);
   }
}
void NTT(poly &a, int n, int op) {
   a.resize(n);
   for(int i = 1; i < n; i ++)
      if(i < (rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0)))
         swap(a[i], a[rev[i]]);
   for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            ll q = mul(W[i + k], a[j + k + i]);
            a[j + k + i] = add(a[j + k], mod - q); ADD(a[j + k], q);
         }
      }
   }
   if(op == 1) return ;
   reverse(a.begin() + 1, a.end());
   ll inv = mod - (mod - 1) / n;
   rep(i, 0, n - 1) a[i] = mul(a[i], inv);
}
bool tag[N];
int p[N], pc;
void sieve(int n) {
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) p[++ pc] = i;
      for(int j = 1; j <= pc && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
int main() {
   prework(2e5);
   sieve(5e4);
   int a, b, c; char op[32];
   static int mp[256]; mp['S'] = 0; mp['H'] = 1; mp['C'] = 2; mp['D'] = 3;
   while(scanf("%d%d%d", &a, &b, &c), a || b || c) {
      poly f[4];
      rep(i, 0, 3) {
         f[i].resize(b + 1);
         rep(j, 2, b) if(tag[j]) f[i][j] = 1;
      }
      while(c --) {
         char z; int x;
         scanf("%d%c", &x, &z); z = mp[z];
         if(x <= b) f[z][x] = 0;
      }
      int n = getn(4 * (b + 1));
      rep(i, 0, 3) NTT(f[i], n, 1);
      rep(i, 0, n - 1) f[0][i] = mul(f[0][i], mul(f[1][i], mul(f[2][i], f[3][i])));
      NTT(f[0], n, -1);
      rep(i, a, b) printf("%lld\n", f[0][i]);
      puts("");
   }
   return 0;
}