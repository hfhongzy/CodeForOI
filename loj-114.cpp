#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
struct Base {
   ll base[64];
   vector<int> pos;
   int n, sz;
   void insert(ll x) {
      n ++;
      per(i, 50, 0) if(x >> i & 1) {
         if(!base[i]) { base[i] = x; sz ++; return; }
         x ^= base[i];
      }
   }
   void build() {
      rep(i, 0, 50) if(base[i]) pos.push_back(i);
   }
   ll kth(ll k) {
      if(sz < n) {
         k --;
      }
      if(k > (1ll << sz)) return -1;
      ll ans = 0;
      per(i, sz - 1, 0) if((k >> i & 1) ^ (ans >> pos[i] & 1)) {
         ans ^= base[pos[i]];
      }
      return ans;
   }
} b;
int n, q;
int main() {
   scanf("%d", &n);
   ll x;
   rep(i, 1, n) {
      scanf("%lld", &x);
      b.insert(x);
   }
   b.build();
   scanf("%d", &q);
   rep(i, 1, q) {
      scanf("%lld", &x);
      printf("%lld\n", b.kth(x));
   }
   return 0;
}