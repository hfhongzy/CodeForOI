#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1005;
void observe(int n = 100) {
  static int sg[N]; sg[0] = 0;
  rep(i, 1, n) {
    vector<bool> vis(N);
    vis[0] = 1;
    rep(j, 1, i - 1) vis[sg[j]] = 1;
    rep(j, 1, i - 1) rep(k, j + 1, i - 1)
      vis[sg[j] ^ sg[k]] = 1;
    sg[i] = 0;
    while(vis[sg[i]]) ++ sg[i];
  }
}
int main() {
  // observe();
  int n;
  while(~ scanf("%d", &n)) {
    int z = 0;
    set<int> s;
    rep(i, 1, n) {
      int x; scanf("%d", &x);
      if(!s.insert(x).second) continue ;
      z ^= x * 2 + ((__builtin_popcount(x) & 1) ^ 1);
    }
    puts(!z ? "Yes" : "No");
  }
  return 0;
}