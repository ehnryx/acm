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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    string s,t;
    cin>>s>>t;
    int n = s.size();

    set<vector<int>> seen;
    for(int i=0;i<n;i++) {
      vector<int> cnt(26,0);
      for(int j=i;j<n;j++) {
        cnt[t[j]-'a']++;
        seen.insert(cnt);
      }
    }

    int best = 0;
    int start = -1;
    for(int i=0;i<n;i++) {
      vector<int> cnt(26,0);
      for(int j=i;j<n;j++) {
        cnt[s[j]-'a']++;
        if(j-i+1 > best && seen.count(cnt)) {
          best = j-i+1;
          start = i;
        }
      }
    }

    if(best) {
      for(int i=0;i<best;i++) {
        cout<<s[start+i];
      }
      cout<<nl;
    } else {
      cout<<"NONE"<<nl;
    }
  }

  return 0;
}
