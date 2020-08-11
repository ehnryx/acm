#include <bits/stdc++.h>
using namespace std;
#define FILENAME "black"

typedef long long ll;
typedef long double ld;
const char nl = '\n';


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
	int b, w;
	cin >> b >> w;
	char bb = '@';
	char ww = '.';
	if (b > w) {
		swap(b,w);
		swap(bb, ww);
	}
	//b <= w
	int d = w - b;
	int r = 3; int c = (2*d+1+2*b-1);
	cout << r << " " << c << nl;
	for (int i = 0; i < c; i++) {
		if (i < 2*d+1) {
			cout << bb;
		}	else {
			int p = i - 2*d;
			cout << (p%2 ? ww : bb);
		}
	}
	cout << nl;
	for (int i = 0; i < c; i++) {
		cout << (i%2 ? ww : bb);
	}
	cout << nl;
	for (int i = 0; i < c; i++) {
		if (i < 2*d+1) {
			cout << bb;
		}	else {
			int p = i - 2*d;
			cout << (p%2 ? ww : bb);
		}
	}
	cout << nl;

	return 0;
}

