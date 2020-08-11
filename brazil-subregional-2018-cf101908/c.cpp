#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int N = 2e5+1;
struct BIT {
	int freq[N];
	void init() {
		memset(freq, 0, sizeof freq);
	}
	void insert(int x, int v) {
		for (; x<N; x+=x&-x)
			freq[x]+=v;
	}
	int query(int x) {
		int res = 0;
		for (; x; x-=x&-x)
			res += freq[x];
		return res;
	}
	int query(int lx, int rx) {
		return query(rx)-query(lx-1);
	}
};
BIT bit;

vector<pii> match;
map<int,int> cmpr;
map<int,int> dcmp;
set<int> seen;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int x, y;
	cin >> x >> y;

	int n, m;
	cin >> n >> m;

	ll ans = 1;
	int a, b, t;

	bit.init();
	for (int i=0; i<n; i++) {
		cin >> a >> b;
		match.push_back(pii(a,b));
		seen.insert(b);
	}
	t = 0;
	for (int it : seen) {
		cmpr[it] = ++t;
		dcmp[t] = it;
	}

	sort(match.begin(), match.end());
	for (int i=0; i<n; i++) {
		ans += 1 + bit.query(cmpr[match[i].second], n);
		bit.insert(cmpr[match[i].second], 1);
	}

	seen.clear();
	match.clear();
	cmpr.clear();
	dcmp.clear();
	bit.init();
	for (int i=0; i<m; i++) {
		cin >> a >> b;
		match.push_back(pii(a,b));
		seen.insert(b);
	}
	t = 0;
	for (int it : seen) {
		cmpr[it] = ++t;
		dcmp[t] = it;
	}

	sort(match.begin(), match.end());
	for (int i=0; i<m; i++) {
		ans += n + 1 + bit.query(cmpr[match[i].second], m);
		bit.insert(cmpr[match[i].second], 1);
	}

	cout << ans << nl;

	return 0;
}
