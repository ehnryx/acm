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

const int N = 1e5+1;
struct BIT {
	int freq[N];
	BIT() { memset(freq, 0, sizeof freq); }
	void insert(int x, int cnt=1) {
		for ( ; x < N; x += x&-x) 
			freq[x] += cnt;
	}
	int query(int x) {
		int res = 0;
		for ( ; x > 0; x -= x&-x)
			res += freq[x];
		return res;
	}
	int query(int xl, int xr) {
		return query(xr) - query(xl-1);
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

	int n;
	cin >> n;

	map<int,vector<int>> index;
	BIT bit;
	int a;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		bit.insert(i);
		index[a].push_back(i);
	}

	pii part[N];
	for (const pair<int,vector<int>>& it : index) {
		for (int i : it.second) {
			part[i].second = n-i - bit.query(i+1,n);
		}
		for (int i : it.second) {
			bit.insert(i, -1);
		}
		for (int i : it.second) {
			part[i].first = bit.query(1,i-1);
		}
	}

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (ll) part[i].first * part[i].second;
	}
	cout << ans << nl;

	return 0;
}
