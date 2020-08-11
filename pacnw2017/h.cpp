#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//typedef long long ll;
//typedef __int128 ll;
typedef long double ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
// will maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    // could overflow
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void insert_line(ll m, ll b) { m = -m; b = -b; // for lower hull
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ll eval(ll x) {
    if (empty()) return INFLL;
    auto l = *lower_bound((Line) { x, is_query });
    return -(l.m * x + l.b); // for lower hull
  }
};

struct Flight {
	int id, other;
	int time, other_t;
	bool dest;
	Flight(int i, int t, int o, int ot, bool d):
		id(i), time(t), other(o), other_t(ot), dest(d) {}
	bool operator < (const Flight& other) const {
		if (time == other.time) return !dest;
		else return time < other.time;
	}
};

inline ll sqr(ll x) { return x*x; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(0);

	int a, b, s, e;
	vector<Flight> f;

	int n, m;
	cin >> n >> m;

	map<int,ll> value[n+1];
	HullDynamic hulls[n+1];
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> s >> e;
		if (a == b && s == e)
			continue;
		f.push_back(Flight(a,s,b,e,false));
		f.push_back(Flight(b,e,a,s,true));
	}
	sort(f.begin(), f.end());

	value[1][0] = 0;
	hulls[1].insert_line(0, 0);
	ll ans = INFLL;
	m = f.size();
	for (int i = 0; i < m; i++) {
		if (f[i].dest) {
			assert(value[f[i].other].count(f[i].other_t));
			if (f[i].id == n) {
				ans = min(ans, value[f[i].other][f[i].other_t]);
			} else {
				hulls[f[i].id].insert_line(-2*f[i].time, value[f[i].other][f[i].other_t] + sqr(f[i].time));
			}
		} 
		else {
			value[f[i].id][f[i].time] = sqr(f[i].time) + hulls[f[i].id].eval(f[i].time);
		}
	}

	//cout << (long long) ans << nl;
	cout << ans << nl;

	return 0;
}
