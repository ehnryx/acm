#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

const int N = 5e3+1;
int c[N];
char s[N], t[N];


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  for (int i=0; i<n; i++) {
    cin >> c[i];
  }

  ll init = 0;
  for (int i=0; i<n; i++) {
    cin >> s[i];
    s[i] -= '0';
    if (s[i]) {
      init += c[i];
    }
  }

  vector<pii> sorted;
  for (int i=0; i<n; i++) {
    cin >> t[i];
    t[i] -= '0';
    sorted.push_back(pii(c[i],i));
  }
  sort(sorted.begin(), sorted.end());

  ll ans = INFLL;
  for (int ch=0; ch<=n; ch++) {
    ll cur = 0;
    ll active = init;
    int last = n;
    int cnt = 0;
    // remove
    for (int j=n-1; j>=0; j--) {
      int i = sorted[j].second;
      if (s[i] && !t[i]) {
        active -= c[i];
        cur += active;
      } else if (s[i] && t[i] && cnt<ch) {
        cnt++;
        last = j;
        active -= c[i];
        cur += active;
      }
    }
    // add
    for (int j=0; j<n; j++) {
      int i = sorted[j].second;
      if (!s[i] && t[i]) {
        active += c[i];
        cur += active;
      } else if (s[i] && t[i] && j>=last) {
        active += c[i];
        cur += active;
      }
    }
    ans = min(ans, cur);
  }
  cout << ans << nl;

  return 0;
}
