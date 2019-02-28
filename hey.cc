#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rs resize
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for (auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }

vector<pair<int,pair<int,int>>> scores;

struct dsu {
	vi par, rnk;
	dsu(int n) : par(n, -1), rnk(n, 0) {}
	int find(int i) { return
		par[i] < 0 ? i : par[i] = find(par[i]); }
	void unite(int a, int b) {
		if ((a = find(a)) == (b = find(b))) return;
		if (rnk[a] < rnk[b]) swap(a, b);
		if (rnk[a] == rnk[b]) rnk[a]++;
		par[a] += par[b]; par[b] = a;
	}
};
/*
ll score(vi t1, vi t2){ // neemt gesorteerdheid aan
	ll i1 = 0, i2 = 0;
	ll s1 = 0, s2 = 0, s3 = 0; // venn diagram ( s_1 (s2_ ) s_3 )
	while(true){
		if(i1 == t1.size()){
			s3 += t2.size() - i2;
			break;
		}
		if(i2 == t2.size()){
			s1 += t1.size() - i1;
			break;
		} 
		if(t1[i1] == t2[i2]){
			s2++;
			i1++;
			i2++;
			continue;
		}
		if(t1[i1] < t2[i2]){
			s1++;
			i1++;
			continue;
		}
		s2++;
		i2++;
		continue;
	}
	return min(s1,min(s2,s3));
}

typedef vector<photo> vp;
vp dat;*/

vector<ii> matched;



struct photo {
	bool hor;
	int id[2];
	vi tags;
};

vector<photo> photos;
vector<vi> occ;
vector<vii> adj;

int score(int a, int b) {
	int na = 0, nb = 0, nab = 0;

	unordered_map<int, bool> has;
	for (int t : photos[b].tags) has[t] = false;

	for (int t : photos[a].tags) {
		if (has.find(t) == has.end()) {
			na++;
			has[t] = true;
		} else
			nab++;
	}
	for (auto pr : has) if (!pr.y) nb++;
	return min(min(na, nb), nab);
}

void run() {
	srand(time(0));
	int n;
	cin >> n;

	photos.clear();
	vector<photo> vphotos;

	unordered_map<string, int> str_lookup;
	int nr_strs = 0;

	REP(i, n) {
		char dir;
		int m;
		cin >> dir >> m;
		photo ph = {dir == 'H', {i,-1}, {}};
		REP(j, m) {
			string s;
			cin >> s;
			if (str_lookup.find(s) == str_lookup.end())
				str_lookup[s] = ++nr_strs;
			ph.tags.pb(str_lookup[s]);
		}
		sort(all(ph.tags));
		( ph.hor ? photos : vphotos ).pb( ph );
	}

	random_shuffle( all(vphotos) );
	for( ll i = 0; i+1 < vphotos.size(); i += 2 ) {
		vector<int> x( vphotos[i].tags.size() + vphotos[i+1].tags.size() );
		auto itr = set_union( vphotos[i].tags.begin(), vphotos[i].tags.end(), vphotos[i+1].tags.begin(), vphotos[i+1].tags.end(), x.begin() );
		x.resize(itr-x.begin());
		photos.pb( { false, { vphotos[i].id[0], vphotos[i+1].id[0] }, x } );
	}
	n = photos.size();

	occ.resize(nr_strs + 1);
	REP(i, n) {
		for (int j : photos[i].tags) occ[j].pb(i);
	}

	// adj.resize(n);
	REP(i, n) {
		vi others;
		for (int j : photos[i].tags) for (int k : occ[j]) others.pb(k);
		sort(all(others));
		others.resize(unique(all(others)) - others.begin());
		for (int j : others)
			// adj[i].eb(j, score(i, j));
			scores.eb(score(i, j), make_pair(i,j));
	}

/*
void run()
{
	ll n;
	cin >> n;
	dat.rs(n);
	rep(i,0,n){
		char c;
		cin >> c;
		dat[i].hor = (c == 'H');
		ll t;
		cin >> t;
		rep(j,0,t){
			string s;
			cin >> s;
			dat[i].tags.pb(hash<string>()(s));
			sort(all(dat[i].tags));
		}
	}
	ll t = n/2;
	rep(i,0,t){
		rep(j,0,i){
			int s = score(dat[i].tags,dat[j+t].tags);
			if( s > 0 )
				scores.eb( s, make_pair( i, j ) );
		}
		if( i % 100 == 0 )
			cerr << i << endl;
	}*/
	cerr << "--------------------------------" << endl;
	sort(all(scores));
	matched.resize(n, make_pair(-1,-1));
	dsu chains(n);
	ll TS = 0;
	while( scores.size() > 0 ) {
		ll ind = max(0ll,ll(scores.size()-1-(rand()%10)));
		ll u[2]= {scores[ind].second.first,scores[ind].second.second };
		if( chains.find(u[0]) != chains.find(u[1]) and matched[u[0]].first == -1 and matched[u[1]].first == -1 ) {
			ll a[2] = {0,0};
			rep(i,0,2) ( ( matched[u[i]].second == -1 ) ? matched[u[i]].second : matched[u[i]].first ) = u[!i];
			chains.unite(u[0],u[1]);
			TS += scores[ind].first;
		}
		scores.erase( scores.begin()+ind );
		if( scores.size() % 1000 == 0 ) cerr << scores.size() << endl;
	}
	vector<int> seen(n,false);
	vector<int> order;
	order.reserve(n);
	rep(i,0,n) {
		if( not seen[i] ) if( matched[i].first == -1 ) {
			ll a = i;
			ll b = matched[i].second;
			order.pb(a);
			seen[a] = true;
			while( b != -1 ) {
				seen[b] = true;
				order.pb(b);
				ll c = matched[b].first == a ? matched[b].second : matched[b].first;
				a = b;
				b = c;
			}
		}
	}
	cerr << "-------------------------------------------" << endl;
	cerr << TS << endl;
	cout << n << endl;
	rep(i,0,n) {
		cout << photos[order[i]].id[0];
		if( not photos[order[i]].hor ) {
			cout << " " << photos[order[i]].id[1];
		}
		cout << endl;
	} 
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
