#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';
const int N = 1 << 19;

int n, q;
string s;
ll t[2*N], d[2*N];
void push(int i) { if (d[i]) { t[2*i] += d[i]; t[2*i+1] += d[i];
  d[2*i] += d[i]; d[2*i+1] += d[i]; d[i] = 0; }}
void pull(int i) {
  t[i] = min(t[2*i], t[2*i+1]);
}
void modify(int x, int y, int v, int i=1, int l=0, int r=N-1) {
  if (y<l || r<x) return;
  if (x<=l && r<=y) { t[i] += v; d[i] += v; return; }
  int m = (l+r)/2; push(i); modify(x, y, v, 2*i, l, m); modify(x, y, v, 2*i+1, m+1, r);
  pull(i);
}
int query(int x, int y, int i=1, int l=0, int r=N-1) {
  if (y<l || r<x) return INF; if (x<=l && r<=y) return t[i]; int m = (l+r)/2;
  push(i); return min(query(x, y, 2*i, l, m), query(x, y, 2*i+1, m+1, r)); }
int bs() {
  int l = 0, r = n-1, ans = -1;
  while (l <= r) {
    int mid = (l+r)/2;
    if (query(mid, n-1) < 2) {
      l = mid+1;
    } else {
      r = mid-1;
      ans = mid;
    }
  }
  return ans;
}

set<int> close;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);
  cin >> n >> q;
  cin >> s;
  for (int i = 0; i < n; i++) {
    modify(i, n, (s[i] == '(') - (s[i] == ')'));
    if (s[i] == ')') close.insert(i);
  }
  while (q--) {
    int flip; cin >> flip; flip--;
    if (s[flip] == '(') {
      s[flip] = ')';
      close.insert(flip);
      modify(flip, n, -2);
      int ans = *close.begin();
      s[ans] = '(';
      modify(ans, n, 2);
      close.erase(close.begin());
      cout << ans+1 << nl;
    } else {
      s[flip] = '(';
      close.erase(flip);
      modify(flip, n, 2);
      /*
      for (int i = 0; i < n; i++) {
        cerr << query(i, i) << " ";
      }
      cerr << endl;
      for (int i = 0; i < n; i++) {
        cerr << query(i, n-1) << " ";
      }
      cerr << endl;
      */
      int ans = bs();
      s[ans] = ')';
      modify(ans, n, -2);
      close.insert(ans);
      cout << ans+1 << nl;
    }
  }
  return 0;
}
