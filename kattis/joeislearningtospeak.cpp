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

  unordered_set<string> sep;
  sep.insert(".");
  sep.insert(",");
  sep.insert(":");
  sep.insert(";");
  sep.insert("?");
  sep.insert("!");

  for(int n,tt=1;cin>>n;tt++) {
    cout<<"Learning case "<<tt<<nl;

    unordered_set<string> words;
    set<vector<string>> sentences;
    words.insert("joe");
    sentences.insert({"joe"});

    vector<string> sc;
    for(string s;cin>>s&&s!="*";) {
      for(char& c:s) c = tolower(c);
      if(!sep.count(s)) {
        words.insert(s);
        sentences.insert({s});
        sc.push_back(s);
      } else {
        int m = sc.size();
        for(int i=0;i<m;i++) {
          vector<string> cur;
          for(int j=0;j<n&&i+j<m;j++) {
            cur.push_back(sc[i+j]);
            sentences.insert(cur);
          }
        }
        sc.clear();
      }
    }
    sc.clear();

    vector<string> tc;
    for(string s;cin>>s&&s!="#";) {
      string t = s;
      for(char& c:s) c = tolower(c);
      if(!sep.count(s)) {
        if(!words.count(s)) {
          cout<<"What does the word \""<<t<<"\" mean?"<<nl;
          words.insert(s);
        }
        sentences.insert({s});
        sc.push_back(s);
        tc.push_back(t);
      } else {
        int m = sc.size();
        bool ask = false;
        for(int i=0;i<m;i++) {
          vector<string> cur;
          for(int j=0;j<n&&i+j<m;j++) {
            cur.push_back(sc[i+j]);
            if(!sentences.count(cur)) {
              ask = true;
              sentences.insert(cur);
            }
          }
        }
        if(ask) {
          cout<<"What does the sentence \"";
          for(int i=0;i<m;i++) {
            if(i>0) cout<<" ";
            cout<<tc[i];
          }
          cout<<"\" mean?"<<nl;
        }
        sc.clear();
        tc.clear();
      }
    }

    cout<<nl;
  }

  return 0;
}
