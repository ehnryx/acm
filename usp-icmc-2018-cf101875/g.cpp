#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Car {
	ld s;
	int v;
	bool operator < (const Car& o) const {
		return s < o.s;
	}
};

struct Node {
	int i, j;
	ld t;
	bool operator < (const Node& o) const {
		return t > o.t;
	}
};

ld collide(const Car& a, const Car& b) {
	ld d = b.s - a.s;
	return d / (a.v - b.v);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	map<int,Car> car;
	for (int i=0; i<n; i++) {
		int s, v;
		cin >> s >> v;
		car[s] = { (ld)s, v };
	}

	priority_queue<Node> dijk;
	for (auto it=car.begin(); next(it)!=car.end(); it++) {
		auto jt = next(it);
		if (it->second.v > jt->second.v) {
			dijk.push({ it->first, jt->first, collide(it->second, jt->second) });
			//cerr << "init " << it->first << " " << jt->first << " at " << collide(it->second, jt->second) << nl;
		}
	}

	ld ans = 0;
	while (!dijk.empty()) {
		Node cur = dijk.top();
		dijk.pop();
		//cerr << "try colliding " << cur.i << " " << cur.j << nl;
		if (car.count(cur.i) && car.count(cur.j)) {
			ans = cur.t;
			//cerr << "collided at " << cur.t << nl;
			car.erase(cur.i);
			auto jt = car.find(cur.j);
			if (jt != car.begin()) {
				auto it = prev(jt);
				if (it->second.v > jt->second.v) {
					dijk.push({ it->first, jt->first, collide(it->second, jt->second) });
					//cerr << "push " << it->first << " " << jt->first << " at " << collide(it->second, jt->second) << nl;
				}
			}
		}
	}
	cout << ans << nl;

	return 0;
}
