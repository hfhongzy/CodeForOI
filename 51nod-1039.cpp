#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef vector<int> vi;
int qpow(int a, int b, int p) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % p)
      if(b & 1) ans = 1ll * ans * a % p;
   return ans;
}
namespace cipolla {
 
int a, t, p;
struct node {
   int x, y;
   node operator * (node b) {
      return {
         (int) ((1ll * x * b.x + 1ll * y * b.y % p * t) % p),
         (int) ((1ll * x * b.y + 1ll * y * b.x) % p)
      };
   }
};
node Pow(node a, int b) {
   node ans = (node) {1, 0};
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
int solve(int n, int p) {
   if(qpow(n, (p - 1) / 2, p) != 1) return -1;
   cipolla::p = p;
   mt19937 mt(time(0));
   uniform_int_distribution<int> ran(1, p - 1);
   for(a = ran(mt); t = (1ll * a * a + p - n) % p, qpow(t, (p - 1) / 2, p) != p - 1; a = ran(mt));
   return Pow(node {a, 1}, (p + 1) / 2).x;
}
 
}

namespace peralta {

int a, w, p;
struct node {
   int x[3]; //x + yw + zw^2
   node operator * (node b) {
      node ans;
      rep(i, 0, 2) ans.x[i] = 0;
      rep(i, 0, 2) rep(j, 0, 2) {
         if(i + j >= 3) ans.x[i + j - 3] = (ans.x[i + j - 3] + 1ll * x[i] * b.x[j] % p * w) % p;
         else ans.x[i + j] = (ans.x[i + j] + 1ll * x[i] * b.x[j]) % p;
      }
      return ans;
   }
};
node Pow(node a, ll b) {
   node ans = {1, 0, 0};
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
vi solve(int n, int p) {
   vi ans; peralta::p = p;
   if(p <= 3) {
      for(int i = 1; i < p; i ++) if(i * i * i % p == n) ans.pb(i);
      return ans;
   }
   if(p % 3 == 2) {
      ans.pb(qpow(n, (2 * p - 1) / 3, p));
      return ans;
   }
   if(qpow(n, (p - 1) / 3, p) != 1) return vi();
   mt19937 mt(time(0));
   uniform_int_distribution<int> ran(1, p - 1);
   for(a = ran(mt); w = (1ll * a * a % p * a + p - n) % p, qpow(w, (p - 1) / 3, p) == 1; a = ran(mt)) ;
   int e = (cipolla::solve(p - 3, p) + p - 1) * ((p + 1ll) / 2) % p;
   ans.pb(Pow(node {a, p - 1, 0}, ((ll)p * p + p + 1) / 3).x[0]);
   ans.pb(1ll * ans[0] * e % p); ans.pb(1ll * ans[1] * e % p);
   sort(ans.begin(), ans.end());
   return ans;
}

}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      int a, p;
      scanf("%d%d", &p, &a);
      vector<int> ans = peralta::solve(a, p);
      if(!ans.size()) printf("No Solution");
      for(int v : ans) printf("%d ", v);
      putchar('\n');
   }
   return 0;
}