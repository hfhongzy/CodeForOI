#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
int n, h[N];
ll rk_l, rk_r;
namespace sub {

ll res[1000005];
int c;
void main() {
   rep(i, 1, n) {
      int mn = h[i];
      rep(j, i, n) {
         mn = min(mn, h[j]);
         res[++ c] = mn * (j - i + 1ll);
      }
   }
   sort(res + 1, res + c + 1);
   rep(i, rk_l, rk_r) printf("%lld ", res[i]);
   putchar('\n');
}

}
namespace sol {

int l[N], r[N], st[N], top, pos[N], mh;
ll vl, vr;
vector<ll> ans;
void init() {
   top = 0;
   rep(i, 1, n) {
      while(top && h[st[top]] > h[i]) top --;
      l[i] = top ? i - st[top] : i;
      st[++ top] = i;
   }
   top = 0;
   per(i, n, 1) {
      while(top && h[st[top]] >= h[i]) top --;
      r[i] = top ? st[top] - i : n - i + 1;
      st[++ top] = i;
   }
}
ll f(ll L, ll R, ll len) { //f(len), len <= L + R - 1
   if(L > R) swap(L, R);
   if(len <= L) return len;
   if(len <= R) return L;
   return L + R - len;
}
ll func(ll L, ll R, ll len) { //f(1)+...+f(len)
   if(L > R) swap(L, R);
   len = min(len, L + R - 1);
   // ll a = 0; rep(i, 1, len) a += f(L, R, i); return a;
   if(len <= L) return len * (len + 1) / 2;
   if(len <= R) return L * (L + 1) / 2 + (len - L) * L;
   return L * (L + 1) / 2 + (R - L) * L + (L + R) * (len - R) - (R + 1 + len) * (len - R) / 2;
}
ll calc(ll mid) { //min*len <= mid
   ll ans = 0;
   rep(i, 1, n) {
      ans += func(l[i], r[i], mid / h[i]);
   }
   return ans;
}
ll kth(ll k) {
   ll l = 0, r = (ll) mh * n, ans;
   while(l <= r) {
      ll mid = (l + r) >> 1;
      if(calc(mid) >= k) r = (ans = mid) - 1;
      else l = mid + 1;
   }
   return ans;
}
void Pb(ll z, int t) {
   while(t --) ans.push_back(z);
}
void main() {
   init();
   mh = *max_element(h + 1, h + n + 1);
   // rep(i, 1, n) pos[i] = i;
   // sort(pos + 1, pos + n + 1, [&](int x, int y) { return h[x] < h[y] || (h[x] == h[y] && x < y); })
   vl = kth(rk_l); vr = kth(rk_r);
   // printf("%lld %lld\n", vl, vr);
   // rep(i, 1, 6) printf("calc %d = %lld\n", i, calc(i));
   rep(i, 1, n) { //min*len \in [vl, vr - 1]
      ll L = (vl + h[i] - 1) / h[i];
      ll R = min((vr - 1) / h[i], l[i] + r[i] - 1ll);
      for(ll j = L; j <= R; j ++) {
         Pb((ll)h[i] * j, f(l[i], r[i], j));
      }
   }
   ll pk = calc(vl - 1), out = rk_r - rk_l + 1;
   sort(ans.begin(), ans.end());
   for(int i = rk_l - pk - 1; i < (int) ans.size(); i ++) printf("%lld ", ans[i]), -- out;
   while(out --) printf("%lld ", vr);
   putchar('\n');
}

}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) {
      scanf("%d", h + i);
   }
   scanf("%lld%lld", &rk_l, &rk_r);
   if(n <= 1000) sub::main();
   else sol::main();
   return 0;
}