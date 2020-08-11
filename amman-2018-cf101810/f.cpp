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


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	//cin >> T;
	read(T);
	while (T--) {
		int n;
		//cin >> n;
		read(n);

		vector<int> a(n);
		unordered_set<int> nums;
		for (int i=0; i<n; i++) {
			//cin >> a[i];
			read(a[i]);
			nums.insert(a[i]);
		}

		ll ans = 0;
		for (int i=0; i<n; i++) {
			vector<int> div;
			int lim = sqrt(a[i]);
			for (int j=1; j<=lim; j++) {
				if (a[i] % j == 0) {
					div.push_back(j);
					div.push_back(a[i]/j);
				}
			}
			sort(div.begin(), div.end());

			for (int j : div) {
				if (nums.count(j)) {
					a[i] = j;
					break;
				}
			}
			ans += a[i];
		}

		cout << ans << nl;
	}

	return 0;
}
