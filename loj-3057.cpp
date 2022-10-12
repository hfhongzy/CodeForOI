#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5005;
int n, m, q;
char str[N];
vector<int> G[N];
namespace sub {

bool vis[N][N];
int q[N * N][2], ql, qr;
void main() {
   rep(i, 1, n) {
      vis[i][i] = 1;
      q[qr][0] = q[qr][1] = i; qr ++;
      rep(j, 0, (int) G[i].size() - 1) {
         int v = G[i][j];
         if(str[v] != str[i]) continue ;
         q[qr][0] = i; q[qr][1] = v; qr ++; vis[i][v] = 1;
      }
   }
   while(ql < qr) {
      int u = q[ql][0], v = q[ql][1]; ql ++;
      rep(i, 0, (int) G[u].size() - 1) {
         int x = G[u][i];
         rep(j, 0, (int) G[v].size() - 1) {
            int y = G[v][j];
            if(str[x] == str[y] && !vis[x][y]) {
               q[qr][0] = x; q[qr][1] = y; qr ++; vis[x][y] = 1;
            }
         }
      }
   }
   rep(i, 1, ::q) {
      int u, v; sscanf("%d%d", &u, &v);
      puts(vis[u][v] || vis[v][u] ? "YES" : "NO");
   }
}

}
namespace sol {

bool vis[N][N];
int q[N * N][2], ql, qr;
vector<int> nG[N];

void main() {
   rep(i, 1, n) {
      vis[i][i] = 1;
      q[qr][0] = q[qr][1] = i; qr ++;
      rep(j, 0, (int) nG[i].size() - 1) {
         int v = nG[i][j];
         if(str[v] != str[i]) continue ;
         q[qr][0] = i; q[qr][1] = v; qr ++; vis[i][v] = 1;
      }
   }
   while(ql < qr) {
      int u = q[ql][0], v = q[ql][1]; ql ++;
      rep(i, 0, (int) nG[u].size() - 1) {
         int x = nG[u][i];
         rep(j, 0, (int) nG[v].size() - 1) {
            int y = nG[v][j];
            if(str[x] == str[y] && !vis[x][y]) {
               q[qr][0] = x; q[qr][1] = y; qr ++; vis[x][y] = 1;
            }
         }
      }
   }
   rep(i, 1, ::q) {
      int u, v; sscanf("%d%d", &u, &v);
      puts(vis[u][v] || vis[v][u] ? "YES" : "NO");
   }
}

}
int main() {
   scanf("%d%d%d%s", &n, &m, &q, str + 1);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   if(m <= 10000) {
      sub::main();
   } else {
      sol::main();
   }
   return 0;
}