#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef double ld;
//typedef complex<ld> pt;

struct pt {
	ld x, y;
	pt(const ld& _x=0, const ld& _y=0): x(_x), y(_y) {}
	pt operator * (const pt& o) const { return pt(x*o.x - y*o.y, x*o.y + y*o.x); }
	pt operator - () const { return pt(-x, -y); }
	pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); };
	pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); };
	pt operator / (const ld& c) const { return pt(x/c, y/c); }
	ld real() const { return x; }
	ld imag() const { return y; }
};
ld real(const pt& a) { return a.x; }
ld imag(const pt& a) { return a.y; }
pt conj(const pt& a) { return pt(a.x, -a.y); }
ld abs(const pt& a) { return sqrt(a.x*a.x + a.y*a.y); }
pt operator * (const ld& c, const pt& a) { return pt(c*a.x, c*a.y); }

const char nl = '\n';
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

ld dp(const pt& a, const pt& b) {
	return real(conj(a) * b);
}

ld area(const vector<pt>& p) {
	int n = p.size();
	ld s = 0;
	for(int j=n-1, i=0; i<n; j=i++) {
		s += cp(p[j], p[i]);
	}
	return s;
}

vector<pt> read() {
	int n;
	cin >> n;
	vector<pt> out;
	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		out.push_back(pt(x, y));
	}
	if(area(out) < 0) {
		reverse(out.begin(), out.end());
	}
	return out;
}

vector<pt> reflect(const vector<pt>& p) {
	vector<pt> out;
	for(const pt& v : p) {
		out.push_back(-v);
	}
	return out;
}

vector<pt> orient(const vector<pt>& p, int e) {
	pt base = p[e];
	pt dir = p[(e+1)%p.size()] - p[e];
	dir = conj(dir / abs(dir));

	vector<pt> out;
	for(const pt& v : p) {
		out.push_back((v - base) * dir);
	}
	return out;
}

enum {
	END_BAD,
	START_FRONT,
	END_FRONT,
	START_ALL,
	END_ALL,
	START_BACK,
	END_BACK,
	START_BAD,
};

struct Event {
	ld x;
	int t;
	ld v;
	Event(const ld& _x, int _t, const ld& _v=0): x(_x), t(_t), v(_v) {}
	bool operator < (const Event& o) const {
		if(x != o.x) return x < o.x;
		return t < o.t;
	}
};

pt get_point(const pt& a, const pt& b, ld y) {
	pt v = (y - a.imag()) / (b.imag() - a.imag()) * (b-a);
	return a + v;
}

pair<ld,ld> get_range(pt a, pt b, pt c, pt d) {
	if(a.imag() > b.imag()) swap(a, b);
	if(c.imag() > d.imag()) swap(c, d);
	ld s = max(a.imag(), c.imag());
	ld t = min(b.imag(), d.imag());
	return make_pair(s, t);
}

void intersect_edges(const pt& v, const pt& w, const vector<pt>& p, vector<Event>& ev) {
	int n = p.size();

	for(int i=0; i<n; i++) {
		const pt& a = p[i];
		const pt& b = p[(i+1)%n];
		auto [s, t] = get_range(v, w, a, b);
		if(s > t + EPS) continue; // no intersection

		if(abs(cp(a-b, v-w)) < EPS) {
			// parallel
			if(dp(a-b, v-w) > 0) continue; // wrong orientation
			if(abs(a.imag() - b.imag()) < EPS) {
				// horizontal
				ld lfix = min(a.real(), b.real());
				ld rfix = max(a.real(), b.real());
				ld lmov = min(v.real(), w.real());
				ld rmov = max(v.real(), w.real());
				ld left = lfix - rmov;
				ld right = rfix - lmov;
				ld front = min(lfix - lmov, rfix - rmov);
				ld back = max(lfix - lmov, rfix - rmov);
				ld overlap = min(rfix - lfix, rmov - lmov);

				ev.push_back(Event(left, START_FRONT, left));
				ev.push_back(Event(front, END_FRONT, left));
				ev.push_back(Event(front, START_ALL, overlap));
				ev.push_back(Event(back, END_ALL, overlap));
				ev.push_back(Event(back, START_BACK, right));
				ev.push_back(Event(right, END_BACK, right));
			}

			else {
				// not horizontal
				pt u = get_point(a, b, s);
				ld x = u.real() - get_point(v, w, s).real();
				ld overlap = abs(u - get_point(a, b, t));
				ev.push_back(Event(x - EPS, START_ALL, overlap));
				ev.push_back(Event(x + EPS, END_ALL, overlap));
			}
		}

		else {
			// not parallel
			if(abs(a.imag() - b.imag()) < EPS) {
				// ab is horizontal
				if(cp(b-a, v-a) < EPS && cp(b-a, w-a) < EPS) continue; // all on the good side
				pt u = get_point(v, w, a.imag());
				ld left = min(a.real(), b.real()) - u.real();
				ld right = max(a.real(), b.real()) - u.real();
				ev.push_back(Event(left + EPS, START_BAD));
				ev.push_back(Event(right - EPS, END_BAD));
			}

			else if(abs(v.imag() - w.imag()) < EPS) {
				// vw is horizontal
				if(cp(w-v, a-v) < EPS && cp(w-v, b-v) < EPS) continue; // all on the good side
				pt c = get_point(a, b, v.imag());
				ld left = c.real() - max(v.real(), w.real());
				ld right = c.real() - min(v.real(), w.real());
				ev.push_back(Event(left + EPS, START_BAD));
				ev.push_back(Event(right - EPS, END_BAD));
			}

			else {
				// neither is horizontal
				ld left = get_point(a, b, s).real() - get_point(v, w, s).real();
				ld right = get_point(a, b, t).real() - get_point(v, w, t).real();
				if(left > right) swap(left, right);
				if(abs(left - right) < EPS) continue;
				ev.push_back(Event(left + EPS, START_BAD));
				ev.push_back(Event(right - EPS, END_BAD));
			}
		}
	}
}

