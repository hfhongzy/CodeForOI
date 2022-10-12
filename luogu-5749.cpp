#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, bit[N], a[N * 2], all;
vector<int> q[2][N];
vector< pair<int, int> > vec;
ll ans;
void ins(int u) {
   all ++;
   for(; u <= n; u += u & (-u)) bit[u] ++;
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) ans += bit[u];
   return ans;
}
int main() {
   scanf("%d", &n); n <<= 1;
   rep(i, 1, n) {
      scanf("%d", a + i);
      int y = a[i] < 0 ? 0 : 1, z = y ? a[i] : - a[i];
      if(!q[y ^ 1][z].size()) q[y][z].push_back(i);
      else {
         ans += !y;
         int u = *q[y ^ 1][z].begin();
         q[y ^ 1][z].erase(q[y ^ 1][z].begin());
         vec.push_back(make_pair(u, i));
      }
   }
   sort(vec.begin(), vec.end());
   for(auto &v : vec) {
      ans += 2 * all - qry(v.first) - qry(v.second);
      ins(v.first); ins(v.second);
   }
   printf("%lld\n", ans);
   return 0;
}