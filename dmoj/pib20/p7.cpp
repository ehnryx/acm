//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 5e4 + 1;
int a[N], o[N], nxt[N], ans[N];
bool prime[N];

void solve(int n, int f, int d) {
  prime[d] = false;
  for(int s=0; s<d; s++) {
    int len = 0;
    for(int i=f+s; i<n; i+=d) {
      o[len++] = a[i];
    }
    sort(o, o+len);
    for(int i=f+s, j=0; i<n; i+=d) {
      nxt[i] = o[j++];
    }
  }
  for(int i=f; i<n; i++) {
    if(ans[i] < nxt[i]) return;
    if(nxt[i] < ans[i]) {
      for(int j=i; j<n; j++) {
        ans[j] = nxt[j];
      }
      return;
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int i=2; i<N; i++) {
    prime[i] = true;
    for(int j=2; j*j<=i; j++) {
      if(i%j == 0) {
        prime[i] = false;
        break;
      }
    }
  }

  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> a[i];
    o[i] = a[i];
    ans[i] = a[i];
    nxt[i] = a[i];
  }
  sort(o, o+n);

  int first = n;
  for(int i=0; i<n; i++) {
    if(o[i] != a[i]) {
      first = i;
      break;
    }
  }

  if(first == n) {
    for(int i=0; i<n; i++) {
      cout << a[i] << " ";
    }
    cout << nl;
    return 0;
  }

  int last = -1;
  for(int i=first; i<n; i++) {
    if(a[i] == o[first]) {
      last = i;
    }
  }
  assert(last != -1);

  int minv = o[first];
  if(last-first == 1) {
    minv = INF;
    for(int i=first; i<n; i++) {
      if(a[i] == o[first]) continue;
      minv = min(minv, a[i]);
    }
  }

  // move minv to front
  for(int i=first; i<n; i++) {
    if(a[i] == minv) {
      int d = i - first;
      for(int j=1; j*j<=d; j++) {
        if(d % j == 0) {
          if(prime[j]) solve(n, first, d);
          if(prime[d/j]) solve(n, first, d/j);
        }
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
