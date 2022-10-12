#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
int qpow(int a, int b, int mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int k, p;
ll n;
struct mat {
   int a[2][2];
   void operator += (mat b) {
      rep(i, 0, 1) rep(j, 0, 1) a[i][j] = (a[i][j] + b.a[i][j]) % p;
   }
   mat operator + (mat b) {
      mat ans;
      rep(i, 0, 1) rep(j, 0, 1) ans.a[i][j] = (a[i][j] + b.a[i][j]) % p;
      return ans;
   }
   mat operator * (const mat &b) {
      mat ans;
      rep(i, 0, 1) rep(j, 0, 1) ans.a[i][j] = ((ll)a[i][0] * b.a[0][j] + (ll)a[i][1] * b.a[1][j]) % p;
      return ans;
   }
   mat operator * (int b) {
      mat ans;
      rep(i, 0, 1) rep(j, 0, 1) ans.a[i][j] = (ll)a[i][j] * b % p;
      return ans;
   }
};
mat Pow(mat a, ll b) {
   mat ans = {1, 0, 0, 1};
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
struct ModRoot {
   int g;
   operator int() const { return g; }
   int get(int p) { //p is prime
      vector<int> vec; vec.clear(); int x = p - 1;
      for(int i = 2; i * i <= x; i ++) {
         if(x % i == 0) {
            vec.push_back(i);
            while(x % i == 0) x /= i;
         }
      }
      if(x > 1) vec.push_back(x);
      for(int i = 2; i < p; i ++) {
         bool mark = 1;
         for(int v : vec) {
            if(qpow(i, (p - 1) / v, p) == 1) {
               mark = 0; break ;
            }
         }
         if(mark) return g = i;
      }
      return g = 0;
   }
} g;
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%lld%d%d", &n, &k, &p);
      int w = qpow(g.get(p), (p - 1) / k, p), c = 1;
      // cerr << "w = " << w << endl;
      mat ans = {0, 0, 0, 0}, tr = mat {0, 1, 1, 1};
      for(int t = 0; t < k; t ++) {
         ans += Pow(tr * c + mat {1, 0, 0, 1}, n);
         c = (ll)c * w % p;
      }
      // assert(c == 1);
      ans = mat{1, 1, 0, 0} * ans;
      int res = (ll)ans.a[0][0] * qpow(k, p - 2, p) % p;
      printf("%d\n", res);
   }
   return 0;
}