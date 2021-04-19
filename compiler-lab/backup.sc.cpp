#include <bits/stdc++.h>
#include <fstream>
#include <regex>
#define nl "\n"
#define pb push_back
#define eb emplace_back
using namespace std;
typedef long long ll;
string arr[4] = {"int", "float", "double", "char"};

vector<string> splt(string st){
	vector<string> vi;
	string word="";
	for(auto x: st){
		if(x == '\n' ||x == ' ' || x == ',' || x == ';' || x== '='){
			if(word!=""){
				vi.pb(word);
			}
			word = "";
		}else{
			word.pb(x);
		}
	}
	return vi;
};
pair<bool, string> isDatatype(string word){
	pair<bool, string> rt(false, "");
	for(int i = 0; i < 4; i++){
		if(word == arr[i]){
			rt.first = true;
			rt.second = word;
			return rt;
		}

	};	  
	return rt;
};

int main(int argc, char ** argv){
	ios::sync_with_stdio(false);
	string txt;
	ifstream readfile("rfile.txt");
	ofstream outfile("outfiles.txt");
	int state = 0;
	if(readfile.is_open()){
		while(getline(readfile, txt)){
			for(int i = 0; i < (int)txt.length(); i++){
				if(txt[i] == '/' && txt[i + 1] == '/'){
					break;
				}else if(txt[i] == '/' && txt[i+1] == '*'){
					state = 1;
				}else if(txt[i] == '*' && txt[i +1] == '/'){
					i++;
					state = 0;
				}else if (state == 0){
					outfile << txt[i];
				};
			}		 
			outfile << nl;
		};
	};
	readfile.close();
	outfile.close();
	ifstream outwc("outfiles.txt");
	string bac;
	if(outwc.is_open()){
		int pos = 1;
		while(getline(outwc, bac)){
			string abc="";
			for(int i = 0; i <bac.length(); i++){
				if(bac[i] == '=')	{
					break;
				}
				else{
					abc.pb(bac[i]);
				};
			};
			vector<string> wlist = splt(abc);
			pair<bool, string> pr;
			for(auto x: wlist){
				 pr= isDatatype(x);
				 if(pr.first)break;
			};
			for(auto x: wlist){
				if(pr.first && pr.second != x){
					cout << pos << "." << x << "=" << pr.second << nl;	
					pos++;
				};
			};
		};
	};
	return 0;
};





