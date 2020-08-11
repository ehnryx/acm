#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

inline bool val(const string& s) {
	return s == "LIE";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n; cin >> n;
	bool res = 0;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		res ^= val(s);
	}
	puts(res ? "LIE" : "TRUTH");

	return 0;
}
