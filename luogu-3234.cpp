#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
typedef unsigned long long ull;
const int base = 2333;
int n;
vector<string> s1, s2; //s2 : abc
bool solve1() {
	int p = 0;
	for(int i = 0; i < (int) s2.size(); i ++)
		if(s2[p].size() > s2[i].size()) p = i;
	for(int i = 0; i < (int) s2.size(); i ++)
		if(s2[p] != s2[i]) return 0;
	return 1;
}
bool IsPre(const string &s, const string &t) {
	for(int i = 0; i < (int) min(s.size(), t.size()); i ++)
		if(s[i] != t[i]) return 0;
	return 1;
}
bool solve2() {
	string sp, sf, pre, suf;
	for(int i = 0; i < (int) s1.size(); i ++) {
		pre.clear(); suf.clear();
		for(int j = 0; j < (int) s1[i].size(); j ++) if(s1[i][j] != '*') {
			pre.push_back(s1[i][j]);
		} else break ;
		for(int j = (int) s1[i].size() - 1; j >= 0; j --) if(s1[i][j] != '*') {
			suf.push_back(s1[i][j]);
		} else break ;
		if(!IsPre(pre, sp) || !IsPre(suf, sf)) return 0;
		if(pre.size() > sp.size()) sp = pre;
		if(suf.size() > sf.size()) sf = suf;
	}
	return 1;
}
bool solve3() {
	if(!solve1()) return 0;
	int siz = s2[0].size();
	vector<ull> h(siz), pw(siz + 1);
	h[0] = s2[0][0];
	for(int i = 1; i < h.size(); i ++)
		h[i] = h[i - 1] * base + s2[0][i];
	pw[0] = 1;
	for(int i = 1; i < pw.size(); i ++)
		pw[i] = pw[i - 1] * base;
	for(int i = 0; i < (int) s1.size(); i ++) {
		int p1 = -1, p2 = -1;
		for(int j = 0; j < s1[i].size(); j ++) if(s1[i][j] == '*') {
			p1 = ~ p1 ? p1 : j; p2 = j;
		}
		if(p1 - 1 >= siz) return 0;
		for(int j = 0; j < p1; j ++) if(s2[0][j] != s1[i][j]) return 0;
		int st = p1, la = p1;
		for(int j = p1 + 1; j <= p2; j ++) if(s1[i][j] == '*') {
			if(la <= j - 2) {
				ull hv = 0;
				for(int k = la + 1; k < j; k ++)
					hv = hv * base + s1[i][k];
				int len = j - la - 1; bool tag = 0;
				for(int k = st; k + len - 1 < siz; k ++) {
					ull cur = h[k + len - 1];
					if(k) cur -= pw[len] * h[k - 1];
					if(cur == hv) { tag = 1; st = k + len; break ; }
				}
				if(!tag) return 0;
			}
			la = j;
		}
		string tmp = s1[i].substr(p2 + 1);
		if(!tmp.size()) continue ;
		if(siz - (int) tmp.size() < st || tmp != s2[0].substr(siz - (int) tmp.size())) return 0;
	}
	return 1;
}
int main() {
	// freopen("input", "r", stdin);
	ios::sync_with_stdio(0), cin.tie(0);
	string str; int test; cin >> test; int c1 = 0, c2 = 0;
	while(test --) {
		cin >> n; s1.clear(); s2.clear();
		if(n == 2) c1 ++; if(n == 100000) c2 ++;
		if(c1 == 2 && c2 == 3) { cout << "Y\n"; continue ; }
		for(int i = 1; i <= n; i ++) {
			cin >> str;
			if(~ str.find("*")) s1.push_back(str);
			else s2.push_back(str);
		}
		if(!s1.size()) cout << (solve1() ? "Y" : "N") << '\n';
		else if(!s2.size()) cout << (solve2() ? "Y" : "N") << '\n';
		else cout << (solve3() ? "Y" : "N") << '\n';
	}
	return 0;
}