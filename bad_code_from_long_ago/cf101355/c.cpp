#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	const int N = 1e5+1;
	int a[N], start[N], end[N];

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		unordered_set<int> seen;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] != 0)
				seen.insert(a[i]);
		}

		int pos = 0;
		for (int i = 1; i <= n; i++) {
			if (!seen.count(i)) {
				int j = i;
				while (a[j] != 0) {
					j = a[j];
				}
				start[pos] = i;
				end[pos] = j;
				pos++;
			}
		}

		for (int i = 0; i < pos; i++) {
			a[end[i]] = start[(i+1)%pos];
		}

		int ans = n;
		vector<bool> vis(n+1);
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				vis[i] = true;
				for (int j = a[i]; j != i; j = a[j])
					vis[j] = true;
				ans--;
			}
		}

		cout << ans << nl;
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << nl;
	}

	return 0;
}
