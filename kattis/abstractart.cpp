#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define nl '\n'
using ld = long double;
using pt = complex<ld>;
using ppt = pair<pt,pt>;
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

ld area(const vector<pt>& v) {
	int n = v.size();
	ld s = 0;
	for(int j=n-1, i=0; i<n; j=i++) {
		s += cp(v[j], v[i]);
	}
	return s / 2;
}

ld sgn(const ld& x) {
	return x < -EPS ? -1 : x > EPS ? 1 : 0;
}

bool seg_x_seg(const pt& a, const pt& b, const pt& c, const pt& d) {
	int s1 = sgn(cp(a-b, a-c)); int s2 = sgn(cp(a-b, a-d));
	int s3 = sgn(cp(c-d, c-a)); int s4 = sgn(cp(c-d, c-b));
	if(!s1 && !s2 && !s3) return false;
	return s1*s2 <= 0 && s3*s4 <= 0;
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

struct Event {
	ld x; int t, i;
	Event(ld _x, int _t, int _i): x(_x), t(_t), i(_i) {}
	bool operator < (const Event& o) const {
		if(abs(x-o.x) > EPS) return x < o.x;
		return t < o.t;
	}
};

struct Segment {
	ld m, b, s, t;
	Segment(const pt& u, const pt& v): s(u.real()), t(v.real()) {
		m = (u.imag() - v.imag()) / (u.real() - v.real());
		b = u.imag() - m * u.real();
	}
	bool operator < (const Segment& o) const {
		ld left = max(s, o.s);
		ld right = min(t, o.t);
		ld x = (left + right) / 2;
		if(abs(eval(x) - o.eval(x)) > EPS) return eval(x) < o.eval(x);
		return t < o.t;
	}
	ld eval(const ld& x) const {
		return m*x + b;
	}
	ld area() const {
		return (t-s) * (eval(s)+eval(t)) / 2;
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(9);

	int n;
	cin >> n;
	ld tot = 0;
	vector<ppt> edges;
	for(int i=0; i<n; i++) {
		int m;
		cin >> m;
		vector<pt> p;
		for(int j=0; j<m; j++) {
			int x, y;
			cin >> x >> y;
			p.push_back(pt(x, y));
		}
		ld cur = area(p);
		tot += abs(cur);
		if(cur < 0) {
			reverse(p.begin(), p.end());
		}
		for(int k=m-1, j=0; j<m; k=j++) {
			edges.push_back(make_pair(p[k], p[j]));
		}
	}

	vector<ppt> segs;
	for(const auto& [a, b] : edges) {
		vector<pair<ld,pt>> line;
		for(const auto& [c, d] : edges) {
			if(seg_x_seg(a, b, c, d)) {
				auto it = line_inter(a, b, c, d);
				line.push_back(make_pair(abs(it-a), it));
			}
		}
		sort(line.begin(), line.end(),
			[] (const auto& A, const auto& B) {
				return A.first < B.first;
			}
		);
		for(int i=1; i<line.size(); i++) {
			segs.push_back(make_pair(line[i-1].second, line[i].second));
		}
	}

	vector<Event> ev;
	n = segs.size();
	for(int i=0; i<n; i++) {
		const auto& [a, b] = segs[i];
		ld s = min(a.real(), b.real());
		ld t = max(a.real(), b.real());
		if(abs(s-t) > EPS) {
			ev.push_back(Event(s, 1, i));
			ev.push_back(Event(t, 2, i));
			ev.push_back(Event((s+t)/2, 0, i));
		}
	}
	sort(ev.begin(), ev.end());

	ld ans = 0;
	ordered_set<Segment> top, bot;
	for(const auto& [x, t, i] : ev) {
		const auto& [a, b] = segs[i];
		if(a.real() < b.real()) {
			Segment cur(a, b);
			if(t == 0) {
				int topcnt = top.size() - top.order_of_key(cur);
				int botcnt = bot.size() - bot.order_of_key(cur);
				if(topcnt == botcnt) {
					ans -= cur.area();
				}
			} else if(t == 1) {
				bot.insert(cur);
			} else {
				bot.erase(cur);
			}
		} else {
			Segment cur(b, a);
			if(t == 0) {
				int topcnt = top.order_of_key(cur);
				int botcnt = bot.order_of_key(cur);
				if(botcnt == topcnt+1) {
					ans += cur.area();
				}
			} else if(t == 1) {
				top.insert(cur);
			} else {
				top.erase(cur);
			}
		}
	}

	cout << tot << " " << ans << nl;

	return 0;
}
