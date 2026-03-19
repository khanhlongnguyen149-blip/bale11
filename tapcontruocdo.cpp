#include <bits/stdc++.h>
using namespace std;
int a[1000];
int n,k;
void in(){
	for(int u=k-1;u>=0;u--){
		cout<<n-u<<" ";
	}cout<<endl;
}
void bale(){
	int i=k-1;
	while(i>0&&(a[i]-a[i-1])==1){
		i--;
		
		}
		if(i==0&&a[i]==1){
			in();
}else{

	a[i]--;
	for(int j=i+1;j<k;j++){
		a[j]=n+1-k+j;
	}for(int p=0;p<k;p++){
		cout<<a[p]<<" ";
	}cout<<endl;
	}}
int main(){
		int t;
		cin>>t;
		while(t--){
			cin>>n>>k;
			for(int r=0;r<k;r++){
				cin>>a[r];
			}bale();
		}return 0;
	}
