#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

int get_num(int x, int cut) {
	int cnt = 0;
	for (int i=1; i<=x+1; i++) {
		int r = (cut+i-1)/i;
		cnt += r;
	}
	return cnt;
}

ll get_sum(int n, int x, int cut) {
	ll sum = 0;
	int top = 0;
	int cnt = 0;
	for (int i=1; i<=x+1; i++) {
		ll r = (cut+i-1)/i;
		cnt += r;
		if ((cut-1)%i == 0) top++;
		sum += r*(r*i-(i-2))/2;
	}
	return sum - (ll)min(top, cnt-n)*cut;
}

ll solve(int n, int t, int x, int& cutoff) {
	int left = 1;
	int right = n;
	while (left < right) {
		int mid = (left+right)/2;
		if (get_num(x, mid) < n) {
			left = mid+1;
		} else {
			right = mid;
		}
	}
	cutoff = left;
	return get_sum(n, x, left) + (ll)x*t;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, t;
	cin >> n >> t;
	
	int left = 0;
	int right = n-1;
	int cutoff = 0;
	while (left < right) {
		int mid = (left+right)/2;
		ll lval = solve(n, t, mid, cutoff);
		ll rval = solve(n, t, mid+1, cutoff);
		if (lval > rval) {
			left = mid+1;
		} else {
			right = mid;
		}
	}

	cout << solve(n, t, left, cutoff) << nl;
	cout << left << nl;
	cerr << "chocolates: " << left << nl;

	vector<pii> lasts;
	for (int i=1; i<=left; i++) {
		int r = (cutoff+i-1)/i;
		lasts.push_back(pii(1+(r-1)*i, i));
	}
	sort(lasts.begin(), lasts.end(), greater<pii>());

	int cnt = get_num(left, cutoff);
	assert(cnt-n <= left);
	set<int> remove;
	for (int i=0; i<cnt-n; i++) {
		remove.insert(lasts[i].second);
	}

	int id = 0;
	for (int i=1; i<=left; i++) {
		int r = (cutoff+i-1)/i;
		if (remove.count(i)) {
			id += r-1;
		} else {
			id += r;
		}
		cout << id << " ";
	}
	cout << nl;

	return 0;
}
