#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; 
	return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T, N, M;
	cin >> T >> N >> M;
	for (int cc = 1; cc <= T; cc++) {
		//cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
}
bool chin_rem(ll a1, ll m1, ll a2, ll m2, ll& A, ll& M) {
  ll X1, X2, d = egcd(m1, m2, X1, X2); if (a1 % d != a2 % d) return false;
  M = m1/d*m2, A = ((X1*(a2/d)%m2*m1 + X2*(a1/d)%m1*m2 + a1%d)%M + M)%M;
  return true;
}

vector<int> query = { 5, 7, 11, 13, 17, 18 };

void caseinit() {
}

void solve() {
	caseinit();

	ll a = 0;
	ll m = 1;
	for (int it : query) {
		for (int i=0; i<18; i++) {
			cout << it << " ";
		}
		cout << endl;

		int res = 0;
		for (int i=0; i<18; i++) {
			int v;
			cin >> v;
			if (v == -1) exit(1);
			res += v;
		}
		assert(chin_rem(a, m, res%it, it, a, m));
	}
	//cerr << "MOD: " << m << nl;
	cout << (a%m+m)%m << endl;

	int verdict;
	cin >> verdict;
	if (verdict == -1) exit(1);

	return;
}

