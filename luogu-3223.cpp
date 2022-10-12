// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;

int n, m;

typedef long long LL;

const int BASE = 1e8, MAXLEN = 10330;
char s[MAXLEN<<3];

struct num {
  int len; LL bt[MAXLEN];
  void upzero() {while(!bt[len] && len!=1) --len;}
  void upbit() {
    LL x(0);
    for (int i = 1; i <= len; i++) {
      if(bt[i] < 0) {bt[i] += BASE; --bt[i+1];}
      bt[i] += x; x = bt[i]/BASE; bt[i] %= BASE;
    }
    while(x) bt[++len] = x % BASE,x /= BASE;
  }
  // LL to_long(){return len<3?bt[2]*BASE+bt[1]:-1;}
  num(LL num) : len(1) { memset(bt,0,sizeof bt); bt[1] = num; upbit(); }
  num() : len(1) { memset(bt,0,sizeof bt); }
  void operator = (LL x) { len = 1; memset(bt, 0, sizeof bt); bt[1] = x; upbit(); }
  void out() {
    printf("%lld", bt[len]);
    for(int i = len - 1; i; i --)
      printf("%08lld", bt[i]);
    printf("\n");
  }
   
  num operator * (const num &b) const {
    num ans(0ll);
    ans.len = len+b.len-1;
    for(int i = 1; i <= len; i ++)
      for(int j = 1; j <= b.len; j ++) {
        ans.bt[i + j - 1] += bt[i] * b.bt[j];
      ans.bt[i + j] += ans.bt[i + j - 1] / BASE;
      ans.bt[i + j - 1] %= BASE;
    }
    if(ans.bt[ans.len+1]) ++ans.len;
    return ans;
  }

  num operator - (const num &b) const {
    num ans(*this); ans.len = len;
    for (int i = 1; i <= b.len; i++)
     ans.bt[i] = bt[i] - b.bt[i];
    ans.upbit(); ans.upzero();
    return ans;
  }
  num operator + (const num &b) const {
    num ans(0ll); ans.len = max(len, b.len);
    for (int i = 1; i <= ans.len; i++)
      ans.bt[i] = bt[i] + b.bt[i];
    ans.upbit();
    return ans;
  }
} now, ans1, ans2, ans3, tmp;

int main() {
    scanf("%d%d", &n, &m);
    if(n + 3 - m < 0) return puts("0"), 0;
    now = tmp = num(1);
    for(int i = 2; i <= n + 1; i ++)
        now = now * num(i);
    for(int i = n + 2; i > n + 3 - m; i --)
        tmp = tmp * num(i);
    // now.print();
    ans1 = now * num(n + 2) * num(n + 3) * tmp;
    ans2 = num(2) * num(m) * now * tmp;
    ans3 = num(2) * now * num(n + 3) * tmp;
    // ans1.print(); ans2.print(); ans3.print();
    ans1 = ans1 + ans2 - ans3;
    ans1.out();
    return 0;
}
/*
( (n + 2)! - 2 * (n + 1)! ) * C(n + 3, m) * m!
这是老师由Boy隔开
2 * (n + 1)! * C(n + 2, m - 1) * m!
这是老师由Girl隔开
1/f[n-m+3]
f[n+2]f[n+3] + 2f[n + 1]f[n+2]m - 2f[n+1]f[n+3]
*/