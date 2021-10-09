//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 150;
const int K = 20+1;
int dp[N][N][K];

void update(int& x, int v) {
  x = max(x, v);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  unordered_map<char,char> op;
  op['A'] = 'U';
  op['U'] = 'A';
  op['C'] = 'G';
  op['G'] = 'C';

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";

    string S;
    cin >> S;
    int k;
    cin >> k;

    vector<char> val;
    vector<int> cnt;
    int pre = -1;
    S.push_back('Z');
    for(int i=0; i<S.size(); i++) {
      if(isalpha(S[i])) {
        if(pre != -1) {
          val.push_back(S[pre]);
          cnt.push_back(stoi(S.substr(pre+1, i-pre)));
        }
        pre = i;
      }
    }

    int ans = 0;
    if(val.front() == op[val.back()]) {
      ans = min(cnt.front(), cnt.back());
      if(val.front() == 'C' || val.front() == 'G') {
        ans = min(ans, k);
        k -= ans;
      }
      cnt.front() -= ans;
      cnt.back() -= ans;
    }
    //cerr<<"ans: "<<ans<<nl;

    vector<char> arr;
    for(int i=0; i<val.size(); i++) {
      for(int j=0; j<min(50,cnt[i]); j++) {
        arr.push_back(val[i]);
      }
    }

    int n = arr.size();
    memset(dp, 0x3f^0xff, sizeof dp);
    for(int i=0; i<n; i++) {
      for(int j=0; j<=k; j++) {
        dp[i][i][j] = 0;
        if(i>0) dp[i][i-1][j] = 0;
      }
    }

    for(int len=2; len<=n; len++) {
      for(int i=0; i+len<=n; i++) {
        int r = i+len-1;
        for(int j=0; j<=k; j++) {
          if(j>0) update(dp[i][r][j], dp[i][r][j-1]);
          update(dp[i][r][j], dp[i+1][r][j]);
          update(dp[i][r][j], dp[i][r-1][j]);
          for(int s=i+1; s<r-1; s++) {
            for(int t=0; t<=j; t++) {
              update(dp[i][r][j], dp[i][s][t] + dp[s+1][r][j-t]);
            }
          }
          if(arr[i] == op[arr[r]]) {
            if(arr[i] == 'C' || arr[i] == 'G') {
              if(j>0) update(dp[i][r][j], dp[i+1][r-1][j-1] + 1);
            } else {
              update(dp[i][r][j], dp[i+1][r-1][j] + 1);
            }
          }
        }
      }
    }

    cout << ans + dp[0][n-1][k] << nl;
  }

  return 0;
}
