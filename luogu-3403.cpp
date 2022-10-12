#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 1e5 + 10;
ull d[N], h;
int x, y, z;
bool vis[N];
int main() {
  scanf("%llu%d%d%d", &h, &x, &y, &z); h --;
  fill(d, d + z, (ull)(-1));
  queue<int> q; q.push(0); vis[0] = 1; d[0] = 0;
  while(q.size()) {
    int u = q.front(); q.pop(); vis[u] = 0;
    int v = (u + x) % z;
    if(d[v] > d[u] + x) {
      d[v] = d[u] + x;
      if(!vis[v]) {
        q.push(v);
        vis[v] = 1;
      }
    }
    v = (u + y) % z;
    if(d[v] > d[u] + y) {
      d[v] = d[u] + y;
      if(!vis[v]) {
        q.push(v);
        vis[v] = 1;
      }
    }
  }
  ull ans = 0;
  for(int i = 0; i < z; i ++)
    if(d[i] <= h) ans += (h - i) / z - (d[i] - i) / z + 1;
  printf("%llu\n", ans);
  return 0;
}