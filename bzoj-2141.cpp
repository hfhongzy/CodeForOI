#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
namespace IO {

static char buf[1 << 15], * S = buf, * T = buf;
char gc() {
   if(S == T) {
      T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
      if(S == T) return EOF;
   }
   return * S ++;
}
int read() {
   int x = 0; char c = gc();
   for(; c < '0' || c > '9'; c = gc());
   for(; c >= '0' && c <= '9'; c = gc())
      x = x * 10 + (c & 15);
   return x;
}

}
using IO :: read;
const int N = 2e4 + 10;
const int M = 820;
int n, m, sz, a[N], b[N];
vector<int> vec[M];
int solve(int *a, int n) {
	vector< pair<int, int> > seq(n);
	vector<int> bit(n, 0);
	for(int i = 1; i <= n; i ++) seq[i - 1] = make_pair(a[i], i);
	sort(seq.begin(), seq.end());
	int ans = 0;
	for(int i = n - 1; i >= 0; i --) {
		int x = seq[i].second;
		for(int j = x; j >= 1; j &= j - 1) ans += bit[j - 1];
		for(int j = x; j <= n; j += j & (-j)) bit[j - 1] ++;
	}
	return ans;
}
int query0(int l, int r, int x) { // < 
	int ans = 0;
	if(b[l] == b[r]) {
		for(int i = l; i <= r; i ++) ans += a[i] < x;
	} else {
		for(int i = l; i <= min(sz * b[l], n); i ++) ans += a[i] < x;
		for(int i = sz * (b[r] - 1) + 1; i <= r; i ++) ans += a[i] < x;
		for(int i = b[l] + 1; i < b[r]; i ++) {
			ans += lower_bound(vec[i].begin(), vec[i].end(), x) - vec[i].begin();
		}
	}
	return ans;
}
int query1(int l, int r, int x) { // >
	int ans = 0;
	if(b[l] == b[r]) {
		for(int i = l; i <= r; i ++) ans += a[i] > x;
	} else {
		for(int i = l; i <= min(sz * b[l], n); i ++) ans += a[i] > x;
		for(int i = sz * (b[r] - 1) + 1; i <= r; i ++) ans += a[i] > x;
		for(int i = b[l] + 1; i < b[r]; i ++) {
			ans += vec[i].end() - upper_bound(vec[i].begin(), vec[i].end(), x);
		}
	}
	return ans;
}
void modify(int l, int p, int v) {
	int sz = (int) vec[l].size();
	for(int i = 0; i < sz; i ++) {
		if(vec[l][i] == p) {
			vec[l][i] = v;
			while(i >= 1 && vec[l][i] < vec[l][i - 1]) swap(vec[l][i], vec[l][i - 1]), i --;
			while(i < sz - 1 && vec[l][i] > vec[l][i + 1]) swap(vec[l][i], vec[l][i + 1]), i ++;
			break ;
		}
	}
}
int main() {
//	freopen("input", "r", stdin);
	n = read(); sz = max(2, (int) sqrt(n * 10));
	for(int i = 1; i <= n; i ++) {
		b[i] = (i - 1) / sz + 1;
		vec[b[i]].push_back(a[i] = read());
	}
	m = read();
	for(int i = 1; i <= b[n]; i ++) {
		sort(vec[i].begin(), vec[i].end());
	}
	int ans = solve(a, n);
	printf("%d\n", ans);
	for(int x, y, i = 1; i <= m; i ++) {
		x = read(); y = read();
		if(x > y) swap(x, y);
		if(a[x] != a[y]) {
			ans += a[x] > a[y] ? -1 : 1;
			if(x + 1 < y) {
				ans += query0(x + 1, y - 1, a[y]);
				ans -= query1(x + 1, y - 1, a[y]);
				ans -= query0(x + 1, y - 1, a[x]);
				ans += query1(x + 1, y - 1, a[x]);
			}
			modify(b[x], a[x], a[y]);
			modify(b[y], a[y], a[x]);
			swap(a[x], a[y]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
/*
- [ > a[j] ] + [ < a[j] ]
- [ < a[i] ] + [ > a[i] ]
modify : O(sz)
query : O(n / sz * log)
sz = sqrt(n * 10)
*/