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

const int S = 124;

struct Query {
	int i, a, b, res;
	Query(int i, int a, int b): i(i), a(a), b(b) {}
	bool operator < (const Query& v) const {
		if (a/S == v.a/S) return (b < v.b)^(a/S%2);
		else return a < v.a;
	}
	bool operator > (const Query& v) const {
		return i < v.i;
	}
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, q, a, b;
	cin >> n >> q;

	vector<int> val(n+1,0);
	for (int i=1; i<=n; i++) {
		cin >> val[i];
	}

	vector<Query> queries;
	for (int i=0; i<q; i++) {
		cin >> a >> b;
		queries.push_back(Query(i,a,b));
	}
	sort(queries.begin(), queries.end());

	unordered_map<int,int> freq;
	vector<int> suf(n+1,0);
	int ans = 0;

	int left, right;
	left = right = 0;
	for (auto& it : queries) {
		for (int i=right; i<=it.b; i++) {
			freq[val[i]]++;
			suf[freq[val[i]]]++;
			if (suf[freq[val[i]]] >= freq[val[i]]) {
				ans = max(ans, freq[val[i]]);
			}
		}
		for (int i=left; i>it.a; i--) {
			freq[val[i-1]]++;
			suf[freq[val[i-1]]]++;
			if (suf[freq[val[i-1]]] >= freq[val[i-1]]) {
				ans = max(ans, freq[val[i-1]]);
			}
		}
		for (int i=right-1; i>it.b; i--) {
			suf[freq[val[i]]]--;
			freq[val[i]]--;
			if (suf[freq[val[i]]+1] < freq[val[i]]+1) {
				ans = min(ans, freq[val[i]]);
			}
		}
		for (int i=left; i<it.a; i++) {
			suf[freq[val[i]]]--;
			freq[val[i]]--;
			if (suf[freq[val[i]]+1] < freq[val[i]]+1) {
				ans = min(ans, freq[val[i]]);
			}
		}
		it.res = ans;
		left = it.a;
		right = it.b+1;
	}

	sort(queries.begin(), queries.end(), greater<Query>());
	for (auto& it : queries) {
		cout << it.res << nl;
	}

	return 0;
}
