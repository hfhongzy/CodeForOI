#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 10;
struct node {
  int id, l, r;
} a[N];
int n, m;
int main() {
  scanf("%d%d", &n, &m);
  int s = m;
  rep(i, 1, m) {
    scanf("%d%d", &a[i].l, &a[i].r);
    a[i].id = i; s += 2 * (a[i].r - a[i].l + 1);
  }
  printf("%d\n", s);
  rep(i, 1, m) {
    rep(j, a[i].l, a[i].r) printf("+ %d\n", j);
    printf("* %d\n", i);
    rep(j, a[i].l, a[i].r) printf("-\n");
  }
  return 0;
}
