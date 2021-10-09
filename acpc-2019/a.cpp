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

const int N = 2e5+1;
const int M = 500;

vector<int> g[N];
unordered_set<int> hob[N];
unordered_set<int> memo[N];
bool done[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;

  unordered_map<string,int> idx;
  int id = 0;
  for(int i=0;i<n;i++) {
    string s,t;
    cin>>s>>t;
    if(!idx.count(s)) idx[s] = id++;
    if(!idx.count(t)) idx[t] = id++;
    g[idx[t]].push_back(idx[s]);
    hob[idx[s]].insert(idx[t]);
  }

  int m;
  cin>>m;
  for(int i=0;i<m;i++) {
    string as, bs;
    cin >> as >> bs;
    int a = idx[as];
    int b = idx[bs];
    bool ok = false;

    if(done[a]) {
      ok = memo[a].count(b);
    } else if(done[b]) {
      ok = memo[b].count(a);
    } else {
      if(hob[a].size() < M) {
        for(int s:hob[a]) {
          if(hob[b].count(s)) {
            ok = true;
            break;
          }
        }
      } else if(hob[b].size() < M) {
        for(int s:hob[b]) {
          if(hob[a].count(s)) {
            ok = true;
            break;
          }
        }
      } else {
        for(int s:hob[a]) {
          for(int t:g[s]) {
            memo[a].insert(t);
          }
        }
        ok = memo[a].count(b);
        done[a] = true;
      }
    }

    if(ok) {
      cout<<"Yes"<<nl;
    } else {
      cout<<"No"<<nl;
    }
  }

  return 0;
}
