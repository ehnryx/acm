#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define I(A, B) 1LL << (A*7 + B)

int64_t a[3][1<<22], t[3], k;

void h(int i = 6, int j = 6, int64_t m = 0) {
  if(i == 6) for(k=6; k>i; k--) if(!(m & I(i, k))) return;
  if(i == 6 && j == 0) {
    if(__builtin_popcountll(m) == 48) a[2][t[2]++] = m;
    return;
  }
  if(i == 0 || (j == 6 && i < 6) || (m & I(i, j))) return;
  m |= I(i, j);
  if(i>0) h(i-1, j, m);
  if(i<6) h(i+1, j, m);
  if(j>0) h(i, j-1, m);
  if(j<6) h(i, j+1, m);
}

void g(int i = 0, int j = 6, int64_t m = 0) {
  if(j == 6) for(k=0; k<i; k++) if(!(m & I(k, j))) return;
  if(i == 6 && j == 6) return h(i, j, m);
  if((i == 0 && j < 6) || i == 6 || (m & I(i, j))) return;
  m |= I(i, j);
  if(i>0) g(i-1, j, m);
  if(i<6) g(i+1, j, m);
  if(j>0) g(i, j-1, m);
  if(j<6) g(i, j+1, m);
}

void f(int i = 0, int j = 0, int64_t m = 0) {
  if(i == 0) for(k=0; k<j; k++) if(!(m & I(i, k))) return;
  if(i == 0 && j == 6) return g(i, j, m);
  if(i == 6 || j == 6 || (m & I(i, j))) return;
  m |= I(i, j);
  if(i>0) f(i-1, j, m);
  if(i<6) f(i+1, j, m);
  if(j>0) f(i, j-1, m);
  if(j<6) f(i, j+1, m);
}

int main() {

  f();
  cerr << "t = " << t[0] << " " << t[1] << " " << t[2] << nl;

  return 0;
}
