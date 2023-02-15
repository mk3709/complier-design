#include<iostream>
using namespace std;
#include<bits/stdc++.h>
string first(map<char,vector<string> > m, char ch){
if(ch=='^' || !(ch>='A' && ch<='Z'))
return ch+"";
string ans="";
for(int i=0;i<m[ch].size();i++){
string s = m[ch][i];
bool checknext=true;
for(int j=0;j<s.length() && checknext;j++){
checknext = false;
if(s[j]=='^' || !(s[j]>='A' && s[j]<='Z')){
if(ans.find(s[j])==string::npos)
ans.push_back(s[j]);
}
else{
string temp = first(m,s[j]);
for(int k=0;k<temp.length();k++){
if(temp[k]=='^')
checknext=true;
else if(ans.find(temp[k])==string::npos)
ans.push_back(temp[k]);
}
if(checknext && j==s.length()-1)
ans.push_back('^');
}
}
}
return ans;
}
string firstofstring(map<char,vector<string> > m, string s){
string ans="";
bool checknext = true;
for(int j=0;j<s.length() && checknext;j++){
checknext = false;
if(s[j]=='^' || !(s[j]>='A' && s[j]<='Z')){
if(ans.find(s[j])==string::npos)
ans.push_back(s[j]);
}
else{
string temp = first(m,s[j]);
for(int k=0;k<temp.length();k++){
if(temp[k]=='^')
checknext=true;
else if(ans.find(temp[k])==string::npos)
ans.push_back(temp[k]);
}
if(checknext && j==s.length()-1)
ans.push_back('^');
}
}
if(ans=="")
return "^";
return ans;
}
string follow(map<char, vector<string> > prod, char start, char ch){
string ans="";
if(start==ch)
ans.push_back('$');
for(map<char, vector<string> >::iterator i=prod.begin();
i!=prod.end(); i++){
for(int j=0;j<i->second.size();j++){
if(i->second[j].find(ch)==string::npos)
continue;
string temp="";
bool parent = false;
for(int a=0;a<i->second[j].length();a++){
parent=false;
if(i->second[j][a]==ch){
if(a==i->second[j].length()-1){
parent=true;
}else{
//cout<<"substr
"<<i->second[j].substr(a,i->second[j].length()-a-1)<<endl;
temp =
firstofstring(prod,i->second[j].substr(a+1,i->second[j].length()-a-1));
//cout<<"temp "<<temp;
for(int k=0;k<temp.length();k++){
if(temp[k]=='^'){
parent=true;
continue;
}
if(ans.find(temp[k])==string::npos)
ans.push_back(temp[k]);
}
}
if(parent){
//to tackle the case when parent is same as
'ch'
if(ch==i->first)
continue;
temp=follow(prod,start,i->first);
for(int k=0;k<temp.length();k++){
if(ans.find(temp[k])==string::npos)
ans.push_back(temp[k]);
}
}
}
}
}
}
return ans;
}
int main(){
map <char, vector<string> > prod;
int n;
cout<<"Enter number of productions : ";
cin>>n;
cout<<"Enter productions : "<<endl;
char start;
for(int i=0;i<n;i++){
char ch;
string s;
cin>>ch;
if(i==0)
start=ch;
cout<<" -> ";
cin>>s;
prod[ch].push_back(s);
}
cout<<"Given grammar is :"<<endl<<endl;
for(map<char, vector<string> >::iterator i=prod.begin();
i!=prod.end(); i++){
cout<<i->first<<" -> ";
for(int j=0;j<i->second.size();j++){
cout<<i->second[j];
if(j!= i->second.size()-1)
cout<<" | ";
}
cout<<endl;
}cout<<"FIRST : "<<endl<<endl;
for(map<char, vector<string> >::iterator i=prod.begin();
i!=prod.end(); i++){
cout<<"FIRST( "<<i->first<<" ) = { ";
string s= first(prod,i->first);
for(int j=0;j<s.length();j++)
if(j!=s.length()-1)
cout<<s[j]<<" , ";
else
cout<<s[j]<<" }";
cout<<endl;
}
cout<<"FOLLOW :"<<endl<<endl;
for(map<char, vector<string> >::iterator i=prod.begin();
i!=prod.end(); i++){
cout<<"FOLLOW( "<<i->first<<" ) = { ";
string s= follow(prod,start,i->first);
for(int j=0;j<s.length();j++)
if(j!=s.length()-1)
cout<<s[j]<<" , ";
else
cout<<s[j]<<" ";
cout<<"}"<<endl;
}
}
