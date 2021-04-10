//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> merge_sort(const vector<int>& a) {
  int n = a.size();
  if(n == 1) return a;
  int half = n/2;
  vector<int> left(a.begin(), a.begin() + half);
  vector<int> right(a.begin() + half, a.end());
  left = merge_sort(left);
  right = merge_sort(right);

  vector<int> out;
  int l = 0, r = 0;
  while(l<left.size() && r<right.size()) {
    cout << 1 << " " << left[l] << " " << right[r] << endl;
    string res;
    cin >> res;
    if(res == "YES") {
      out.push_back(left[l++]);
    } else {
      out.push_back(right[r++]);
    }
  }
  if(l < left.size()) out.insert(out.end(), left.begin()+l, left.end());
  else out.insert(out.end(), right.begin()+r, right.end());
  return out;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  a = merge_sort(a);

  for(int i=1; i<n; i++) {
    cout << 1 << " " << a[i-1] << " " << a[i] << endl;
    string res;
    cin >> res;
    if(res == "NO") {
      cout << 0 << " ";
      for(int _ : a) {
        cout << 0 << " ";
      }
      cout << endl;
      return 0;
    }
  }

  cout << 0 << " ";
  for(int it : a) {
    cout << it << " ";
  }
  cout << endl;

  return 0;
}
