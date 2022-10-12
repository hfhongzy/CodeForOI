 
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;
 
const int N = 100010;
const int M = 7000010;
 
int n, m, q, u, v, t;
int l[M], cutl[M], cnt;
double p;
 
queue<int> h, h1, h2;
 
void get_max(int &Now) {
    int _a = h.empty() ? -2e9 : h.front();
    int _b = h1.empty() ? -2e9 : h1.front();
    int _c = h2.empty() ? -2e9 : h2.front();
    if(_a >= _b && _a >= _c) { Now = _a; h.pop(); }
    else if(_b >= _a && _b >= _c) { Now = _b; h1.pop(); }
    else if(_c >= _a && _c >= _b) { Now = _c; h2.pop(); }
}
 
int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    p = u / (double) v;
    for(int i = 1; i <= n; i ++)
        scanf("%d", l + i);
    sort(l + 1, l + n + 1, greater<int>());
    for(int i = 1; i <= n; i ++) h.push(l[i]);
    int data = 0, Now, _a, _b, _c, l_len, r_len;
    for(int i = 1; i <= m; i ++) {
        get_max(Now);
        cutl[i] = Now + data;
        l_len = cutl[i] * p;
        r_len = cutl[i] - l_len;
        h1.push(l_len - i * q);
        h2.push(r_len - i * q);
        data += q;
    }
    for(int i = t; i <= m; i += t)
        printf("%d ", cutl[i]);
    printf("\n");
    cnt = h.size() + h1.size() + h2.size();
    for(int i = 1; i <= cnt; i ++) {
        get_max(Now);
        if(i % t == 0) printf("%d ", Now + data);
    }
    printf("\n");
    return 0;
}