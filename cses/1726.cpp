#include<bits/stdc++.h>
using namespace std;

double r[64], d[8][8], p[8][8];
int k, s, i, j, h, c;
main() {
	cin >> k;
	fill(r, r+64, 1);
	for(s=0; s<64; s++) {
		memset(d, 0, sizeof d);
		d[s/8][s%8] = 1;
		for(h=0; h<k; h++) {
			memset(p, 0, sizeof p);
			for(i=0; i<8; i++) for(j=0; j<8; j++) {
				c = 2 + (0<i & i<7) + (0<j & j<7);
				if(i>0) p[i-1][j] += d[i][j] / c;
				if(j>0) p[i][j-1] += d[i][j] / c;
				if(i<7) p[i+1][j] += d[i][j] / c;
				if(j<7) p[i][j+1] += d[i][j] / c;
			}
			swap(d, p);
		}
		for(i=0; i<64; i++) r[i] *= 1 - d[i/8][i%8];
	}
	printf("%.6f", accumulate(r, r+64, 0.));
}
