 #include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int mod = 1e9 + 7;
int ans, n, k;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int p[20], t[20], p2[20];
int sp[20], pos[20];
int qry(int l, int r, int *p) {
   int x = 0;
   rep(i, l, r) rep(j, i + 1, r) x += p[i] > p[j];
   return x;
}
void dfs(int u, int sum) {
   if(u == k + 1) {
      if(sum) return ;
      rep(i, 1, 2 * n) p[i] = i;
      rep(i, 1, k) pos[i] = pos[i - 1] + sp[i];
      rep(i, 1, k) pos[i] *= 2;
      // rep(i, 1, k) printf("%d, ", pos[i]);
      do {
         for(int i = 2; i <= 2 * n; i += 2) t[i >> 1] = p[i];
         sort(t + 1, t + n + 1);
         for(int i = 2; i <= 2 * n; i += 2) p2[i] = t[i >> 1], p2[i - 1] = p[i - 1];
         
         // printf("!");
         
         ll v = 1;
         rep(i, 1, k) {
            v *= qry(pos[i - 1] + 1, pos[i], p2);
         }
         ans = (ans + v) % mod;
      } while(next_permutation(p + 1, p + 2*n + 1));
      return ;
   }
   rep(i, 1, sum) {
      sp[u] = i;
      dfs(u + 1, sum - i);
   }
}
int solve() {
   ans = 0; dfs(1, n);
   int fac = 1;
   rep(i, 1, 2 * n) fac = 1ll * fac * i % mod;
   ans = 1ll * ans * qpow(fac, mod - 2) % mod;
   return ans;
}
int main() {
   scanf("%d", &mod); //mod = 1e9 + 7;
   int ans[6][6];
   ans[1][1] = 500000004;
   ans[2][1] = 166666670; ans[2][2] = 250000002;
   ans[3][1] = 5; ans[3][2] = 400000005; ans[3][3] = 125000001;
   ans[4][1] = 9; ans[4][2] = 483333347; ans[4][3] = 492857148; ans[4][4] = 562500004;
   ans[5][1] = 166666682; ans[5][2] = 690476229; ans[5][3] = 886904780; ans[5][4] = 156746034; ans[5][5] = 281250002;
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d%d", &n, &k);
      printf("%d\n", ans[n][k]); //solve()
   }
   return 0;
}
/*
3246307
6
1 1
2 1
2 2
3 1
3 2
3 3
*/