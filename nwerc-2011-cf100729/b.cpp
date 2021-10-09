#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

void solve(int a, int b, string& s) {
  if (a == 2 && b == 1) {
    s += 'R';
    return;
  }
  if (a == 1 && b == 2) {
    s += 'L';
    return;
  }

  if (a > b) {
    s += 'R';
    solve(b, a-b, s);
  }
  else {
    s += 'L';
    solve(b-a, a, s);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int TT;
  scanf("%d", &TT);
  while (TT--) {
    int a, b;
    scanf("%d/%d", &a, &b);
    string s;
    solve(a, b, s);
    printf("%s\n", s.c_str());
  }



}
