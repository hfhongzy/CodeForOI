#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct node { int x, y; } a[N];
int n, st1[N], top1, st2[N], top2;
ll solve(int l, int r) {
  if(l == r) return 0;
  int mid = (l + r) >> 1, p = mid;
  ll ans = solve(l, mid) + solve(mid + 1, r);
  top1 = top2 = 0;
  rep(i, l, mid) {
    while(p < r && a[p + 1].y > a[i].y) {
      ++ p;
      while(top2 && a[st2[top2]].x > a[p].x) top2 --;
      st2[++ top2] = p;
    }
    int z = lower_bound(st1 + 1, st1 + top1 + 1, a[i].x, [&](int x, int val) { return a[x].x > val; }) - st1 - 1;
    int up = !z ? 1<<30 : a[st1[z]].y;
    ans += top2 - ( lower_bound(st2 + 1, st2 + top2 + 1, up, [&](int x, int val) { return a[x].y > val; }) - st2 ) + 1;
    while(top1 && a[st1[top1]].x < a[i].x) top1 --;
    st1[++ top1] = i;
  }
  inplace_merge(a + l, a + mid + 1, a + r + 1, [&](node a, node b) { return a.y > b.y; });
  return ans;
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
  sort(a + 1, a + n + 1, [&](node a, node b) { return a.x < b.x; });
  printf("%lld\n", solve(1, n));
  return 0;
}