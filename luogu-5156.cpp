#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const ll INF = 1ll << 61;
struct node {
   int mx;
   ll cnt;
   node operator + (node rhs) { 
      if(mx < rhs.mx) return rhs;
      if(mx > rhs.mx) return *this;
      return {mx, min(INF, cnt + rhs.cnt)};
   }
   void operator += (node rhs) { *this = *this + rhs; }
} t[N], bit[N];
int n, a[N], pos[N];
vector<int> st[N];
ll k;
bool vis[N];
void insert(int u, node x) {
   for(; u >= 1; u &= u - 1) {
      bit[u] += x;
   }
}
node query(int u) {
   node ans = {0, 1};
   for(; u <= n; u += u & (-u)) {
      ans += bit[u];
   }
   return ans;
}
int main() {
   scanf("%d%lld", &n, &k);
   rep(i, 1, n) scanf("%d", a + i), pos[a[i]] = i;
   per(i, n, 1) {
      t[i] = query(pos[i]); t[i].mx ++;
      insert(pos[i], t[i]);
      st[t[i].mx].pb(i);
   }
   int m = query(1).mx, cur = 0;
   per(i, m, 1) {
      for(int v : st[i]) if(pos[cur] < pos[v]) {
         k -= t[v].cnt;
         if(k <= 0) {
            k += t[v].cnt;
            cur = v;
            vis[v] = 1;
            break ;
         }
      }
   }
   printf("%d\n", n - m);
   rep(i, 1, n) if(!vis[i]) printf("%d\n", i);
   return 0;
}