void intersect_points(const pt& v, const vector<pt>& p, vector<Event>& ev) {
	int n = p.size();
	ld y = v.imag();

	for(int i=0; i<n; i++) {
		const pt& a = p[i];
		const pt& b = p[(i+1)%n];
		const pt& c = p[(i+2)%n];
		ld s = min(a.imag(), b.imag());
		ld t = max(a.imag(), b.imag());

		bool push_start = false;
		bool push_end = false;
		ld x = b.real() - v.real();

		if(s + EPS < y && y < t - EPS) {
			// intersects edge
			x = get_point(a, b, y).real() - v.real();
			if(a.imag() < b.imag()) {
				push_end = true; // up edge -> end
			} else {
				push_start = true; // down edge -> start
			}
		}

		else if(abs(b.imag() - y) < EPS) {
			// intersects vertex
			s = min(a.imag(), c.imag());
			t = max(a.imag(), c.imag());

			if(s + EPS < y && y < t - EPS) {
				// hits normal turn
				if(a.imag() < c.imag()) {
					push_end = true;
				} else {
					push_start = true;
				}
			}

			else if(cp(a-b, c-b) > 0) {
				// should be concave
				if(abs(s - y) < EPS || abs(t - y) < EPS) {
					// orthogonal
					if(a.imag() < c.imag()) {
						push_end = true;
					} else {
						push_start = true;
					}
				} else {
					// v shaped
					push_end = true;
					push_start = true;
				}
			}
		}

		if(push_start) {
			ev.push_back(Event(x + EPS, START_BAD));
		}
		if(push_end) {
			ev.push_back(Event(x - EPS, END_BAD));
		}
	}
}

ld sweep(const vector<pt>& p, const vector<pt>& q) {
	int n = p.size();
	int m = q.size();
	vector<pt> ref_p = reflect(p);
	vector<pt> ref_q = reflect(q);

	vector<Event> ev;
	for(int i=0; i<n; i++) {
		intersect_edges(p[i], p[(i+1)%n], q, ev);
		intersect_points(p[i], q, ev);
		intersect_points((p[i]+p[(i+1)%n])/(ld)2, q, ev);
	}
	for(int j=0; j<m; j++) {
		intersect_points(ref_q[j], ref_p, ev);
		intersect_points((ref_q[j]+ref_q[(j+1)%m])/(ld)2, ref_p, ev);
	}
	sort(ev.begin(), ev.end());

	ld best = 0;
	ld all = 0;
	ld front = 0;
	ld back = 0;
	int fcnt = 0;
	int bcnt = 0;
	int bad = 0;

	for(const auto& [x, t, v] : ev) {
		if(!bad) {
			ld cur = all + (fcnt*x - front) + (back - bcnt*x);
			best = max(best, cur);
		}

		if(t == START_FRONT) {
			fcnt++;
			front += v;
		} else if(t == END_FRONT) {
			fcnt--;
			front -= v;
		} else if(t == START_ALL) {
			all += v;
		} else if(t == END_ALL) {
			all -= v;
		} else if(t == START_BACK) {
			bcnt++;
			back += v;
		} else if(t == END_BACK) {
			bcnt--;
			back -= v;
		} else if(t == START_BAD) {
			bad++;
		} else { // t == END_BAD
			bad--;
		}

		if(!bad) {
			ld cur = all + (fcnt*x - front) + (back - bcnt*x);
			best = max(best, cur);
		}
	}

	//assert(bad == 0);
	//assert(fcnt == 0);
	//assert(bcnt == 0);
	//assert(abs(front) < EPS);
	//assert(abs(back) < EPS);

	return best;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	vector<pt> p = read();
	vector<pt> q = read();
	int n = p.size();
	int m = q.size();

	ld ans = 0;
	for(int i=0; i<n; i++) {
		vector<pt> rotp = orient(p, i);
		for(int j=0; j<m; j++) {
			vector<pt> rotq = reflect(orient(q, j));
			ans = max(ans, sweep(rotp, rotq));
		}
	}
	cout << ans << nl;

	return 0;
}
