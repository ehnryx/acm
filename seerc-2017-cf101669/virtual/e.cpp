#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const unordered_map<string, int> m = {
	{"Do", 0},
	{"Do#", 1},
	{"Re", 2},
	{"Re#", 3},
	{"Mi", 4},
	{"Fa", 5},
	{"Fa#", 6},
	{"Sol", 7},
	{"Sol#", 8},
	{"La", 9},
	{"La#", 10},
	{"Si", 11}
};

const int N = 1e7+1, K = 12;
char a[N+1];
const int scale = 0b101010110101;

inline char get() {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int& x) {
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get());
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
inline void read(string& s) {
	static char c;
	for (c = get(); c == '\n' || c == ' '; c = get());
	for (; c != '\n' && c != ' '; c = get()) s.push_back(c);
}

inline int getkeys(char k) {
	return ((scale << k) | (scale >> (12 - k))) & ((1 << 12) - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n; cin >> n;

	int cur = 0; int last = 0;
	for (int i=0; i<n; i++) {
		string s; cin >> s;
		a[i] = m.at(s);
		if (!i) cur = getkeys(a[i]);
		if (!(cur & getkeys(a[i]))) {
			last = i;
			cur = getkeys(a[i]);
		} else cur &= getkeys(a[i]);
	}
	int ans = 1;
	for (int i = 0; i < last; i++) {
		if (!(cur & getkeys(a[i]))) {
			ans++;
			cur = getkeys(a[i]);
		} else cur &= getkeys(a[i]);
	}
	cout << ans << nl;

	return 0;
}
