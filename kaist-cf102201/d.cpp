#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Rectangle {
	int a, b, c, d;
	void transpose() {
		swap(a,b);
		swap(c,d);
	}
};

struct Solver {
	struct Segment {
		int x, a, b, t;
		bool operator < (const Segment& o) const {
			return x < o.x;
		}
	};

	ll ans = INFLL;
	Solver(const vector<Rectangle>& rect, int sx, int sy, int tx, int ty) {
		vector<Segment> p;
		for(auto [a, b, c, d] : rect) {
			p.push_back({a, b, d, 1});
			p.push_back({c, b, d, 0});
		}
		p.push_back({sx, sy, sy, 1});
		p.push_back({tx, ty, ty, 1});
		sort(p.begin(), p.end());

		map<int,ll> dist;
		bool seen = false;
		for(auto [x, a, b, add] : p) {
			if(add) {
				bool first = false;
				if(a == b && !seen) {
					seen = true;
					first = true;
					dist[a] = 0;
				} else {
					ll adist = INFLL;
					ll bdist = INFLL;
					auto it = dist.lower_bound(a);
					while(it != dist.end() && it->first <= b) {
						adist = min(adist, it->second + it->first - a);
						bdist = min(bdist, it->second + b - it->first);
						it = dist.erase(it);
					}
					if(it != dist.end()) {
						adist = min(adist, it->second + it->first - a);
						bdist = min(bdist, it->second + it->first - b);
					}
					if(it != dist.begin()) {
						adist = min(adist, prev(it)->second + a - prev(it)->first);
						bdist = min(bdist, prev(it)->second + b - prev(it)->first);
					}
					dist[a] = adist;
					dist[b] = bdist;
				}
				if(a == b && !first) {
					ans = dist[a] + abs(sx-tx);
					break;
				}
			} else {
				auto ita = dist.find(a);
				if(ita->second >= INFLL) {
					dist.erase(ita);
				}
				auto itb = dist.find(b);
				if(itb->second >= INFLL) {
					dist.erase(itb);
				}
			}
		}
	}

	ll get() const {
		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, sx, sy, tx, ty;
	cin >> n >> sx >> sy >> tx >> ty;

	vector<Rectangle> rect;
	for(int i=0; i<n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		rect.push_back({a, b, c, d});
	}
	Solver horizontal(rect, sx, sy, tx, ty);

	for(int i=0; i<n; i++) {
		rect[i].transpose();
	}
	Solver vertical(rect, sy, sx, ty, tx);

	cerr<<"horizontal: "<<horizontal.get()<<nl;
	cerr<<"vertical: "<<vertical.get()<<nl;
	cout << min(horizontal.get(), vertical.get()) << nl;

	return 0;
}
