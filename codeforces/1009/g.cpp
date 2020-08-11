#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 6;
int cnt[N];
vector<int> adj[N];

bool halls(int i, int bm) {
	unordered_set<int> match;
	for (int j = 0; j < N; j++) {
		if (bm & 1<<j) {
			auto it = upper_bound(adj[j].begin(), adj[j].end(), i);
			for (int r = 0; r < N && it != adj[j].end(); r++) {
				match.insert(*it);
				it++;
			}
		}
	}
	return match.size() >= __builtin_popcount(bm);
}

bool valid(int i, int v) {
	if (!cnt[v]) return false;
	--cnt[v];

	int active = 0;
	for (int i = 0; i < N; i++) {
		if (cnt[i]) active |= 1<<i;
	}

	for (int bm = 1; bm < 1<<N; bm++) {
		if ((bm & active) == bm) {
			if (!halls(i, bm)) {
				cnt[v]++;
				return false;
			}
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	string s;

	cin >> s;
	int n = s.size();

	for (char c : s) {
		cnt[c-'a']++;
	}

	int m;
	cin >> m;

	int a;
	vector<pair<int,string>> query;
	for (int i=0; i<m; i++) {
		cin >> a >> s;
		query.push_back(pair<int,string>(a, s));
	}
	query.push_back(pair<int,string>(INF, ""));
	sort(query.begin(), query.end());

	int pos = 0;
	for (int i=1; i<=n; i++) {
		string t = "abcdef";
		if (query[pos].first == i) {
			t = query[pos++].second;
		}
		cerr << i << ": " << t << nl;

		for (char c : t) {
			adj[c-'a'].push_back(i);
		}
	}
	cerr << nl;

	cerr << "ADJ[N] " << nl; for (int i = 0; i < N; i++) {
		cerr << i << ": "; for (int j : adj[i]) cerr << j << " "; 
	cerr << nl; }
	cerr << nl;

	string ans;
	pos = 0;
	for (int i=1; i<=n; i++) {
		string t = "abcdef";
		if (query[pos].first == i) {
			t = query[pos++].second;
		}

		cerr << i << ": " << t << "  answer: " << ans << nl;

		for (char c : t) {
			if (valid(i, c-'a')) {
				ans.push_back(c);
				break;
			}
		}

		if (ans.size() < i) {
			cout << "Impossible" << nl;
			return 0;
		}
	}

	cout << ans << nl;

	return 0;
}
