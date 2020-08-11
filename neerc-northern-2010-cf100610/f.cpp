#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
const char nl = '\n';

#define FILE "frames"

struct Rectangle {
	ll x1, y1, x2, y2;
	Rectangle() {}
	Rectangle(ll a, ll b, ll c, ll d) : x1(a), y1(b), x2(c), y2(d) {}
	Rectangle translate(ll dx, ll dy) const {
		return Rectangle(x1+dx, y1+dy, x2+dx, y2+dy);
	}
	ll intersect(const Rectangle& o) const {
		ll dx = min(x2, o.x2) - max(x1, o.x1);
		ll dy = min(y2, o.y2) - max(y1, o.y1);

		return (dx > 0 && dy > 0 ? dx*dy : 0);
	}
};

ll best = -1;
pii slv(-1, -1);
struct Frame {
	Rectangle rect[4];
	ll x[4], y[4];
	void build() {
		sort(x, x+4);
		sort(y, y+4);

		rect[0] = Rectangle(x[0], y[0], x[3], y[1]);
		rect[1] = Rectangle(x[0], y[1], x[1], y[2]);
		rect[2] = Rectangle(x[2], y[1], x[3], y[2]);
		rect[3] = Rectangle(x[0], y[2], x[3], y[3]);
	}
	void intersect(const Frame& o) const {
		for (int i=0; i<4; ++i) {
			for (int j=0; j<4; ++j) {
				for (int k=0; k<4; ++k) {
					for (int l=0; l<4; ++l) {

						ll sum = 0;
						for (int a=0; a<4; ++a) {
							Rectangle shifted = o.rect[a].translate(x[i]-o.x[j], y[k]-o.y[l]);
							for (int b=0; b<4; ++b) {
								sum += shifted.intersect(rect[b]);
							}
						}

						//best = max(best, sum);
						if (sum > best) {
							best = sum;
							slv = pii(x[i]-o.x[j], y[k]-o.y[l]);
						} else if (sum == best) {
							//cerr << " : " << x[i]-o.x[j] << " " << y[k]-o.y[l] << " W " << sum << endl;
						}
					}
				}
			}
		}
	}
};

int main() {
	if (fopen(FILE ".in", "r")) {
		freopen(FILE ".in", "r", stdin);
		freopen(FILE ".out", "w", stdout);
	}

	Frame a, b;

	for (int i=0; i<4; ++i) {
		cin >> a.x[i] >> a.y[i];
	}
	for (int i=0; i<4; ++i) {
		cin >> b.x[i] >> b.y[i];
	}

	a.build();
	b.build();
	a.intersect(b);
	cout << best << endl;
	cout << slv.first << " " << slv.second << endl;

	return 0;
}
