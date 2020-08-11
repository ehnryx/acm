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

const int N = 1e5;

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int k;
	cin >> k;

	map<ll,int> vals;
	for (int i = 0; i <= N; i++) {
		vals[(ll)i*(i+1)/2 + i/2 + i/2 + 2] = i;
	}

	int r = 0;
	vector<char> ans;
	int cur = 0;
	while (k > 1) {
		auto it = prev(vals.upper_bound(k));
		k -= it->first;
		ans.push_back(cur+'b');
		cur = (cur+1)%25;
		for (int i = 0; i < it->second; i++) {
			ans.push_back('a');
		}
		ans.push_back(cur+'b');
		cur = (cur+1)%25;
		r++;
	}
	if (k == 1) {
		ans.push_back(cur+'b');
	}
	cerr << r << " rounds " << nl;

	cerr << "length: " << ans.size() << nl;
	assert(ans.size() <= N);
	for (char c : ans) {
		cout << c;
	}
	cout << nl;

	return 0;
}
