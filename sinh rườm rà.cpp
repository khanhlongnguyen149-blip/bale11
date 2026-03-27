#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	string s;
	vector<long long> a;
	cin>>t;
	
	while(t--){
		int m;
		cin>>m;
		a.clear();
		cin>>s;
	//	cout<<p<<" ";
		for( int i=0; i<s.length();i++){
			a.push_back(s[i]-'0');
		}
		int p=a.size()-1;
		while(p!=0&&a[p-1]>=a[p]){
			p--;
		}
		if(p==0){
			cout<<m<<" BIGGEST"<<endl;
		}else{
	
		int e=p-1;
		while(p<=a.size()-1&&a[p]>=a[e]){
			p++;
		}
	
		swap(a[e],a[p-1]);
	for(int i=e+1;i<a.size()-1;i++){
		for(int j=i+1;j<a.size();j++){
			if(a[j]<a[i]) swap(a[j],a[i]);
		}
	}
		
		cout<<m<<" ";
		for(int i=0;i<a.size();i++){
			cout<<a[i];
		}cout<<endl;}
	}	}

