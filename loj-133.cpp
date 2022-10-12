#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
struct Base {
   ll base[64];
   void insert(ll x) {
      per(i, 50, 0) if(x >> i & 1) {
         if(!base[i]) { base[i] = x; return; }
         x ^= base[i];
      }
   }
   ll maxv() {
      ll ans = 0;
      per(i, 50, 0) if(!(ans >> i & 1)) ans ^= base[i];
      return ans;
   }
} b;
int n;
int main() {
   scanf("%d", &n);
   ll x;
   rep(i, 1, n) {
      scanf("%lld", &x);
      b.insert(x);
   }
   printf("%lld\n", b.maxv());
   return 0;
}