#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int p, a, b, pa[N], pb[N], n, m;
bool vis[N];
void solve() {
  fill(vis, vis + p, 0);
  for(int z = 1, i = 1; i < p; i ++) {
    z = (ll)z * a % p;
    vis[z] = 1;
    if(z == 1) { n = i; break ; }
  }
  for(int z = 1, i = 1; i < p; i ++) {
    z = (ll)z * b % p;
    if(vis[z]) { m = i; break ; }
  }
}
int main() {
  scanf("%d%d%d", &p, &a, &b);
  solve();
  if((ll)n * m != p - 1) {
    puts("No"); return 0;
  }
  // cerr << "n = " << n << ", m = " << m << endl;
  puts("Yes");
  if(n == 1) {
    for(int z = 1, i = 1; i <= p; i ++) {
      printf("%d ", z);
      z = (ll)z * b % p;
    }
    puts("");
    return 0;
  }
  if(m == 1) {
    for(int z = 1, i = 1; i <= p; i ++) {
      printf("%d ", z);
      z = (ll)z * a % p;
    }
    puts("");
    return 0;
  }
  if(n & 1) {
    swap(a, b);
    solve();
  }
  *pa = 1;
  rep(i, 1, n) pa[i] = (ll)pa[i - 1] * a % p;
  *pb = 1;
  rep(i, 1, m) pb[i] = (ll)pb[i - 1] * b % p;

  for(int i = 1, x = 0, y = 0; i <= p; i ++) {
    int z = (ll)pa[x] * pb[y] % p;
    printf("%d ", z);
    if((y == m - 1 && !(x & 1)) || (!y && (x & 1))) {
      x ++;
    } else {
      y += x & 1 ? -1 : 1;
    }
  }
  puts("");
  return 0;
}