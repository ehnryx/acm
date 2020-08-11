#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Bishop {
	ll first, second;
	Bishop (ll center = -1, ll radius = -1) {
		first = center - radius;
		second = center + radius;
	}
	bool operator < (const Bishop& other) const {
		if (second != other.second) return second < other.second;
		else return first < other.first;
	}
};

const int MAXN = 2e5;
vector<Bishop> row[MAXN];
vector<Bishop> col[MAXN];
void reset() {
	for (int i = 0; i < MAXN; i++) {
		row[i].clear();
		col[i].clear();
	}
}

int solve(vector<Bishop> arr[]) {
	int res = 0;

	for (int i = 0; i < MAXN; i++) {
		sort(arr[i].begin(), arr[i].end());

		int cur = 0;
		ll pos = -INFLL;
		for (const Bishop& x : arr[i]) {
			if (x.first >= pos) {
				pos = x.second;
				cur++;
			}
		}
		res = max(res, cur);
	}

	return res;
}

int main() {
	freopen("bishops.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		reset();

		ll p;
		int a, b;
		int n, m, c;
		cin >> n >> m >> c;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> p;
			row[a+b-2].push_back(Bishop(2*a, 2*p*p + c - 1));
			col[a-b+n].push_back(Bishop(2*a, 2*p*p + c - 1));
		}
		cout << max(solve(row), solve(col)) << nl;

	}

	return 0;
}
