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
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
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

	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;

	int freq[26];
	memset(freq, 0, sizeof freq);
	for (int i = 0; i < n; i++) {
		freq[s[i]-'a']++;
	}

	int letter = -1;
	int bound = INF;
	for (int i = 0; i < 26; i++) {
		if (freq[i] < bound) {
			bound = freq[i];
			letter = i + 'a';
		}
	}

	if (k > n || k < bound) {
		cout << "WRONGANSWER" << nl;
	}
	else {
		string ans;
		for (int i = 0; i < n; i++) {
			ans.push_back(letter);
		}
		int cur = bound;
		for (int i = 0; i < n && cur < k; i++) {
			if (s[i] != letter) {
				ans[i] = s[i];
				cur++;
			}
		}
		cout << ans << nl;
	}

	return 0;
}
