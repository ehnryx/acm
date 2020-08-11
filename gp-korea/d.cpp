#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;

const char nl = '\n';

const int N = 1001000;
const int INF = 0x3f3f3f3f;

char s[N];
int f[N][26];
int lst[N];
int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> (s+1);
	n = strlen(s+1);

	for (int j=0; j<26; ++j) {
		lst[j] = INF;
	}

	for (int i=n; i>=0; --i) {
		for (int j=0; j<26; ++j) {
			f[i][j] = lst[j];
		}
		if (i) {
			lst[s[i]-'a'] = i;
		}
	}

	int ans = 0;

	int p = 1;
	while (p<=n) {
		int j = p;
		int i = f[0][s[j]-'a'];
		int amt = 0;
		while (i < p && j<=n) {
			++ amt;
			++ j;
			if (j<=n) {
				i = f[i][s[j]-'a'];
			}
		}
		++ans;
		p += max(amt, 1);
	}
	
	cout << ans << endl;


	return 0;
}
