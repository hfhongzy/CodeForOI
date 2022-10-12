#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 45;
const int mod = 1e9 + 7;
int n, cnt[8], id;
void dfs(int u, int r) {
  if(!u) {
    id ++;
    return ;
  }
  for(; r >= 0; r -= u) {
    dfs(u - 1, r);
  }
}
int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i += 2) {
    int c = 0;
    for(int j = i; j <= n; j <<= 1)
      ++ c;
    ++ cnt[c];
  }
  dfs(6, n);
  cerr << "id = " << id << endl;
  return 0;
}
