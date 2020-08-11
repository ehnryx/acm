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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	ll s;
	cin >> n >> s;

	unordered_map<ll,int> cnt;
	ll sum = 0;

	int a;
	vector<ll> pref;
	cnt[0]++;
	for (int i=0; i<n; i++) {
		cin >> a;
		pref.push_back(sum);
		sum += a;
		cnt[sum]++;
	}

	ll ans = 0;
	for (const ll& start : pref) {
		cnt[start]--;
		ans += cnt[start+s];
	}
	cout << ans << nl;

	return 0;
}
