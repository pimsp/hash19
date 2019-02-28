#include<bits/stdc++.h>

#define x first
#define y second

using namespace std;

int main() {
	int n;
	cin >> n;
	unordered_map<string, int> H;

	map<int, int> taglens;

	while (n--) {
		char ch;
		cin >> ch;
		int m;
		cin >> m;
		taglens[m]++;
		for (int i = 0; i < m; i++) {
			string x;
			cin >> x;
			H[x]++;
		}
	}
	cout << H.size() << endl;

	map<int, int> freq;
	for (auto pr : H) freq[pr.second]++;

	cout << "Tag frequencies: " << endl;
	for (auto pr : freq) cout << pr.x << "x: " << pr.y << ", ";
	cout << endl;

	cout << "Tag lengths: " << endl;
	for (auto pr : taglens) cout << pr.x << "x: " << pr.y << ", ";
	cout << endl;
	return 0;
}
