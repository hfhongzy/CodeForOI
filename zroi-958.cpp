#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, a[N][2], d[N][2], f[N][2];
bool vis[N][2];
int find(int u, int o) {
   if(f[u][o] == u) return u;
   int v = find(f[u][o], o);
   d[u][o] += d[f[u][o]][o];
   return f[u][o] =  v;
}
int q[N * 2][2], ql, qr;
void push(int u, int o) {
   if(vis[u][o]) return ;
   q[qr][0] = u; q[qr][1] = o; qr ++; vis[u][o] = 1;
}
bool check(int mid) {
   if(mid == 0) return n == 1;
   rep(i, 1, n) {
      vis[i][0] = vis[i][1] = 0;
      d[i][0] = d[i][1] = 0;
      f[i][0] = f[i][1] = i;
   }
   ql = qr = 0; push(1, 0); push(1, 1);
   for(; ql < qr; ql ++) {
      int u = q[ql][0], o = q[ql][1];
      int v = a[u][o], t = v;
      while(1) {
         t = find(t, o);
         if(find(v, o), d[v][o] >= mid) break ;
         push(t, o ^ 1);
         if(find(a[t][o], o) == t) break ;
         f[t][o] = a[t][o]; d[t][o] = 1;
      }
   }
   return vis[n][0] || vis[n][1];
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d%d", a[i], a[i] + 1);
   int l = 0, r = n, ans = -1;
   while(l <= r) {
      int mid = (l + r) >> 1;
      if(check(mid)) r = (ans = mid) - 1;
      else l = mid + 1;
   }
   printf("%d\n", ans);
   return 0;
}
/*
5
3 2
4 3
5 2
2 3
1 2
*/