#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int M = 194256;
const ll mod = 2002100820040527;
inline ll add(ll a, ll b) {
   return a + b >= mod ? a + b - mod : a + b;
}
inline ll dec(ll a, ll b) {
   return a - b < 0 ? a - b + mod : a - b;
}
inline ll mul(ll a, ll b) {
   if(a <= 1000000000LL && b <= 1000000000LL) return a * b % mod;
   ll c = a * b - (ll) ((long double) a * b / mod + 0.5) * mod;
   return c < 0 ? c + mod : c;
}
ll qpow(ll a, int b) {
   ll ans = 1;
   for(; b; b >>= 1, a = mul(a, a))
      if(b & 1) ans = mul(ans, a);
   return ans;
}
struct HashTable {
   int hd[M], sec[N], nxt[N], ec;
   ll fir[N];
   void insert(ll x, int y) {
      int z = x % M;
      for(int i = hd[z]; i; i = nxt[i]) {
         if(fir[i] == x) { sec[i] = y; return ; }
      }
      ec ++; fir[ec] = x; sec[ec] = y; nxt[ec] = hd[z]; hd[z] = ec;
   }
   int find(ll x) {
      int z = x % M;
      for(int i = hd[z]; i; i = nxt[i])
         if(fir[i] == x) return sec[i];
      return -1;
   }
   void clear() {
      for(int i = ec; i >= 1; i --) {
         hd[fir[i] % M] = nxt[i];
      }
      ec = 0;
   }
} H;
int n, a[N], lg[N];
ll ans, pw[N];
void solve(int l, int r) {
   if(l == r) { ans ++; return ; }
   int t = lg[r - l + 1], mid = (l + r) >> 1;
   solve(l, mid); solve(mid + 1, r);
   ll s2 = 0;
   for(int i = mid; i >= l; i --) {
      s2 = add(s2, pw[i]); H.insert(s2, i);
   }

   int mx = 0, st = mid + 1;
   ll sum = 0, mxp = 0;
   for(int i = mid + 1; i <= r; i ++) {
      if(a[i] >= mx) { mx = a[i]; mxp = pw[i]; }
      sum = add(sum, pw[i]);
      while(st > l && a[st - 1] < mx) st --;
      if(st <= mid) {
         ll res = mxp;
         for(int x = 0; x <= t; x ++, res = add(res, res)) {
            int z = H.find(dec(res, sum));
            if(z >= st) {
               ans ++;
            }
         }
      }
   }

   H.clear();

   ll s1 = 0;
   for(int i = mid + 1; i <= r; i ++) {
      s1 = add(s1, pw[i]); H.insert(s1, i);
   }

   st = mid; mx = sum = mxp = 0;
   for(int i = mid; i >= l; i --) {
      if(a[i] >= mx) { mx = a[i]; mxp = pw[i]; }
      sum = add(sum, pw[i]);
      while(st < r && a[st + 1] <= mx) st ++;
      if(st > mid) {
         ll res = mxp;
         for(int x = 0; x <= t; x ++, res = add(res, res)) {
            int z = H.find(dec(res, sum));
            if(~ z && z <= st) {
               ans ++;
            }
         }
      }
   }
   
   H.clear();
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i), pw[i] = qpow(2, a[i]);
   rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
   solve(1, n);
   printf("%lld\n", ans);
   return 0;
}