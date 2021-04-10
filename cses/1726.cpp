#include <iostream>

#define F(I,N) for(I=0; I<N; I++)
#define I(C,A,B) if(C) d[s][h+1][(i A)*8 + j B] += d[s][h][i*8+j] / c;

double r[64], d[64][101][64], t;
int k, s, i, j, h, c;
main() {
  std::cin >> k;
  F(s,64) {
    d[s][0][s] = 1;
    F(h,k) F(i,8) F(j,8) {
      c = 2 + (0<i & i<7) + (0<j & j<7);
      I(i>0, -1,   )
      I(j>0,   , -1)
      I(i<7, +1,   )
      I(j<7,   , +1)
    }
    F(i,64) r[i] += !s, r[i] *= 1 - d[s][k][i];
  }
  F(i,64) t += r[i];
  printf("%.6f", t);
}
