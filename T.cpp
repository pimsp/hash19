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

struct photo{
	bool hor;
	vi tags;
};

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }


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
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
