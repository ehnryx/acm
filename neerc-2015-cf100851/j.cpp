#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int N = 1000;

int n;

int query(const string& s) {
	cout << s << endl;
	fflush(stdout);
	int k; cin >> k;
	if (k == n) exit(0);
	return k;
}

char flip(char x) {
	return x == '0' ? '1' : '0';
}

mt19937 rng(time(0));

int main() {

	cin >> n;
	string s(n, '0');
	while (1) {
		for (int i = 0; i < n; i++) {
			s[i] = rng()%2 + '0';
		}
		if (query(s) == n/2) break;
	}
	//cerr << "s: " << s << endl;
	bitset<N> toflip;
	//toflip[0] = 1;
	for (int i = 1; i < n; i++) {
		string t = s;
		t[0] = flip(t[0]);
		t[i] = flip(t[i]);
		if (query(t) == n/2) {
			toflip[i] = 1;
		}
	}
	//for (int i = 0; i < n; i++) if (toflip[i]) cerr << "flip: " << i << nl;
	string t = s;
	for (int i = 0; i < n; i++) {
		if (toflip[i]) t[i] = flip(t[i]);
	}
	query(t);
	t = s;
	for (int i = 0; i < n; i++) {
		if (!toflip[i]) t[i] = flip(t[i]);
	}
	query(t);

	return 0;
}
