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

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 Rand(seed);
// mt19937_64 
uniform_int_distribution<ll> range(0, 1ll << 32);
inline void ucin() {
   ios::sync_with_stdio(0); cin.tie(0);
}
// uniform_real_distribution<double> dbran;
template<class T> inline void chkmax(T &x, const T &y) { if(x < y) x = y; }
template<class T> inline void chkmin(T &x, const T &y) { if(x > y) x = y; }

const int N = 2e5 + 10;
const int INF = 2e9 + 10;

int qpow(int a, int b, int mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int w[32], n, cnt[32], fx[32];
char s[N];
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      rep(i, 1, 26) scanf("%d", w + i);
      scanf("%s", s + 1);
      n = strlen(s + 1);
      bool mark = 0;
      int pl = n + 1, pr = 0;
      rep(i, 1, n) if(w[ s[i] - 'a' + 1 ] == 4) {
         pl = min(pl, i); pr = max(pr, i);
      }
      rep(i, 2, n - 1) if(w[ s[i] - 'a' + 1 ] >= 4 && pl >= i && pr <= i) {
         if((w[ s[i - 1] - 'a' + 1 ] & 2) && (w[ s[n] - 'a' + 1 ] & 2)) {
            puts("Yes"); mark = 1; break ;
         }
      }
      if(!mark) {
         puts("No");
      }
   }
   return 0;
}
