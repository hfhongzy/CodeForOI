#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
const int mod = 998244353;
int m, n, p, pos[N], c[N];
char s[N], res[N];
ll invs;
deque<int> q;
int main() {
   scanf("%d%s", &m, s + 1); n = strlen(s + 1);
   int cnt = 0;
   rep(i, 1, n) {
     res[i] = '0';
      if(s[i] == '1') cnt ++, pos[++ p] = i;
      else invs += cnt;
   }
   rep(i, 1, m) q.push_back(p + i);
   rep(i, 1, p) {
      int l = p - i + 1, r = p - i + m;
      q.push_front(l);
      while(q.size() && q.back() > r) {
         q.pop_back();
      }
      int k = pos[i] - pos[i - 1] - 1;
      while(k -- && q.size()) {
         int x = q.front();
         c[x - l + 1] ++;
         if(x < m) c[x + 1] --;
         q.pop_front();
      }
      res[pos[i] - (m - q.size())] = '1';
   }
   rep(i, 1, m) c[i] += c[i - 1];
   int ans = invs % mod, bas = 1;
   //printf("%lld!", invs * 1ll);
   rep(i, 1, m) {
      bas = bas * 233ll % mod;
      invs = (invs + c[i]) % mod;
      //printf("%lld!", invs * 1ll);
      ans ^= invs * bas % mod;
   }
   printf("%s\n%d\n", res + 1, ans);
   return 0;
}