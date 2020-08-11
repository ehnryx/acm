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
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

struct Range {
	int l, r;
	int cost;
	Range(int l, int r, int c): l(l), r(r), cost(c) {}
	bool operator < (const Range& other) const {
		return l < other.l;
	}
	bool operator == (const Range& other) const {
		return l == other.l;
	}

	bool rightof(int x) const {
		return r >= x;
	}
	bool leftof(int x) const {
		return l <= x;
	}
	int length() const {
		return r-l+1;
	}
	ll value() const {
		return (ll) cost * length();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	//cin >> T;
	read(T);
	while (T--) {
		int n, k;
		//cin >> n >> k;
		read(n); read(k);

		int a, b, c;
		vector<int> p;
		vector<Range> segs;
		for (int i=0; i<n; i++) {
			//cin >> a >> b >> c;
			read(a); read(b); read(c);
			p.push_back(a);
			p.push_back(b-k+1);
			segs.push_back(Range(a,b,c));
		}
		segs.push_back(Range(2*INF,2*INF,0));
		sort(p.begin(), p.end());
		sort(segs.begin(), segs.end());

		ll ans = 0;
		ll cur = 0;

		auto update = [&] (const Range& seg, int dir) {
			cur += dir * seg.value();
		};

		auto solve = [&] (int x, const Range& left, const Range& right) {
			ll res = 0;
			if (left.leftof(x)) {
				res -= (ll) left.cost * (x - left.l);
			}
			if (right.leftof(x+k-1)) {
				res += (ll) right.cost * (x+k - right.l);
			}
			return res;
		};

		int left, right;
		left = right = 0;
		for (int it : p) {
			while (!segs[left].rightof(it)) {
				update(segs[left], -1);
				left++;
			}
			while (!segs[right].rightof(it+k-1)) {
				update(segs[right], 1);
				right++;
			}

			ans = max(ans, cur + solve(it, segs[left], segs[right]));
		}

		cout << ans << nl;
	}

	return 0;
}
