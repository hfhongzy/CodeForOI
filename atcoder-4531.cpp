#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef double db;

const int N = 305;

int n, a[N], cnt[4];
db f[N][N][N];
bool vis[N][N][N];

db dfs(int x, int y, int z) {
   if(x == 0 && y == 0 && z == 0) return 0;
   db &res = f[x][y][z];
   if(vis[x][y][z]) return res;
   vis[x][y][z] = 1; res = 1;
   if(x) res += dfs(x - 1, y, z) * x / n;
   if(y) res += dfs(x + 1, y - 1, z) * y / n;
   if(z) res += dfs(x, y + 1, z - 1) * z / n;
   return res /= (x + y + z) * 1.0 / n;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i), cnt[a[i]] ++;
   printf("%.12f\n", dfs(cnt[1], cnt[2], cnt[3]));
   return 0;
}