#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;

const char nl = '\n';

const int N  = 1001000;

char s[N];
int f[N][26];
int n;
int lst[26];

bool check(int beg, int fin, int k) { // suffix [beg, fin)
	cerr << "CHECK " << beg << " " << fin << " " << k << endl;
	assert (beg >= 1);
	if (beg < 1) return false;
	int j = fin-1;
	int i = beg;
	while (j >= beg && i) {
		i = f[i][s[j]-'a'];
		--j;
	}
	//cerr << "CHECK " << beg << " " << fin << " : " << i << endl;
	return i!=0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> (s+1);
	n = strlen(s+1);

	for (int i=1; i<=n; ++i) {
		for (int j=0; j<26; ++j) {
			f[i][j] = lst[j];
		}
		lst[s[i]-'a'] = i;
	}

	int ans = 0;
	int p = n;
	while (p > 0) {
		//cerr << " P " << p << endl;
		int lo = 0, hi = 1;
		while (check(p-hi+1, p+1, hi)) {
			lo = hi;
			hi *= 2;
		}
		--hi;
		while (lo < hi) {
			int m = (lo+hi+1)/2;
			if (check(p-m+1, p+1, m)) {
				lo = m;
			} else {
				hi = m-1;
			}
		}
		++ans;
		if (hi == 0) {
			p -= 1;
		} else {
			p -= hi;
		}
	}

	cout << ans << endl;

	return 0;
}
