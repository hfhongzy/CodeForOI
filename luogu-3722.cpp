#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct answer {
   int x, l, r, v;
   bool operator < (const answer &b) const {
      return x < b.x;
   }
};
vector<answer> va;
struct ques {
   int x, l, r, sgn, id;
   bool operator < (const ques &b) const {
      return x < b.x;
   }
};
vector<ques> vq;
int n, m, p1, p2, p[N], L[N], R[N];
ll ans[N], bit[N][2], dt;
void modify(int u, ll v) {
   dt += v;
   for(ll c = u * v; u <= n; u += u & (-u)) {
      bit[u][0] += v; bit[u][1] += c;
   }
}
void modify(int l, int r, int v) {
   modify(r, v); if(l > 1) modify(l - 1, -v);
}
ll query(int u) {
   ll ans = 0, val = dt;
   for(int z = u; z >= 1; z &= z - 1) {
      ans += bit[z][1]; val -= bit[z][0];
   }
   ans += val * u;
   return ans;
}
ll query(int l, int r) { return query(r) - query(l - 1); }
int main() {
   scanf("%d%d%d%d", &n, &m, &p1, &p2);
   rep(i, 1, n) scanf("%d", p + i);
   stack<int> S;
   rep(i, 1, n) {
      while(S.size() && p[S.top()] < p[i]) S.pop();
      L[i] = S.size() ? S.top() : 0; S.push(i);
   }
   while(S.size()) S.pop();
   per(i, n, 1) {
      while(S.size() && p[S.top()] < p[i]) S.pop();
      R[i] = S.size() ? S.top() : n + 1; S.push(i);
   }
   rep(i, 1, n) {
      if(L[i] && R[i] <= n) {
         va.pb({L[i], R[i], R[i], p1});
      }
      if(L[i] && i + 1 <= R[i] - 1) {
         va.pb({L[i], i + 1, R[i] - 1, p2});
      }
      if(R[i] <= n && L[i] + 1 <= i - 1) {
         va.pb({R[i], L[i] + 1, i - 1, p2});
      }
   }
   int l, r;
   rep(i, 1, m) {
      scanf("%d%d", &l, &r);
      ans[i] = 1ll * (r - l) * p1;
      if(l > 1) vq.pb((ques) {l - 1, l, r, -1, i});
      vq.pb((ques) {r, l, r, 1, i});
   }
   sort(va.begin(), va.end());
   sort(vq.begin(), vq.end());
   vector<answer>::iterator A = va.begin();
   vector<ques>::iterator Q = vq.begin();
   rep(i, 1, n) {
      while(A != va.end() && A->x <= i) {
         modify(A->l, A->r, A->v); A ++;
      }
      while(Q != vq.end() && Q->x <= i) {
         ans[Q->id] += Q->sgn * query(Q->l, Q->r); Q ++;
      }
   }
   rep(i, 1, m) printf("%lld\n", ans[i]);
   return 0;
}