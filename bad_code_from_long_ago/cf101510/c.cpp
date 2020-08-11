#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

bool valid(int n, int a[], int len, int k) {
	int good = -1;
	for (int i = 0; i < n; i++) {
		int cur = upper_bound(a, a+n, a[i]+len) - (a+i);
		if (cur < k && good < i) return false;
		else if (cur >= k) good = i+cur-1;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, k;
	cin >> n >> k;

	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);

	ll left, right, ans;
	left = 0; right = 2e9+1;
	while (left <= right) {
		ans = (left + right) / 2;
		if (valid(n, a, ans, k))
			right = ans-1;
		else
			left = ans+1;
	}
	if (!valid(n, a, ans, k)) {
		ans++;
	}
	cout << ans << nl;

	return 0;
}
