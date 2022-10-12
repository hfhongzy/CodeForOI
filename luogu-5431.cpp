#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
char gc() {
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
int n, p, k, pd[N], ipd[N], a[N];
int qpow(int a, int b) {
   const int mod = p;
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int main() {
   read(n); read(p); read(k);
   const int mod = p;
   pd[0] = 1;
   rep(i, 1, n) read(a[i]), pd[i] = (ll) pd[i - 1] * a[i] % mod;
   ipd[n] = qpow(pd[n], mod - 2);
   per(i, n, 1) ipd[i - 1] = (ll) ipd[i] * a[i] % mod;
   int t = 1, ans = 0;
   rep(i, 1, n) {
      t = (ll) t * k % mod;
      ans = (ans + (ll) t * pd[i - 1] % mod * ipd[i]) % mod;
   }
   printf("%d\n", ans);
   return 0;
}