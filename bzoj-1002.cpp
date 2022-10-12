#include <algorithm>
#include <cstdio>
using namespace std;
const int base = 1e8, N = 105;
int n;
struct Node {
	int n, a[102];
	void operator = (const int &x) {
		a[0] = x; n = 1;
	}
	Node operator + (const int &x) { //x < 10
		Node ans; ans.n = n + 1;
		for(int i = 0; i < n; i ++) ans.a[i] = a[i];
		ans.a[0] += x;
		for(int i = 0; i < n; i ++) {
			ans.a[i + 1] += ans.a[i] / base;
			ans.a[i] %= base;
		}
		while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
		return ans;
	}
	Node operator * (const int &x) { //x < 10
		Node ans; ans.n = n + 1; ans.a[0] = 0;
		for(int i = 0; i < n; i ++) {
			ans.a[i] += a[i] * x;
			ans.a[i + 1] = ans.a[i] / base;
			ans.a[i] %= base;
		}
		while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
		return ans;
	}
	Node operator - (Node b) {
		Node ans; ans.n = n;
		for(int i = n - 1; ~ i; i --) ans.a[i] = 0;
		for(int i = 0; i < n; i ++) {
			ans.a[i] += a[i] - (i < b.n ? b.a[i] : 0);
			if(ans.a[i] < 0) ans.a[i + 1] --, ans.a[i] += base;
		}
		while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
		return ans;
	}
	void out() {
		printf("%d", a[n - 1]);
		for(int i = n - 2; i >= 0; i --)
			printf("%08d", a[i]);
		puts("");
	}
} a[N];
int main() {
	scanf("%d", &n);
	a[1] = 1; a[2] = 5;
	for(int i = 3; i <= n; i ++)
		a[i] = a[i - 1] * 3 - a[i - 2] + 2;
	a[n].out();
	return 0;
}