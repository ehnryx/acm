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

const int N = 1e4 + 1;
int n;
int arr[N];
int id[N];
vector<pii> ans;

void iswap(int cur) {
  int mid = id[cur];
  int len = min(mid - cur, n - mid + 1);
  int left = mid - len;
  int right = mid + len - 1;
  ans.push_back(pii(left, right));

  for (int i = 0; i < len; i++) {
    swap(arr[left+i], arr[mid+i]);
    id[arr[left+i]] = left+i;
    id[arr[mid+i]] = mid+i;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    ans.clear();
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> arr[i];
      id[arr[i]] = i;
    }
    for (int cur = 1; cur <= n; cur++) {
      int mid = (cur + n) / 2;
      while (id[cur] > mid) {
        iswap(cur);
      }
      if (id[cur] > cur) {
        iswap(cur);
      }
    }

    cout << ans.size() << nl;
    for (const pii& it : ans) {
      cout << it.first << " " << it.second << nl;
    }
  }

  return 0;
}
