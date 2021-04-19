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
	map <char, string> symblist;
	symblist['}'] = "curly_bracket_closed";symblist['{'] = "curly_bracket_opened";symblist['['] = "square_bracket_opened";symblist[']'] = "square_bracket_closed";symblist['('] = "parenthesis_opened";symblist[')'] = "parenthesis_closed";
	symblist[','] = "comma";symblist['+'] = "unary_plus";symblist['-'] = "unary_minus";symblist['*'] = "unary_multiplication";symblist['/'] = "unary_divition";
	symblist['.'] = "dot";symblist[';'] = "semiclone";symblist['!'] = "not";symblist['>'] = "gt";symblist['<'] = "lt";symblist['='] = "equal";
	string txt;
	ifstream readfile("rfile.txt");
	ofstream outfile("outfiles.txt");
	int state = 0;
  	string bac;
 	vector<string> ptline;
    vector<string> starr;
	if(readfile.is_open()){
    int pos = 1;
	int spos = 1;
	while(getline(readfile, txt)){
      string sline = "";
			for(int i = 0; i < (int)txt.length(); i++){
				if(txt[i] == '/' && txt[i + 1] == '/'){
					break;
				}else if(txt[i] == '/' && txt[i+1] == '*'){
					state = 1;
				}else if(txt[i] == '*' && txt[i +1] == '/'){
					i++;
					state = 0;
				}else if (state == 0){
          sline.pb(txt[i]);
					outfile << txt[i];
				};
			}	
			outfile << nl;
      //# Partition table will go here
      	string abc="";
		    int sflag = 0;
			for(int i = 0; i <sline.length(); i++){
				if(sflag){
					if(sline[i] == ',' || sline[i]==';'){
						sflag = 0;
						continue;
					}
				}
				if(sline[i] == '=')	{
					sflag = 1;
				}
				else{
					abc.pb(sline[i]);
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
     	     		string ptl ="";
					ptl += to_string(pos);ptl.pb('.');ptl+=x;ptl.pb('=');ptl+=pr.second;ptl.pb('\n');
					ptline.pb(ptl);
					pos++;
				};
			};

		//#Partitation table will end here

	  	//# symbol table code here
		for(int i = 0; i < sline.size(); i++){
		string prline = "";
			if(symblist[sline[i]].size()){
				prline+=to_string(spos);prline+=". ";prline.pb(sline[i]);prline+=" = ";prline+=symblist[sline[i]];prline.pb('\n');
				spos++;
				starr.pb(prline);
			}
		}
		//# symbol talbe code ends here
		};
		// write to files.
		for(auto x: ptline) outfile << x;
		outfile << nl;
		for(auto x: starr) outfile << x;
		
	};
	readfile.close();
	outfile.close();
	return 0;
};





