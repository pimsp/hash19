#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
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

struct photo {
	bool hor;
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

void read_photos() {
	int n;
	cin >> n;

	photos.clear();

	unordered_map<string, int> str_lookup;
	int nr_strs = 0;

	REP(i, n) {
		char dir;
		int m;
		cin >> dir >> m;
		photos.pb({dir == 'H', {}});
		REP(j, m) {
			string s;
			cin >> s;
			if (str_lookup.find(s) == str_lookup.end())
				str_lookup[s] = ++nr_strs;
			photos.back().tags.pb(str_lookup[s]);
		}
	}

	occ.resize(nr_strs + 1);
	REP(i, n) {
		for (int j : photos[i].tags) occ[j].pb(i);
	}

	adj.resize(n);
	REP(i, n) {
		vi others;
		for (int j : photos[i].tags) for (int k : occ[j]) others.pb(k);
		sort(all(others));
		others.resize(unique(all(others)) - others.begin());
		for (int j : others)
			adj[i].eb(j, score(i, j));
	}

	int nscore = 0;

	int st = rand() % n;
	vector<bool> used(n, false);
	used[st] = true;
	int nleft = n-1;

	vector<int> answer = { st };

	while (nleft--) {
		int best = -1, bestscore = -1;
		for (ii j : adj[st]) {
			if (used[j.x]) continue;
			if (j.y > bestscore || (j.y == bestscore && (rand() % 2))) {
				bestscore = j.y;
				best = j.x;
			}
		}
		if (best < 0) {
			// take a random one
			bestscore = 0;
			best = rand() % n;
			while (used[best]) best = rand() % n;
		}
		assert(!used[best]);

		nscore += bestscore;
		st = best;
		used[st] = true;

		answer.pb(st);
	}
	cout << nscore << endl;

	ofstream out("output.out");
	out << answer.size() << endl;
	for (int i  :answer) out << i << endl;
}

void run()
{
	read_photos();
}

int main()
{
	srand(time(NULL));

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
