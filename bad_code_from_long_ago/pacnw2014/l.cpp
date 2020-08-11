#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

inline ld dist(const vector<ll> &a, const vector<ll> &b) {
	return sqrt((a[0]-b[0])*(a[0]-b[0])
		+ (a[1]-b[1])*(a[1]-b[1])
		+ (a[2]-b[2])*(a[2]-b[2]));
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	cout << fixed << setprecision(0);

	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		int p; cin >> p;
		map<string, int> dumb;
		vector<vector<ll>> ps(p);
		for (int i = 0; i < p; i++) {
			string s; int x, y, z; cin >> s >> x >> y >> z;
			dumb[s] = i;
			ps[i] = {x, y, z};
		}
		vector<vector<ld>> d(p, vector<ld>(p));
		for (int i = 0; i < p; i++)
			for (int j = 0; j < p; j++)
				d[i][j] = dist(ps[i], ps[j]);
		int w; cin >> w;
		for (int i = 0; i < w; i++) {
			string a, b; cin >> a >> b;
			d[dumb[a]][dumb[b]] = 0;
		}
		for (int k = 0; k < p; k++)
			for (int i = 0; i < p; i++)
				for (int j = 0; j < p; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		int q; cin >> q;
		cout << "Case " << t << ":" << endl;
		while (q--) {
			string a, b; cin >> a >> b;
			cout << "The distance from " << a << " to " << b << " is " << d[dumb[a]][dumb[b]] << " parsecs." <<endl;
		}
	}
	return 0;
}
