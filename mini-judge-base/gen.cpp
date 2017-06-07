#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){

	vector<int> args;

	for(int i=1;i<argc;i++){
		int x = atoi(argv[i]);
		args.push_back(x);
	}
	
	if(args.size()>0){
		cout<<args[0];
		for(int i=1;i<args.size();i++)
			cout<<' '<<args[i];
		cout<<'\n';
	}
	
	return 0;
}
