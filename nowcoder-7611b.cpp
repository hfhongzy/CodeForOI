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
struct node {
   int cnt, v, l, r;
   void lnk(int x) { l == 0 ? l = x : r = x; }
   void cut(int x) { l == x ? l = 0 : r = 0; }
   int nxt(int la) { return l ^ r ^ la; }
   // void chg(int x, int y) { l == x ? l = y : }
} a[N];
int n, q, id, L[N], R[N];
int main() {
   scanf("%d%d", &n, &q);
   char op[20]; int x, y, z;
   rep(Q, 1, q) {
      scanf("%s", op);
      if(op[2] == 's') {
         scanf("%d%d%d", &x, &y, &z);
         a[++ id] = {x, y, 0, 0};
         if(!L[z]) {
            L[z] = R[z] = id;
         } else {
            a[id].l = R[z];
            a[R[z]].lnk(id);
            R[z] = id;
         }
      } else if(op[2] == 'p') {
         scanf("%d%d", &x, &z);
         for(int u = R[z], la = 0; u; ) {
            int v = a[u].nxt(la);
            if(x - a[u].cnt <= 0) {
               printf("%d\n", a[u].v);
               if(x - a[u].cnt < 0) {
                  a[u].cnt -= x;
                  a[u].cut(la);
                  R[z] = u;
               } else {
                  if(v) {
                     a[v].cut(u); R[z] = v;
                  } else {
                     L[z] = R[z] = 0;
                  }
               }
               break ;
            }
            x -= a[u].cnt;
            la = u; u = v;
         }
         // printf("?");
      } else {
         scanf("%d%d", &x, &y);
         if(!L[x]) continue ;
         if(!L[y]) {
            L[y] = R[x]; R[y] = L[x];
            L[x] = R[x] = 0;
         } else {
            a[R[y]].lnk(R[x]);
            a[R[x]].lnk(R[y]);
            R[y] = L[x];
            L[x] = R[x] = 0;
         }
      }
   }
   return 0;
}
