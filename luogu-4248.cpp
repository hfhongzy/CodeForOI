#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define per(i, a, b) for (int i = a, i##end = b; i >= i##end; --i)
#define rep0(i, a) for (int i = 0, i##end = a; i < i##end; ++i)
#define per0(i, a) for (int i = a-1; ~i; --i)
#define chkmin(a, b) a = std::min(a, b)
#define chkmax(a, b) a = std::max(a, b)
#define x first
#define y second

typedef long long ll;

const int maxn = 555555;

char s[maxn];
int sa[maxn], ht[maxn], rk[maxn];

void build_sa(char *s, int *sa) {
    static int t[maxn << 1], t2[maxn << 1], c[maxn], *x = t, *y = t2, n, m;
    n = strlen(s), m = 'z'+1;
    rep0(i, m) c[i] = 0;
    rep0(i, n) c[x[i] = s[i]]++;
    rep(i, 1, m) c[i] += c[i-1];
    per0(i, n) sa[--c[x[i]]] = i;
    for (int k = 1; k < n; k <<= 1) {
        int p = 0;
        rep(i, n-k, n-1) y[p++] = i;
        rep0(i, n) if (sa[i] >= k) y[p++] = sa[i]-k;
        rep0(i, m) c[i] = 0;
        rep0(i, n) c[x[y[i]]]++;
        rep(i, 1, m) c[i] += c[i-1];
        per0(i, n) sa[--c[x[y[i]]]] = y[i];
        std::swap(x, y);
        p = 1; x[sa[0]] = 0;
        rep(i, 1, n-1) x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
        if ((m = p) == n) return;
    }
}

void get_ht(char *s, int *sa, int *ht) {
    static int rk[maxn], j; j = 0;
    rep0(i, strlen(s)) rk[sa[i]] = i;
    rep0(i, strlen(s)) {
        j && j--;
        if (rk[i]) while (s[i+j] == s[sa[rk[i]-1]+j]) j++;
        ht[rk[i]] = j;
    }
}

int main() {
    scanf("%s", s);
    build_sa(s, sa);
    get_ht(s, sa, ht);
    ll ans = 0, now = 0; int st[maxn], top = 0, n = strlen(s);
    rep0(i, n) {
        while (top && ht[i] <= ht[st[top]]) now -= 1ll*(st[top]-st[top-1])*ht[st[top]], top--;
        now += 1ll*(i-st[top])*ht[i]; st[++top] = i;
        ans += 1ll*(n-1)*(i+1) - 2*now;
    }
    printf("%lld", ans);
    return 0;
}