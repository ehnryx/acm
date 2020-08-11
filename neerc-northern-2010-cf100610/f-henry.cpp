#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const char nl = '\n';

#define FILE "frames"

int main() {
	if (fopen(FILE ".in", "r")) {
		freopen(stdin, FILE ".in", "r");
		freopen(stdout, FILE ".out", "w");
	}

	Rectangle in[2], out[2];
	for(int i=0; i<2; i++) {
		int a, b, x, y, ia, ib, ix, iy
		cin >> a >> b >> x >> y >> ia >> ib >> ix >> iy;
		out[i] = {a,b,x,y};
		in[i] = {ia,ib,ix,iy};
	}

	

	return 0;
}
