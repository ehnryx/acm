#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int a[N];

int main() {
  int n, k, r;
  scanf("%d%d%d", &n, &k, &r);
  for (int i = 1; i <= k; i++) {
    int x;
    scanf("%d", &x);
    a[x] = true;
  }
  int cnt = 0;
  for (int i = 1; i <= r; i++) {
    cnt += a[i];
  }
  printf("%d\n", ans);
  return 0;
}
