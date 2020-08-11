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
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
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

struct Cactus {
	int h, a;
	ll atk;
	Cactus() {}
	Cactus(int h, int a, int bossatk): h(h), a(a) {
		atk = a * (1 + (h-1)/bossatk);
	}

	operator ll() { return atk; }
	bool operator < (const Cactus& other) const {
		return atk > other.atk;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		int n;
		ll hp, atk;
		cin >> n >> hp >> atk;

		int h, a;
		vector<Cactus> eyqs;
		for (int i = 0; i < n; i++) {
			cin >> h >> a;
			eyqs.push_back(Cactus(h, a, atk));
		}
		sort(eyqs.begin(), eyqs.end());

		int ans = -1;
		for (int i = 0; i < n; i++) {
			hp -= eyqs[i];
			if (hp <= 0) {
				ans = i;
				break;
			}
		}
		cout << ans << nl;
	}

	return 0;
}
