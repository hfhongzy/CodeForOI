#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
ll n;
vector<ll> p;
mt19937 mt(time(0));

const int S = 10, base[S] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
ll mul(ll x, ll y, ll p) {
  ll t = floor(x * (long double)y / p);
  ll r = (x * y - t * p) % p;
  return r < 0 ? r + p : r;
}
ll qpow(ll a, ll b, ll p) {
  ll ans = 1;
  for(; b >= 1; b >>= 1, a = mul(a, a, p))
    if(b & 1) ans = mul(ans, a, p);
  return ans;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
bool check(ll n, ll a, ll t, int k) {
  a = qpow(a, t, n);
  ll z = a;
  for(int i = 0; i < k; i ++) {
    a = mul(a, a, n);
    if(a == 1 && 1 != z && z != n - 1) return 0;
    z = a;
  }
  return a == 1;
}
bool MR(ll n) {
  for(int i = 0; i < S; i ++) if(n % base[i] == 0) return n == base[i];
  ll t = n - 1; int k = 0;
  for(; !(t & 1); t >>= 1) k ++;
  for(int i = 0; i < S; i ++) if(!check(n, base[i], t, k)) return 0;
  return 1;
}
#define f(x) ((mul(x, x, n) + c) % n)
ll PR(ll n) {
  ll c = mt() & 1023;
  uniform_int_distribution<ll> ran(0, n - 1);
  ll a = ran(mt), b = f(a);
  while(1) {
    ll pd = 1, s = a, t = b;
    for(int i = 0; i < 128; i ++) {
      pd = mul(pd, abs(s - t), n);
      s = f(s); t = f(f(t));
    }
    ll d = gcd(pd, n);
    if(d == 1) { a = s; b = t; continue; }
    for(int i = 0; i < 128; i ++) {
      d = gcd(abs(a - b), n);
      if(d > 1) return d;
      a = f(a); b = f(f(b));
    }
  }
  return n;
}
void calc(ll n) {
  if(n == 1) return ;
  if(MR(n)) { p.pb(n); return ; }
  ll d = 0;
  while((d = PR(n)) == n) ;
  calc(d); calc(n / d);
}
int main() {
  scanf("%lld", &n);
  calc(n);
  sort(p.begin(), p.end());
  p.resize(unique(p.begin(), p.end()) - p.begin());
  ll ans = n;
  for(ll v : p) ans = ans / v * (v - 1);
  printf("%lld\n", ans);
  return 0;
}