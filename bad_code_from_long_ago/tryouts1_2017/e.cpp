#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	const int lim = 50;

	int add = 1;
#ifdef DEBUG 
	for (add = 0; add <= lim; add++) {
#endif

	ll pos[lim+1][lim+1]; // a, b
	for (int i = 0; i <= lim; i++)
		for (int j = 0; j <= lim; j++)
			pos[i][j] = 3017+i;

	int ans = 0;
	ll guess;
	int gc;
	unordered_map<ll,int> cnt;
	string s = "";
	while (s != "Captured") {
		cnt.clear();
		for (int i = 0; i <= lim; i++) 
			for (int j = 0; j <= lim; j++) 
				if (pos[i][j] > 0) 
					cnt[pos[i][j]]++;
#ifdef DEBUG
		if (cnt.empty()) break;
#endif
		gc = 0;
		for (auto& p: cnt) {
			if (p.second > gc) {
				guess = p.first;
				gc = p.second;
			} else if (p.second == gc && p.first > guess) {
				guess = p.first;
			}
		}
		if (ans == 0) guess = 3017+add;
		for (int i = 0; i <= lim; i++) {
			for (int j = 0; j <= lim; j++) {
				if (pos[i][j] > 0) {
					if (pos[i][j] == guess)
						pos[i][j] = 0;
					else
						pos[i][j] += j;
				}
			}
		}
		ans++;
#ifndef DEBUG
		cout << guess << endl; 
		cin >> s;
#endif
	}
#ifdef DEBUG
	cerr << add << ": " << ans << " guesses" << endl;
}
#endif

	return 0;
}
