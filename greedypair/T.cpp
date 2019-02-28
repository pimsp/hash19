#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for (auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)
#define rs resize

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }

struct photo{
	bool hor;
	vi tags;
};

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

vp dat;


const ll MAXN = 50000;
const ll INF = (1LL << 60);
vvi a(MAXN + 1, vi(MAXN + 1)); // matrix, 1-based

vi minimum_assignment(ll n, ll m) { // n rows, m columns. Resultaat match p[j],j
	vi u(n + 1), v(m + 1), p(m + 1), way(m + 1);
	for (ll i = 1; i <= n; i++) {
		p[0] = i;
		ll j0 = 0;
		vi minv(m + 1, INF);
		vector<char> used(m + 1, false);
		do {
			used[j0] = true;
			ll i0 = p[j0], delta = INF, j1;
			for (ll j = 1; j <= m; j++)
				if (!used[j]) {
					ll cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, way[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
			for (ll j = 0; j <= m; j++) {
				if(used[j]) u[p[j]] += delta, v[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);
		do {
			ll j1 = way[j0]; p[j0] = p[j1]; j0 = j1;
		} while (j0);
	}
	// column j is assigned to row p[j]
	return p;
}

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
		rep(j,0,t){
			a[i+1][j+1] = score(dat[i].tags,dat[j+t].tags);
		}
	}
	vi p = minimum_assignment(t,t);
	cout << 2*t << endl;
	rep(i,0,t){
		cout << p[i+1]-1 << endl;
		cout << i + t << endl;
	}

}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
