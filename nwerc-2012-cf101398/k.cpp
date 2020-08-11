#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const char nl = '\n';

ostream& operator << (ostream& os, const set<int>& v) {
	os << "{ ";
	for (int i : v) os << i << " "; return os << "}";
}

const int N = 101;
set<int> possible[N];
set<int> ans[N];
ll fact[N];

void init(int sz, int k) {
	for (int i = 0; i < k; i++) {
		ans[i].clear();
		for (int j = 0; j < k; j++) {
			ans[i].insert(j);
		}
	}
}

void precmp() {
	fact[0] = 1;
	for (int i = 1; i <= 100; i++) {
		fact[i] = i*fact[i-1];
	}
}

ll power(ll b, int e) {
	ll res = 1;
	while (e > 0) {
		if (e & 1) res *= b;
		b *= b;
		e /= 2;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	precmp();

	int k;
	while (cin >> k) {
		string s, t;
		cin >> s;
		cin >> t;
		init(s.size(), k);

		for (int p = 0; p < s.size()/k; p++) {
			for (int i = 0; i < k; i++) {
				possible[i].clear();
			}
			for (int i = 0; i < k; i++) {
				for (int j = 0; j < k; j++) {
					if (s[p*k+i] == t[p*k+j]) {
						possible[i].insert(j);
					}
				}
			}

			for (int j = 0; j < k; j++) {
				vector<int> bad;
				for (int i : ans[j]) {
					if (!possible[j].count(i)) bad.push_back(i);
				}
				for (int i : bad) ans[j].erase(i);
			}
		}

		set<int> seen;
		unordered_map<int,int> cnt;
		unordered_map<int,int> sz;
		bool bad = false;
		for (int i = 0; i < k; i++) {
			if (ans[i].empty()) {
				bad = true;
				break;
			} else {
				cnt[*ans[i].begin()]++;
				sz[*ans[i].begin()] = ans[i].size();
			}
			for (int j : ans[i]) {
				seen.insert(j);
			}
		}
		if (bad || seen.size() != k) {
			cout << 0 << nl;
			continue;
		}

		ll res = 1;
		for (const pii& it : cnt) {
			if (it.second != sz[it.first]) {
				bad = true;
				break;
			} else {
				res *= fact[sz[it.first]];
			}
		}
		if (bad) res = 0;

		cout << res << endl;
	}

	return 0;
}
