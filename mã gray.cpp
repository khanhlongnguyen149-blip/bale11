#include <bits/stdc++.h>
using namespace std;
int n;

void bale(vector<vector<int>> &b){
for(int i=2;i<=n;i++){
	for(int j=b.size()-1;j>=0;j--){
		b.push_back(b[j]);
	}
	for(int k=0;k<pow(2,i-1);k++){
		b[k].insert(b[k].begin(),0);
	}
	for(int p=pow(2,i-1);p<pow(2,i);p++){
		b[p].insert(b[p].begin(),1);
	}
}
for(int i=0;i<b.size();i++){
	for(int j=0;j<b[i].size();j++){
	cout<<b[i][j];
	}cout<<" ";
	
}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		vector<vector<int>> a;
		a.push_back({0});
		a.push_back({1});		
		bale(a);
		cout<<endl;
	}
	
	
}