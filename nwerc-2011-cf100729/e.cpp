#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 25e3 + 10;
const int K = 128;
int cnt[K];
int lpos[N];
int npos[N];
int n; string s;
void deal() {
	cin >> n >> s;
	memset(lpos, -1, sizeof lpos);
	memset(npos, -1, sizeof npos);
	memset(cnt, 0, sizeof cnt);
	vector<char> rev;
	// lpos
	for (int i = 0; i < n; i++) {
		lpos[s[i]] = i;
	}
	reverse(s.begin(), s.end());
	for (char c : s) {
		if (cnt[c]++ == 0)
			rev.push_back(c);
	}
	string opt;
	for (char c : rev) {
		opt.append(cnt[c], c);
	}
	reverse(opt.begin(), opt.end());
	//cerr << "opt: " << opt << nl;
	for (int i = 0; i < n; i++) {
		npos[opt[i]] = i;
	}
	ll ans = 0;
	for (char c : rev) {
		ll diff = lpos[c] - npos[c];
		assert(diff >= 0);
		ans += cnt[c] * (diff);
	}
	cout << ans*5 << nl;
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) deal();
}

