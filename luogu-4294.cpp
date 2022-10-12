#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define queue STL_queue_Always_MLE
using namespace std;
typedef pair<int, int> pii;
const int N = 105, INF = 1e9 + 10;

template<class T>
inline bool chkmin(T &x, const T &y) {
   if(x > y) { x = y; return 1; }
   return 0;
}

template <class T>
struct queue {
   T q[1 << 18], *l, *r;
   queue() { l = r = q; }
   inline int get() { return *l ++; }
   inline void push(T x) { *r ++ = x; }
   inline void clear() { l = r = q; }
   inline bool empty() { return l == r; }
};
int n, m, k, w[N], dp[N][1 << 10];
pii pre[N][1 << 10];
char ans[N][N];

vector<int> G[N];
queue<int> q;
bool use[N];
void spfa(int s) {
   while(!q.empty()) {
      int u = q.get(); use[u] = 0;
      for(int v : G[u]) if(dp[v][s] > w[v] + dp[u][s]) {
         dp[v][s] = w[v] + dp[u][s];
         pre[v][s] = mp(u, s);
         if(!use[v]) { use[v] = 1; q.push(v); }
      }
   }
}
// int ID(int x, int y) { return m * (x - 1) + y; }
void solve(int x, int y) {
   if(!x || !y) return ;
   if(w[x]) ans[(x + m - 1) / m][(x - 1) % m + 1] = 'o';
   if(pre[x][y].fs == x) {
      solve(x, pre[x][y].sc);
      solve(x, y ^ pre[x][y].sc);
   } else {
      solve(pre[x][y].fs, y);
   }
}
int main() {
   scanf("%d%d", &n, &m);
   memset(dp, 0x3f, sizeof dp);
   int c = 0;
   rep(i, 1, n) rep(j, 1, m) {
      c ++;
      scanf("%d", w + c);
      if(!w[c]) {
         ans[i][j] = 'x';
         dp[c][1 << k] = 0;
         k ++;
      } else ans[i][j] = '_';
      if(i < n) { G[c].pb(c + m); G[c + m].pb(c); }
      if(j < m) { G[c].pb(c + 1); G[c + 1].pb(c); }
   }
   rep(i, 1, (1 << k) - 1) {
      q.clear();
      rep(j, 1, c) {
         for(int s = i; s; s = (s - 1) & i) {
            if(chkmin(dp[j][i], dp[j][s] + dp[j][i ^ s] - w[j])) {
               pre[j][i] = mp(j, s);
            }
         }
         if(dp[j][i] < INF) {
            q.push(j); use[j] = 1;
         }
      }
      spfa(i);
   }
   int res = INF, st = 0;
   rep(i, 1, c) if(chkmin(res, dp[i][(1 << k) - 1])) st = i;
   printf("%d\n", res);
   solve(st, (1 << k) - 1);
   rep(i, 1, n) puts(ans[i] + 1);
   return 0;
}