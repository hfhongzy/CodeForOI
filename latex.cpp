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
const int mod = 1e9 + 7;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
const int arr[5][3] = {
   {-17, -68, -97}, //?
   {-17, -68, -127}, //!
   {-17, -68, -102}, //:
   {-29, -128, -126}, //.
   {-17, -68, -101}, //;
};
int main() {
   freopen("latex.in", "r", stdin);
   freopen("latex.out", "w", stdout);
   vector<char> vec;
   char c;
   while((c = getchar()) != EOF) vec.pb(c);
   for(int i = 0; i < (int)vec.size(); i ++) {
      c = vec[i];
      if(c < 0) {
         bool mark = 0;
         if(i + 2 < (int)vec.size()) {
            for(int j = 0; j < 5; j ++)
               if(arr[j][0] == c && arr[j][1] == vec[i + 1] && arr[j][2] == vec[i + 2])
                  mark = 1, j = 5;
         }
         if(!mark && i && vec[i - 1] == '$') {
            putchar(' ');
         }
         putchar(c); putchar(vec[i + 1]); putchar(vec[i + 2]);
         i += 2;
      } else {
         if(c == '$' && i && vec[i - 1] < 0) {
            bool mark = 0;
            for(int j = 0; j < 5; j ++)
               if(arr[j][0] == vec[i - 3] && arr[j][1] == vec[i - 2] && arr[j][2] == vec[i - 1])
                  mark = 1, j = 5;
            if(!mark) {
               putchar(' ');
            }
         }
         putchar(c);
      }
   }
   return 0;
}
/*

*/