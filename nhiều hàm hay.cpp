#include <bits/stdc++.h>
using namespace std;
vector<string> b;
vector<string> c;
int n,k;
void bale(int p){
	if(b.size()==k){
		for(int i=0;i<k;i++){
			cout<<b[i]<<" ";
		}cout<<endl;
		return;
	}
	for(int i=p;i<c.size();i++){
		b.push_back(c[i]);
		bale(i+1);
		b.pop_back();
	}
}
int main(){
	cin>>n>>k;
	vector<string> h(n);
	for(int i=0;i<n;i++){
		cin>>h[i];
	}
	set<string> s(h.begin(), h.end());
	c.assign(s.begin(),s.end());
	bale(0);
	return 0;
}