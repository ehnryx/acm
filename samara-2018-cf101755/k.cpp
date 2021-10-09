#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
int value[N];

int n, m;
bool valid(int k) {
  int cur = 0;
  for (int i = 0; i < n; i++) {
    if (value[i] <= cur) {
      cur++;
    } else if (k > 0) {
      k--;
      cur++;
    }
  }
  return cur >= m;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> value[i];
  }

  int left = 0;
  int right = n;
  int mid = n;
  while (left <= right) {
    mid = (left+right)/2;
    if (valid(mid)) right = mid-1;
    else left = mid+1;
  }
  if (!valid(mid)) mid++;
  cout << mid << nl;

  return 0;
}
