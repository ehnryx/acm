#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

// start at a, n terms
ll up(ll a, ll n) {
  return a*n + n*(n-1)/2;
}
ll down(ll a, ll n) {
  ll m = min(a+1,n);
  return m*a - m*(m-1)/2;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  ll t, n, m;
  cin >> t >> n >> m;

  ll a[m], b[m];
  for (int i=0; i<m; i++) {
    cin >> a[i] >> b[i];
  }

  ll ub = up(b[0], a[0]);
  ll lb = down(b[0], a[0]);

  for (int i=1; i<m; i++) {
    ll diff = a[i] - a[i-1];
    if (abs(b[i]-b[i-1]) > diff) {
      cout << "No" << nl;
      return 0;
    }

    ll single = abs(b[i]-b[i-1]);
    ub += up(min(b[i],b[i-1]), single);
    lb += down(max(b[i],b[i-1]), single);
    diff -= single;

    if (diff%2 == 0) {
      ub += 2*up(max(b[i],b[i-1]), diff/2) + max(b[i],b[i-1])+diff/2;
      lb += 2*down(min(b[i],b[i-1]), diff/2) + max(0LL, min(b[i],b[i-1])-diff/2);
    } else {
      ub += 2*up(max(b[i],b[i-1]), diff/2+1);
      lb += 2*down(min(b[i],b[i-1]), diff/2+1);
    }
    ub -= b[i-1];
    lb -= b[i-1];
  }

  ub += up(b[m-1]+1, n-a[m-1]);
  lb += down(b[m-1]-1, n-a[m-1]);

  //cerr << lb << " < " << t << " < " << ub << " ? " << nl;
  if (lb <= t && t <= ub) {
    cout << "Yes" << nl;
  } else {
    cout << "No" << nl;
  }

  return 0;
}
