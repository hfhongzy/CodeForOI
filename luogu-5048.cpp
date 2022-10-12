#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int B = 707;
int n, m, a[N], num[N], bel[N], L[N / B + 5], R[N / B + 5], p[N];
int res[N / B + 5][N / B + 5];
vector<int> vec[N];
bool checkL(int l, int r, int low) {
  return int(vec[a[l]].size()) - p[l] + 1 >= low && vec[a[l]][p[l] + low - 2] <= r;
}
bool checkR(int l, int r, int low) {
  return p[r] >= low && vec[a[r]][p[r] - low] >= l;
}
int query(int l, int r) {
  int ans = res[bel[l] + 1][bel[r] - 1];
  if(bel[l] + 1 > bel[r] - 1) {
    rep(i, l, r) {
      while(checkR(l, i, ans + 1)) ++ ans;
    }
  } else {
    int x = L[bel[l] + 1];
    int y = R[bel[r] - 1];
    per(i, x - 1, l) {
      while(checkL(i, y, ans + 1)) ++ ans;
    }
    rep(i, y + 1, r) {
      while(checkR(l, i, ans + 1)) ++ ans;
    }
  }
  return ans;
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", a + i), num[i] = a[i];
  sort(num + 1, num + n + 1);
  rep(i, 1, n) a[i] = lower_bound(num + 1, num + n + 1, a[i]) - num;
  rep(i, 1, n) bel[i] = (i - 1) / B + 1;
  rep(i, 1, n) {
    if(!L[bel[i]]) L[bel[i]] = i;
    R[bel[i]] = i;
  }
  rep(i, 1, bel[n]) {
    static int cnt[N];
    fill(cnt, cnt + n + 1, 0);
    int mx = 0;
    rep(j, i, bel[n]) {
      rep(k, L[j], R[j]) mx = max(mx, ++ cnt[a[k]]);
      res[i][j] = mx;
    }
  }
  rep(i, 1, n) {
    vec[a[i]].pb(i);
    p[i] = int(vec[a[i]].size());
  }
  int l, r, lans = 0;
  rep(T, 1, m) {
    scanf("%d%d", &l, &r);
    l ^= lans; r ^= lans;
    printf("%d\n", lans = query(l, r));
  }
  return 0;
}