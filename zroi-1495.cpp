#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 Rand(seed);
uniform_int_distribution<int> range(1, 3), ran(0, 1);
const int N = 1e5 + 10;
int n, m, col[N];
vector<int> G[N];
bool check() {
   rep(i, 1, n) for(int v : G[i]) if(col[v] == col[i]) return 0;
   return 1;
}
int main() {
   // freopen("input/03colors10.in", "r", stdin);
   // freopen("input/03colors10.out", "w", stdout);
   scanf("%d%d", &n, &m); //fprintf(stderr, "n = %d\n", n);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   rep(i, 1, n) col[i] = range(Rand);
   rep(T, 1, 10000) {
      rep(i, 1, n) {
         int cnt[4] = {0}, c = 1;
         for(int v : G[i]) cnt[col[v]] ++;
         rep(j, 2, 3) if(cnt[j] < cnt[c] || (cnt[j] == cnt[c] && ran(Rand))) c = j;
         col[i] = c;
      }
      if(check()) {
         break ;
      }
   }
   rep(i, 1, n) printf("%d ", col[i]);
   return 0;
}