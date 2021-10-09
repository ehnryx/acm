#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  const int N = 400, K = 10, W = 1e9, WW = 1e6;
  mt19937 rng;
  cout << N << " " << K << " " << W << nl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << (rng()%WW)+1 << " ";
    }
    cout << nl;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << (rng()%K)+1 << " ";
    }
    cout << nl;
  }

  return 0;
}
