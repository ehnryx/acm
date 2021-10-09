#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> manacher(const string& s) {
  int n = s.size(); vector<int> len(2*n-1); len[0] = 1;
  for(int d, i=1; i+1 < 2*n; i+=d) {
    int &r = len[i], left = (i-r-1)/2, right = (i+r+1)/2;
    while(0 <= left && right < n && s[left] == s[right]) {
      --left; ++right; r += 2; }
    for(d=1; len[i-d] < r-d; d++) len[i+d] = len[i-d];
    len[i+d] = r-d; } return len; }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(string s;cin>>s;) {
    set<string> ans;
    int n = s.size();
    vector<int> pals = manacher(s);
    for(int i=0; i<2*n-1; i++) {
      if(i%2) {
        for(int j=2; j<=pals[i]; j+=2) {
          ans.insert(s.substr(i/2-j/2+1, j));
        }
      } else {
        for(int j=3; j<=pals[i]; j+=2) {
          ans.insert(s.substr(i/2-j/2, j));
        }
      }
    }
    for(const string& it:ans) {
      cout<<it<<nl;
    }
    cout<<nl;
  }

  return 0;
}
