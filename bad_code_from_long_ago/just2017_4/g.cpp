#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, ans;
  int arr[1000000];
  int left[1000000];
  int right[1000000];

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> arr[i];
    left[0] = arr[0];
    for (int i = 1; i < n; i++)
      left[i] = max(left[i-1], arr[i]);
    right[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--)
      right[i] = min(right[i+1], arr[i]);

    ans = 0;
    for (int i = 1; i < n-1; i++) {
      if (left[i] == arr[i] && arr[i] == right[i])
        ans++;
    }
    cout << ans << nl;
  }

  return 0;
}
