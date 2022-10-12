#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 2e7 + 30;
int p[N >> 3], mu[N], sn, tot;
ll mu1[N], mu2[N];
bool tag[N];
void sieve() {
   mu[1] = 1;
   for(int i = 2; i <= sn; i++) {
      if(!tag[i]) p[++ tot] = i, mu[i] = -1;
      for(int j = 1; j <= tot && i * p[j] <= sn; j++) {
         tag[i * p[j]] = 1;
         if (i % p[j] == 0) break ;
         mu[i * p[j]] = -mu[i];
      }
   }
   for(int i = 1; i <= sn; i ++) {
      mu1[i] = mu1[i - 1] + mu[i];
      mu2[i] = mu2[i - 1] + (mu[i] != 0);
   }
}

ll n, m;
unordered_map<int, int> Map;
ll Mu(int n) {
   if(n <= sn) return mu1[n];
   if(Map.count(n)) return Map[n];
   int res = 1;
   for(int i = 2, j; i <= n; i = j + 1) {
      j = n / (n / i); res -= Mu(n / i) * (j - i + 1);
   }
   Map[n] = res;
   return res;
}
ll Mu2(ll n) {
   if (n <= sn) return mu2[n];
   ll res = 0, i;
   for(i = 1; i * i * i <= n; i ++) {
      res += mu[i] * (n / (i * i));
   }
   ll tmp = Mu(i - 1);
   for(ll j = n / (i * i); j >= 1; j --) {
      res += Mu(sqrt(n / j)) - tmp;
   }
   return res;
}
int main() {
   scanf("%lld%lld", &n, &m);
   if(n > m) swap(n, m);
   sn = min((ll) (pow(m, 3 / 7.0)), n); sieve();
   ll ans = 0, la = 0, cur = 0;
   for(ll l = 1, r; l <= n; l = r + 1) {
      ll a = sqrt(n / l), b = sqrt(m / l);
      r = min(n / (a * a), m / (b * b));
      ans += ((cur = Mu2(r)) - la) * a * b;
      la = cur;
   }
   printf("%lld\n", ans);
   return 0;
}