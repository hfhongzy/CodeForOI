#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int INF = 2e9;
struct node {
  int l, r, w;
} a[N];
int n, all, num[N], m, sum[N];
int arr[N], t;
bool mark[N];
int Max(int x, int y) {
  if(abs(x) != abs(y)) return abs(x) < abs(y) ? x : y;
  return max(x, y);
}
int best(int l, int r) {
  if(l <= 0 && 0 <= r) return 0;
  return Max(l, r);
}
int main() {
  scanf("%d", &n);
  int op, l, r, w;
  rep(i, 1, n) {
    scanf("%d", &op);
    if(op == 1) {
      scanf("%d%d%d", &l, &r, &w);
      num[++ m] = l; num[++ m] = r;
      a[i] = {l, r, w};
    }
    if(op == 2) {
      scanf("%d%d", &l, &w);
      num[++ m] = l;
      a[i] = {l, l, w};
    }
    if(op == 3) {
      scanf("%d%d", &l, &w); all ^= w;
      num[++ m] = l;
      a[i] = {l, l, w};
    }
  }
  sort(num + 1, num + m + 1);
  m = unique(num + 1, num + m + 1) - num - 1;
  rep(i, 1, m) {
    arr[++ t] = num[i];
    if(i < m && num[i + 1] > num[i] + 1) {
      arr[++ t] = num[i] + 1; mark[t] = 1;
    }
  }
  rep(i, 1, n) {
    a[i].l = lower_bound(arr + 1, arr + t + 1, a[i].l) - arr;
    a[i].r = lower_bound(arr + 1, arr + t + 1, a[i].r) - arr;
    sum[a[i].l] ^= a[i].w;
    sum[a[i].r + 1] ^= a[i].w;
  }
  rep(i, 1, t) sum[i] ^= sum[i - 1];
  int ans = -1, res = -1;
  rep(i, 1, t) {
    int c = sum[i] ^ all, d = mark[i] ? best(arr[i], arr[i + 1] - 1) : arr[i];
    if(c > ans) {
      ans = c; res = d;
    } else if(c == ans) {
      res = Max(res, d);
    }
  }
  int c = all, d = Max(best(-INF, arr[1] - 1), best(arr[t] + 1, INF));
  if(ans < c) {
    ans = c; res = d;
  } else if(ans == c) {
    res = Max(res, d);
  }
  printf("%d %d\n", ans, res);
  return 0;
}