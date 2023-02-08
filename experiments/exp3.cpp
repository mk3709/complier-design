
-----Left Recursion-----
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int n;
    cout<<"\nEnter number of non terminals: ";
    cin>>n;
    cout<<"\nEnter non terminals one by one: ";
    int i;
    vector<string> nonter(n);
    vector<int> leftrecr(n,0);
    for(i=0;i<n;++i) {
            cout<<"\nNon terminal "<<i+1<<" : ";
        cin>>nonter[i];
    }
    vector<vector<string> > prod;
    cout<<"\nEnter 'esp' for null";
    for(i=0;i<n;++i) {
        cout<<"\nNumber of "<<nonter[i]<<" productions: ";
        int k;
        cin>>k;
        int j;
        cout<<"\nOne by one enter all "<<nonter[i]<<" productions";
        vector<string> temp(k);
        for(j=0;j<k;++j) {
            cout<<"\nRHS of production "<<j+1<<": ";
            string abc;
            cin>>abc;
            temp[j]=abc;
            if(nonter[i].length()<=abc.length()&&nonter[i].compare(abc.substr(0,nonter[i].length()))==0)
                leftrecr[i]=1;
        }
        prod.push_back(temp);
    }
    for(i=0;i<n;++i) {
        cout<<leftrecr[i];
    }
    for(i=0;i<n;++i) {
        if(leftrecr[i]==0)
            continue;
        int j;
        nonter.push_back(nonter[i]+"'");
        vector<string> temp;
        for(j=0;j<prod[i].size();++j) {
            if(nonter[i].length()<=prod[i][j].length()&&nonter[i].compare(prod[i][j].substr(0,nonter[i].length()))==0) {
                string abc=prod[i][j].substr(nonter[i].length(),prod[i][j].length()-nonter[i].length())+nonter[i]+"'";
                temp.push_back(abc);
                prod[i].erase(prod[i].begin()+j);
                --j;
            }
            else {
                prod[i][j]+=nonter[i]+"'";
            }
        }
        temp.push_back("esp");
        prod.push_back(temp);
    }
    cout<<"\n\n";
    cout<<"\nNew set of non-terminals: ";
    for(i=0;i<nonter.size();++i)
        cout<<nonter[i]<<" ";
    cout<<"\n\nNew set of productions: ";
    for(i=0;i<nonter.size();++i) {
        int j;
        for(j=0;j<prod[i].size();++j) {
            cout<<"\n"<<nonter[i]<<" -> "<<prod[i][j];
        }
    }
    return 0;
}



-----Left Factoring-----
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;
void reverse(char str[], int length){
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
 
int main()
{
    cout<<"\nEnter number of productions: ";
    int p;
    cin>>p;
    vector<string> prodleft(p),prodright(p);
    cout<<"\nEnter productions one by one: ";
    int i;
    for(i=0;i<p;++i) {
        cout<<"\nLeft of production "<<i+1<<": ";
        cin>>prodleft[i];
        cout<<"\nRight of production "<<i+1<<": ";
        cin>>prodright[i];
    }
    int j;  
    int e=1;
    for(i=0;i<p;++i) {
        for(j=i+1;j<p;++j) {
            if(prodleft[j]==prodleft[i]) {
                int k=0;
                string com="";
                while(k<prodright[i].length()&&k<prodright[j].length()&&prodright[i][k]==prodright[j][k]) {
                    com+=prodright[i][k];
                    ++k;
                }
                if(k==0)
                    continue;
                char* buffer;
                string comleft=prodleft[i];
                if(k==prodright[i].length()) {
                    prodleft[i]+=string(itoa(e,buffer,10));
                    prodleft[j]+=string(itoa(e,buffer,10));
                    prodright[i]="^";
                    prodright[j]=prodright[j].substr(k,prodright[j].length()-k);
                }
                else if(k==prodright[j].length()) {
                    prodleft[i]+=string(itoa(e,buffer,10));
                    prodleft[j]+=string(itoa(e,buffer,10));
                    prodright[j]="^";
                    prodright[i]=prodright[i].substr(k,prodright[i].length()-k);
                }
                else {
                    prodleft[i]+=string(itoa(e,buffer,10));
                    prodleft[j]+=string(itoa(e,buffer,10));
                    prodright[j]=prodright[j].substr(k,prodright[j].length()-k);
                    prodright[i]=prodright[i].substr(k,prodright[i].length()-k);
                }
                int l;
                for(l=j+1;l<p;++l) {
                    if(comleft==prodleft[l]&&com==prodright[l].substr(0,fmin(k,prodright[l].length()))) {
                        prodleft[l]+=string(itoa(e,buffer,10));
                        prodright[l]=prodright[l].substr(k,prodright[l].length()-k);
                    }
                }
                prodleft.push_back(comleft);
                prodright.push_back(com+prodleft[i]);
                ++p;
                ++e;
            }
        }
    }
    cout<<"\n\nNew productions";
    for(i=0;i<p;++i) {
        cout<<"\n"<<prodleft[i]<<"->"<<prodright[i];
    }
    return 0;
}


