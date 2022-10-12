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

const int N = 5000 + 5;
const int M = 2000 + 5;
const int INF = 2e9 + 10;

char gc() {
   // return getchar();
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
int n, m, k, ans = INF, a[N], b[N];
short c[N][M], cl[N][M], arr[N][M], arr2[N][M];
int main() {
   //freopen("A.in", "r", stdin);
   read(n); read(m); read(k);
   rep(i, 1, n) { read(a[i]); read(b[i]); }
   rep(i, 1, n) rep(j, 1, m) read(c[i][j]);
   rep(i, 1, n) rep(j, 1, m) cl[i][j] = j == 1 ? c[i][j] : min(cl[i][j - 1], c[i][j]);
   static int q[N];
   rep(i, 1, n) {
      int ql = 1, qr = 0;
      rep(x, k, m - b[i]) {
         while(ql <= qr && c[i][q[qr]] >= c[i][x]) {
            qr --;
         }
         q[++ qr] = x;
      }
      rep(t, 1, m - k + 1) { //t + k <= x <= min(m, m + t - b[i])
         if(t <= b[i]) {
            int x = m + t - b[i];
            while(ql <= qr && c[i][q[qr]] >= c[i][x]) {
               qr --;
            }
            q[++ qr] = x;
         }
         while(ql <= qr && q[ql] < t + k) ql ++;
         arr[i][t] = ql <= qr ? c[i][q[ql]] : -1; 
      }
   }
   rep(t, 1, m - k + 1) {
      int res = 0;
      rep(i, 1, n) {
         int cost = ~ arr[i][t] ? arr[i][t] : INF;
         if(t - b[i] >= 1) {
            cost = min(cost, (int)cl[i][t - b[i]]);
         }
         if(cost == INF) { res = INF; break ; }
         res += cost;
      }
      ans = min(ans, res);
   }
   // ans = INF;
   rep(i, 1, n) {
      int ql = 1, qr = 0;
      rep(x, 1, m - k + 1 - b[i]) {
         while(ql <= qr && c[i][q[qr]] >= c[i][x]) {
            qr --;
         }
         q[++ qr] = x;
      }
      rep(t, m - k + 2, m) { //L + 1 <= x <= t - b[i]
         int L = k - (m - t + 1);
         if(t - b[i] >= 1) {
            int x = t - b[i];
            while(ql <= qr && c[i][q[qr]] >= c[i][x]) {
               qr --;
            }
            q[++ qr] = x;
         }
         while(ql <= qr && q[ql] <= L) ql ++;
         arr2[i][t] = ql <= qr ? c[i][q[ql]] : -1; 
      }
   }
   rep(t, m - k + 2, m) {
      int res = 0;
      rep(i, 1, n) {
         int cost = ~ arr2[i][t] ? arr2[i][t] : INF;
         if(cost == INF) { res = INF; break ; }
         res += cost;
      }
      ans = min(ans, res);
   }
   if(ans == INF) ans = -1;
   printf("%d\n", ans);
   return 0;
}