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
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	ll len[3], wid[3];
	memset(len, 0, sizeof len);
	memset(wid, 0, sizeof wid);

	ll a[n], b[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		len[i%3] += a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
		wid[i%3] += b[i];
	}

	ll ans[3];
	memset(ans, 0, sizeof ans);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ans[(i+j)%3] += len[i]*wid[j];
		}
	}

	for (int i = 1; i <= 3; i++) {
		cout << ans[i%3] << " ";
	} cout << nl;

	return 0;
}
