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

const int N = 6e5 + 10;
const int INF = 2e9 + 10;

int qpow(int a, int b, int mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int n, k, a[N];
ll ans = 2e18;
bool check(int mid) {
   rep(i, 1, mid) {
      
   }
}
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, n) {
      scanf("%d", a + i);
   }
   int l = 0, r = *max_element(a + 1, a + n + 1);
   while(l <= r) {
      int mid = (l + r) >> 1;
      if(check(mid)) r = mid - 1;
      else l = mid + 1;
   }
   return 0;
}
