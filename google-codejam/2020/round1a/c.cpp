//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////



void casesolve() {
  //cerr<<nl;

  int n, m;
  cin >> n >> m;

  const int N = n+2;
  const int M = m+2;

  int g[N][M], sum[N][M], cnt[N][M];
  bool alive[N][M];
  int left[N][M], right[N][M], up[N][M], down[N][M];
  memset(g, 0, sizeof g);
  memset(alive, false, sizeof alive);
  memset(left, -1, sizeof left);
  memset(right, -1, sizeof right);
  memset(up, -1, sizeof up);
  memset(down, -1, sizeof down);

  ll total = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      total += g[i][j];
      alive[i][j] = true;
    }
  }

  for(int i=0; i<N; i++) {
    for(int j=0; j<M; j++) {
      if(i>0) up[i][j] = i-1;
      if(i+1<N) down[i][j] = i+1;
      if(j>0) left[i][j] = j-1;
      if(j+1<M) right[i][j] = j+1;
    }
  }

  vector<pair<int,int>> remove;
  ll ans = total;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      sum[i][j] = g[i-1][j] + g[i+1][j] + g[i][j-1] + g[i][j+1];
      cnt[i][j] = !!g[i-1][j] + !!g[i+1][j] + !!g[i][j-1] + !!g[i][j+1];
      if(i>1 && i<n && j>1 && j<m) assert(cnt[i][j] == 4);
      if(cnt[i][j]*g[i][j] < sum[i][j]) {
        alive[i][j] = false;
        remove.push_back(make_pair(i, j));
      }
    }
  }
  //cerr<<"start with "<<total<<nl;
  //cerr<<nl;

  //int rid = 0;
  while(!remove.empty()) {
    vector<pair<int,int>> cand;
    //cerr<<"round: "<<++rid<<nl;

    for(const auto& it : remove) {
      int i, j;
      tie(i, j) = it;
      assert(g[i][j]);
      assert(up[i][j] != -1);
      assert(down[i][j] != -1);
      assert(left[i][j] != -1);
      assert(right[i][j] != -1);
      assert(sum[i][j] == g[up[i][j]][j] + g[down[i][j]][j] + g[i][left[i][j]] + g[i][right[i][j]]);
      assert(cnt[i][j] == !!g[up[i][j]][j] + !!g[down[i][j]][j] + !!g[i][left[i][j]] + !!g[i][right[i][j]]);
      //cerr<<i<<" "<<j<<nl;
      ////cerr<<"remove "<<i<<" "<<j<<nl;
      total -= g[i][j];

      // connect
      up[down[i][j]][j] = up[i][j];
      down[up[i][j]][j] = down[i][j];
      left[i][right[i][j]] = left[i][j];
      right[i][left[i][j]] = right[i][j];

      // replace
      sum[up[i][j]][j] += g[down[i][j]][j] - g[i][j];
      sum[down[i][j]][j] += g[up[i][j]][j] - g[i][j];
      sum[i][left[i][j]] += g[i][right[i][j]] - g[i][j];
      sum[i][right[i][j]] += g[i][left[i][j]] - g[i][j];
      cnt[up[i][j]][j] += !!g[down[i][j]][j] - !!g[i][j];
      cnt[down[i][j]][j] += !!g[up[i][j]][j] - !!g[i][j];
      cnt[i][left[i][j]] += !!g[i][right[i][j]] - !!g[i][j];
      cnt[i][right[i][j]] += !!g[i][left[i][j]] - !!g[i][j];

      // check and push
      for(const auto& jt : {
        make_pair(up[i][j], j), make_pair(down[i][j], j),
        make_pair(i, left[i][j]), make_pair(i, right[i][j])
      }) {
        cand.push_back(jt);
      }
    }

    remove.clear();
    for(const auto& it : cand) {
      int i, j;
      tie(i, j) = it;
      if(!alive[i][j] || !g[i][j]) continue;
      //cerr<<"ASSERT "<<i<<" "<<j<<" -> Sum = "<<sum[i][j]<<nl;
      //cerr<<"up: "<<g[up[i][j]][j]<<nl;
      //cerr<<"down: "<<g[down[i][j]][j]<<nl;
      //cerr<<"left: "<<g[i][left[i][j]]<<nl;
      //cerr<<"right: "<<g[i][right[i][j]]<<nl;
      assert(sum[i][j] == g[up[i][j]][j] + g[down[i][j]][j] + g[i][left[i][j]] + g[i][right[i][j]]);
      if(cnt[i][j]*g[i][j] < sum[i][j]) {
        alive[i][j] = false;
        remove.push_back(make_pair(i, j));
      }
    }
    ans += total;
    //cerr<<"add "<<total<<nl;
    //cerr<<nl;
  }

  cout << ans << nl;
  //cerr<<nl;

  return;
}

