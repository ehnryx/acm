#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void setprint(const set<int>& s) {
	cerr << "(";
	for(int v : s ) {
		cerr << v << ", ";
	}
	cerr << ")";
}

struct mapping {
	set<int> raw, encoded;

	static set<int> intersect(const set<int>& a, const set<int>& b)
	{
		set<int> ans;
		for(auto ait = a.begin(), bit=b.begin();ait != a.end() && bit != b.end();++ait) {
			for(;bit != b.end() && *bit < *ait;++bit) {}
			if(bit != b.end() && *bit == *ait) {
				ans.insert(*ait);
			}
		}
		return ans;
	}


	void insert(int a, int b) {
		raw.insert(a);
		encoded.insert(b);
	}
	bool contains(int a, int b) const {
		return ( raw.count(a) && encoded.count(b) );
	}
	int size() const {
		return raw.size();
	}
	mapping intersect(const mapping& o) const {
		set<int> new_raw = intersect(raw, o.raw);
		set<int> new_encoded = intersect(encoded, o.encoded);
		mapping ans;
		ans.raw = new_raw;
		ans.encoded = new_encoded;
		return ans;
	}
};

ll factorial(ll v) {
	if(v <= 1) {
		return 1LL;
	}
	return factorial(v-1)*v;
}

struct block {
	bool valid;
	vector<mapping> mappings;
	vector<int> group_of_index;
	int my_size;

	block() :valid(true) {}
	block(string a, string b) {
		set_to(a, b);
	}
	void set_to(string a, string b) {
		my_size = a.size();
		mappings = vector<mapping> ();
		group_of_index = vector<int>(a.size(), -1);
		valid = true;

		vector<vector<int>> aind(26, vector<int>());
		vector<vector<int>> bind(26, vector<int>());

		// map character to occurrences of that character
		for(size_t i=0;i<a.size();++i) {
			aind[a[i]-'a'].push_back(i);
		}
		for(size_t i=0;i<a.size();++i) {
			bind[b[i]-'a'].push_back(i);
		}
		int gind = 0;

		for(size_t i=0;i<26;++i) {
			if(aind[i].size() || bind[i].size()) {
				if(aind[i].size() != bind[i].size()) {
					// require the same number of each character.
					valid = false;
					return;
				}
				mapping m;
				for(size_t j=0;j<aind[i].size();++j) {
					m.insert(aind[i][j], bind[i][j]);
					group_of_index[aind[i][j]] = gind;
				}
				mappings.push_back(m);
				++gind;
			}
		}
	}

	bool has_mapping(int a, int b) const {
		if(!valid) return false;
		return mappings[group_of_index[a]].contains(a, b);
	}

	void print() {
		for(mapping m : mappings) {
			setprint(m.raw); 
			//cerr << " -> ";
			setprint(m.encoded);
			//cerr << "; ";
		}
	}

	block merge(const block& o) const {
		block ans;
		if(!valid || !o.valid) {
			ans.valid = false;
			return ans;
		}

		for(int i=0;i<size();++i) {
			bool found = false;
			for(int v : mappings[group_of_index[i]].encoded) {
				if(o.has_mapping(i, v)) {
					found = true;
					break;
				}
			}
			if(!found) {
				//cerr << " bad merge because could not find a mapping for " << i << endl;
				ans.valid = false;
				return ans;
			}
		}

		vector<mapping> new_mapping;
		for(mapping m : mappings)
		{
			set<int> other_groups;
			for(int v : m.raw) {
				other_groups.insert(o.group_of_index[v]);
			}
			for(int g : other_groups) {
				new_mapping.push_back(o.mappings[g].intersect(m));
			}
		}
		vector<int> goi(size());
		for(size_t i=0;i<new_mapping.size();++i) {
			for(int v : new_mapping[i].raw) {
				goi[v] = i;
			}
		}
		ans.my_size = size();
		ans.valid = true;
		ans.mappings = new_mapping;
		ans.group_of_index = goi;
		return ans;
	}

	ll get_ans() const {
		if(!valid) return 0LL;
		ll ans = 1;
		for( mapping m : mappings ) {
			ans *= factorial(m.size());
		}
		return ans;
	}

	int size() const {
		return my_size;
	}

};

void run(int k, string& m, string& c) {
	if(m.size() != c.size() || m.size()%k != 0) {
		cout << "0\n";
		return ;
	}
	////////cerr << "!! " << endl;
	vector<block> blocks;
	for(size_t i=0;i<m.size()/k;++i) {
		////////cerr << "-- " << endl;
		blocks.push_back(block(m.substr(i*k, k), c.substr(i*k, k)));
		////////cerr << "-- " << endl;
		if(!blocks.back().valid) {
			cout << "0" << endl;
			return ;
		}
	}
	//////cerr << "!! " << endl;
	block base = blocks[0];
	for(size_t i=1;i<blocks.size();++i) {
		//cerr << "!! ";
		//cerr; base.print(); //cerr << endl;
		//cerr; blocks[i].print(); //cerr << endl;
		base = base.merge(blocks[i]);
		if(!base.valid) {
			cout << "0" << endl;
			return ;
		}
	}
	//cerr; base.print();
	//cerr << endl;
	cout << base.get_ans() << endl;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);
	while(!cin.eof()) {
		int k; cin >> k;
		if(cin.eof()) {
			break;
		}
		string m, c;
		cin >> m >> c;
		run(k, m, c);
	}
	return 0;
}
