#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back

typedef double db;
typedef long long ll;
typedef long double ldb;
typedef unsigned uint;
typedef unsigned long long ull;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

template<class T> inline void chkmax(T &x, const T &y) { if(x < y) x = y; }
template<class T> inline void chkmin(T &x, const T &y) { if(x > y) x = y; }

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int x, y, z, a[10];
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d%d", a + 1, a + 2, a + 3);
      int l1 = min(1000 / a[2] + 1, 1000 / a[1] + 1);
      int l2 = min(1000 / a[1] + 1, 1000 / a[3] + 1);
      int ans = 23333333;
      rep(i, 0, l1) {//x[1][2]
         rep(j, 0, l2) {//x[1][3]
            int r1 = 1000 - i * a[2] - j * a[3];
            int r2 = 1000 - i * a[1];
            int r3 = 1000 - j * a[1];
            if(r1 > 0) {
               if(r2 <= 0 && r3 <= 0) ans = min(ans, i + j);
               else if(r2 > 0 && r3 > 0) {
                  int x = (r2 + a[3] - 1) / a[3];
                  int y = (r3 + a[2] - 1) / a[2];
                  if(x == y) ans = min(ans, i + j + x);
               }
            } else {
               if(r2 <= 0 || r3 <= 0) ans = min(ans, i + j);
               else {
                  int x = (r2 + a[3] - 1) / a[3];
                  int y = (r3 + a[2] - 1) / a[2];
                  ans = min(ans, i + j + min(x, y));
               }
            }
         }
      }
      printf("%d\n", ans);
   }
   return 0;
}