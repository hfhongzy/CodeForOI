#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5e4 + 15, M = 1e4;
int n, m, p, c, a[N], L, Phi[N];
inline int mod(int x) { return x >= p ? x - p : x; }
int phi(int n) {
   int ans = n;
   for(int i = 2; i * i <= n; i ++) {
      if(n % i == 0) {
         ans = ans / i * (i - 1);
         while(n % i == 0) n /= i;
      }
   }
   if(n > 1) ans = ans / n * (n - 1);
   return ans;
}
void init(int p) {
   p = phi(p); L ++; Phi[L] = p;
   if(p == 1) { Phi[++ L] = 1; return ; }
   init(p);
}
int sum[N << 2], mdf[N << 2], cnt[N];
int P[31][M + 5], P2[31][M + 5];
bool T[31][M + 5], T2[31][M + 5];
void prework() {
   rep(i, 0, L) if(Phi[i] > 1) {
      P[i][0] = 1;
      rep(j, 1, M) {
         if(T[i][j - 1] || 1ll * P[i][j - 1] * c >= Phi[i]) {
            T[i][j] = 1; P[i][j] = 1ll * P[i][j - 1] * c % Phi[i];
         } else {
            P[i][j] = P[i][j - 1] * c;
         }
      }
      P2[i][0] = 1;
      rep(j, 1, M) {
         if(T[i][M] || T2[i][j - 1] || 1ll * P2[i][j - 1] * P[i][M] >= Phi[i]) {
            T2[i][j] = 1; P2[i][j] = 1ll * P2[i][j - 1] * P[i][M] % Phi[i];
         } else {
            P2[i][j] = P2[i][j - 1] * P[i][M];
         }
      }
   }
}
int Pow(int x, int id) { //c^x mod Phi[id]
   if(Phi[id] == 1) return 1;
   if(id == 0) return 1ll * P2[id][x / M] * P[id][x % M] % p;
   bool flag = T2[id][x / M] || T[id][x % M];
   if(!flag && 1ll * P2[id][x / M] * P[id][x % M] >= Phi[id]) flag = 1;
   return flag ? 1ll * P2[id][x / M] * P[id][x % M] % Phi[id] + Phi[id] : P2[id][x / M] * P[id][x % M];
}
int calc(int k, int a) { //c^c^c^c(k个)^a
   int ans = 0;
   per(i, k, 0) {
      if(i == k) ans = min(a, a % Phi[i] + Phi[i]);
      else {
         ans = Pow(ans, i);
      }
   }
   return ans % p;
}
void build(int u, int l, int r) {
   if(l == r) { sum[u] = a[l]; return; }
   int mid = (l + r) >> 1; build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
   sum[u] = mod(sum[u << 1] + sum[u << 1 | 1]);
}
void modify(int u, int l, int r) {
   if(mdf[u] >= (r - l + 1) * L) return ;
   if(l == r) { cnt[l] ++; mdf[u] ++; sum[u] = calc(cnt[l], a[l]); return ; }
   int mid = (l + r) >> 1;
   modify(u << 1, l, mid); modify(u << 1 | 1, mid + 1, r);
   sum[u] = mod(sum[u << 1] + sum[u << 1 | 1]);
   mdf[u] = mdf[u << 1] + mdf[u << 1 | 1];
}
void modify(int u, int l, int r, int ql, int qr) {
   if(mdf[u] >= (r - l + 1) * L) return ;
   if(l == ql && r == qr) { modify(u, l, r); return ; }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr);
   else {
      modify(u << 1, l, mid, ql, mid);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr);
   }
   sum[u] = mod(sum[u << 1] + sum[u << 1 | 1]);
   mdf[u] = mdf[u << 1] + mdf[u << 1 | 1];
}
int query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return sum[u];
   int mid = (l + r) >> 1;
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return mod(query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr));
}
int main() {
   scanf("%d%d%d%d", &n, &m, &p, &c);
   rep(i, 1, n) scanf("%d", a + i);
   Phi[0] = p; init(p); prework();
   // rep(i, 1, L) printf("p = %d\n", Phi[i]);
   build(1, 1, n);
   int op, l, r;
   rep(i, 1, m) {
      scanf("%d%d%d", &op, &l, &r);
      if(op == 0) modify(1, 1, n, l, r);
      if(op == 1) printf("%d\n", query(1, 1, n, l, r));
   }
   return 0;
}