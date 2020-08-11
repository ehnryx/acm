#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

vector<int> days = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int diff(pii a, pii b) {
	int m, d, gm, gd;
	tie(m,d) = a;
	tie(gm,gd) = b;
	int res = 0;
	while (m!=gm || d!=gd) {
		d++;
		if (d > days[m]) {
			d = 1;
			m++;
			if (m > 12) m = 1;
		}
		res++;
	}
	return res;
}

pii pre(pii a) {
	int m, d;
	tie(m,d) = a;
	--d;
	if (d==0) {
		--m;
		if (m==0) {
			m = 12;
		}
		d = days[m];
	}
	return pii(m,d);
}

//#define FILEIO
int main() {
	//ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	pii date[3*n];
	For(i,n) {
		string _; cin >> _;
		int m, d;
		scanf("%d-%d", &m, &d);
		date[i] = pii(m,d);
	}
	sort(date, date+n);

	For(i,n) {
		date[i+2*n] = date[i+n] = date[i];
	}

	int best = 0;
	set<pii> valid;
	For(i,3*n) {
		if (i>0) {
			int cur = diff(date[i-1], date[i]);
			//cerr << date[i-1].first << " " << date[i-1].second << " -- " << date[i].first << " " << date[i].second << " -> " << cur << nl;
			if (cur > best) {
				best = cur;
				valid.clear();
			}
			if (cur == best) {
				valid.insert(pre(date[i]));
			}
		}
	}

	int m = 10;
	int d = 28;
	for (int i=0; i<500; i++) {
		if (valid.count(pii(m,d))) {
			printf("%02d-%02d\n", m, d);
			return 0;
		}
		d++;
		if (d>days[m]) {
			d = 1;
			m++;
			if (m>12) m = 1;
		}
	}
	assert(false);

	return 0;
}
