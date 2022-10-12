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

const int N = 4e5 + 5;

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
int n, m, k, r, q;
struct Edge { int v; db w; };
struct Graph {
   vector<Edge> G[N];
   void add(int u, int v, db w) {
      G[u].push_back({v, w});
   }
   struct Node {
      int u; db d;
      bool operator < (const Node &b) const {
         return fabs(d - b.d) < 1e-8 ? 0 : d > b.d;
      }
   };
   db dis[N];
   void Dijkstra(int s, int n) {
      fill(dis + 1, dis + n + 1, 1e18);
      priority_queue<Node> pq; pq.push({s, dis[s] = 0});
      while(pq.size()) {
         int u = pq.top().u; db d = pq.top().d; pq.pop();
         if(dis[u] < d) continue ;
         for(auto e : G[u]) {
            db D = e.v > ::n ? ceil(d) : d;
            if(dis[e.v] > D + e.w) {
               dis[e.v] = D + e.w; pq.push({e.v, dis[e.v]});
            }
         }
      }
   }
} G;
int main() {
   //freopen("A.in", "r", stdin);
   scanf("%d%d%d%d%d", &n, &m, &k, &r, &q);
   int u, v, w;
   rep(i, 1, m) {
      scanf("%d%d%d", &u, &v, &w);
      G.add(u, v, w * 1.0 / r);
      G.add(v, u, w * 1.0 / r);
   }
   int t, c;
   rep(i, 1, k) {
      scanf("%d%d", &t, &c);
      while(t --) {
         scanf("%d", &u);
         G.add(u, n + i, 0);
         G.add(n + i, u, c);
      }
   }
   rep(Q, 1, q) {
      scanf("%d%d", &u, &v);
      G.Dijkstra(u, n + k);
      int ans = ceil(G.dis[v]);
      printf("%d\n", ans);
   }
   return 0;
}