#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 110, mod = 1e9 + 7;
int n, m, l, id = 1, len[N], fail[N], ch[N][26];
char unit[N][N];
bool tag[N];
void insert(char *s) {
   int u = 1;
   for(; *s; s ++) {
      int &v = ch[u][*s - 'a'];
      u = v ? v : v = ++ id;
   }
   tag[u] = 1;
}
void build() {
   queue<int> q; int v; fail[1] = 1;
   for(int i = 0; i < 26; i ++) if((v = ch[1][i]) > 0) {
      q.push(v); fail[v] = 1;
   } else ch[1][i] = 1;
   while(q.size()) {
      int u = q.front(); q.pop(); tag[u] |= tag[fail[u]];
      for(int i = 0; i < 26; i ++) if((v = ch[u][i]) > 0) {
         fail[v] = ch[fail[u]][i]; q.push(v);
      } else ch[u][i] = ch[fail[u]][i];
   }
}
void task1() {
   static int dp[N][N], tr[N][N]; //dp[l][id]
   for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= id; j ++) {
         int u = j; bool t = tag[u];
         for(int k = 1; k <= len[i]; k ++) {
            u = ch[u][unit[i][k]]; t |= tag[u];
            if(t) break ;
         }
         tr[i][j] = t ? 0 : u;
      }
   }
   dp[0][1] = 1;
   for(int i = 0; i < l; i ++) {
      for(int j = 1; j <= id; j ++) if(dp[i][j]) {
         for(int k = 1; k <= n; k ++) if(i + len[k] <= l && tr[k][j]) {
            (dp[i + len[k]][tr[k][j]] += dp[i][j]) %= mod;
         }
      }
   }
   int ans = 0;
   for(int i = 1; i <= id; i ++)
      (ans += dp[l][i]) %= mod;
   printf("%d\n", ans);
}
struct mat {
   int a[N * 2][N * 2], n, m;
   mat operator * (const mat &b) {
      mat ans; ans.n = n; ans.m = b.m;
      for(int i = 1; i <= ans.n; i ++) {
         for(int j = 1; j <= ans.m; j ++) {
            ans.a[i][j] = 0;
            for(int k = 1; k <= m; k ++) {
               (ans.a[i][j] += 1ll * a[i][k] * b.a[k][j] % mod) %= mod;
            }
         }
      }
      return ans;
   }
} fir, tr;
mat Pow(mat a, int b) {
   mat ans = a; b --;
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
void task2() {
   fir.n = 1; fir.m = id * 2; fir.a[1][1] = 1;
   tr.n = tr.m = id * 2;
   for(int i = id + 1; i <= 2 * id; i ++) tr.a[i - id][i] = 1;
   for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= id; j ++) {
         int u = j; bool t = tag[u];
         for(int k = 1; k <= len[i]; k ++) {
            u = ch[u][unit[i][k]]; t |= tag[u];
            if(t) break ;
         }
         if(!t) {
            tr.a[len[i] == 1 ? j : id + j][u] ++;
         }
      }
   }
   fir = fir * Pow(tr, l);
   int ans = 0;
   for(int i = 1; i <= id; i ++)
      (ans += fir.a[1][i]) %= mod;
   printf("%d\n", ans);
}
int main() {
   scanf("%d%d%d", &n, &m, &l);
   for(int i = 1; i <= n; i ++) {
      scanf("%s", unit[i] + 1);
      len[i] = strlen(unit[i] + 1);
      for(int j = 1; j <= len[i]; j ++)
         unit[i][j] -= 'a';
   }
   for(int i = 0; i < m; i ++) {
      static char str[N];
      scanf("%s", str);
      insert(str);
   }
   build();
   if(l <= 100) task1(); else task2();
   return 0;
}
/*
4 2 10
ab
ba
aa
a
bba
abb
*/