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
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;}
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	for (int n;;) {
		cin >> n;
		if (!n) break;
		int a, b;
		pol p;
		for (int i=0; i<n; i++) {
			cin >> a >> b;
			p.push_back(pt(a,b));
		}
		cout << area(chull(p)) << nl;
	}

	return 0;
}
