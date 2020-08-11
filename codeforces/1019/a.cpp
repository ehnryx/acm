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

const int N = 3000+1;
set<int> vote[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		vote[a].insert(b);
	}

	auto solve = [&] (int guess) {
		int total = vote[1].size();
		ll res = 0;

		priority_queue<int, vector<int>, greater<int>> leftover;
		for (int i = 2; i <= m; i++) {
			int cnt = vote[i].size();
			for (int it : vote[i]) {
				if (cnt < guess) {
					leftover.push(it);
				}
				else {
					res += it;
					total++;
					cnt--;
				}
			}
		}

		while (total < guess && !leftover.empty()) {
			res += leftover.top();
			leftover.pop();
			total++;
		}

		return total < guess ? INFLL : res;
	};

	ll ans = INFLL;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, solve(i));
	}
	cout << ans << nl;

	return 0;
}
