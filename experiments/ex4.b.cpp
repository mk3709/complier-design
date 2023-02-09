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
