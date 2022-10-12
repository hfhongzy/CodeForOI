#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int M = 12;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int id, n, m, rt, a[M][N], w[N], ls[N], rs[N]; //-1:? -2:max -3:min; 0~9
char s[N];
int dp[N][2], res[1 << M];
vector<int> vec;
void dfs(int u) {
  if(u) { dfs(ls[u]); dfs(rs[u]); vec.push_back(u); }
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 0, m - 1) rep(j, 1, n) scanf("%d", a[i] + j);
  scanf("%s", s + 1);
  stack<int> op, num;
  int cnt = 0;
  for(int i = 1; s[i]; i ++) {
    if(isdigit(s[i])) {
      w[++ id] = s[i] - '0';
      if(op.size() && op.top()) {
        int u = op.top();
        ls[u] = num.top(); num.pop(); rs[u] = id; num.push(u); op.pop();
      } else {
        num.push(id);
      }
    } else if(s[i] == '(') {
      op.push(0);
    } else if(s[i] == ')') {
      op.pop();
      if(op.size() && op.top()) {
        int u = op.top(); op.pop();
        int v1 = num.top(); num.pop();
        int v2 = num.top(); num.pop();
        ls[u] = v2; rs[u] = v1;
        num.push(u);
      }
    } else {
      if(s[i] == '?') cnt ++;
      w[++ id] = (s[i] == '?' ? -1 : (s[i] == '>' ? -2 : -3));
      op.push(id);
    }
  }
  rt = num.top(); dfs(rt);
  for(int i = 0; i < (1 << m); i ++) {
    for(int u : vec) {
      if(!ls[u]) { dp[u][1] = i >> w[u] & 1; dp[u][0] = !dp[u][1]; continue ; }
      if(w[u] != -2) {
        dp[u][0] = ( (ll)dp[ls[u]][0] * dp[rs[u]][1] + (ll)dp[ls[u]][0] * dp[rs[u]][0] + (ll)dp[ls[u]][1] * dp[rs[u]][0] ) % mod;
        dp[u][1] = (ll)dp[ls[u]][1] * dp[rs[u]][1] % mod;
      } else {
        dp[u][0] = dp[u][1] = 0;
      }
      if(w[u] != -3) {
        dp[u][1] = (dp[u][1] + (ll)dp[ls[u]][0] * dp[rs[u]][1] + (ll)dp[ls[u]][1] * dp[rs[u]][0] + (ll)dp[ls[u]][1] * dp[rs[u]][1]) % mod;
        dp[u][0] = (dp[u][0] + (ll)dp[ls[u]][0] * dp[rs[u]][0]) % mod;
      }
    }
    res[i] = dp[rt][1];
  }
  int ans = 0;
  rep(i, 1, n) {
    static int p[M];
    rep(j, 0, m - 1) p[j] = j;
    sort(p, p + m, [&](int x, int y) { return a[x][i] > a[y][i]; });
    int st = 0;
    rep(j, 0, m - 1) {
      int u = p[j];
      ans = (ans + a[u][i] * (ll)(res[st ^ (1 << u)] - res[st] + mod)) % mod;
      st ^= 1 << u;
    }
  }
  printf("%d\n", ans);
  return 0;
}