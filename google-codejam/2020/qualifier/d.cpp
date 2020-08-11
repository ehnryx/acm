#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve(int);
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	int B;
	cin >> B;
	for (int cc = 1; cc <= T; cc++) {
		//cout << "Case #" << cc << ": ";
		solve(B);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 150 + 1;
int ans[N];
vector<int> groups[N];

int query(int v) {
	cout << v << endl;
	char r;
	cin >> r;
	assert(r != 'N');
	return r - '0';
}

void answer(int n) {
	for(int i=1; i<=n; i++) {
		cout << ans[i];
	}
	cout << endl;
	char r;
	cin >> r;
	if(r == 'N') {
		exit(0);
	}
}

void caseinit() {
}

void solve(int n) {
	caseinit();

	int m = 0;
	for(int s=0; s<n; s+=8) {
		groups[m].clear();
		for(int i=0; i<4; i++) {
			if(s/2 + i + 1 > n - (s/2 + i)) break;
			groups[m].push_back(s/2 + i + 1);
			groups[m].push_back(n - (s/2 + i));
		}
		m++;
	}

	int state = 0; // 1: comp, 0: rev
	int same = -1;
	int diff = -1;
	for(int i=0; i<m; i++) {
		state = 0;
		if(same == -1) {
			query(1);
		} else {
			if(query(same) != ans[same]) {
				state |= 0b10;
			}
		}
		if(diff == -1) {
			query(1);
		} else {
			if(query(diff) == ans[diff]) {
				if(state) state |= 0b01;
			} else {
				if(!state) state |= 0b01;
			}
		}
		//cerr<<"State: "<<bitset<2>(state)<<nl;

		for(int it : groups[i]) {
			int val = query(it);
			if(state & 0b10) val ^= 1;
			if(state & 0b01) {
				ans[n-it+1] = val;
			} else {
				ans[it] = val;
			}
		}

		for(int it : groups[i]) {
			if(ans[it] == ans[n-it+1]) {
				same = it;
			} else {
				diff = it;
			}
		}
	}

	if(state & 0b01) {
		reverse(ans+1, ans+1+n);
	}
	if(state & 0b10) {
		for(int i=1; i<=n; i++) {
			ans[i] ^= 1;
		}
	}

	answer(n);

	return;
}

