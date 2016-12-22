#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
using namespace std;
class node
{
public:
    char chr;
    int cnt;
    node* left;
    node* right;
    node(char c=NULL,int n=0)
    {
        chr=c,cnt=n,left=NULL,right=NULL;
    }
};
struct compare
{
    bool operator()(const node* l, const node* r)
    {
        return (l->cnt> r->cnt);
    }
};

//data_structure
map<char,int> count;
priority_queue<node,vector<node*>,compare> minheap;
set<char> charactors;
map<char,string> hufman;
//


//function
void countchar(string &inp);
void makehuffman();
void mkmaphuffman(node *,string code);
void printhuffmancode(string &inp);
//

int main() {
    string input;
    cin >> input;
    countchar(input);
    makehuffman();
    mkmaphuffman(minheap.top(),"");
    printhuffmancode(input);

    return 0;
}


void countchar(string &inp)
{
    for(int i=0;i<inp.length();i+=8)
    {
        string help;
        for (int j = i; j < i+8; ++j)help=help+inp[j];
        count[char(stoi(help, nullptr,2))]++;
        charactors.insert(char(stoi(help, nullptr,2)));
    }

    //make first minheap tree
    set<char>::iterator it;
    for(it=charactors.begin();it!=charactors.end();it++){
        minheap.push(new node(*it,count[*it]));
    }
}

void makehuffman()
{
    node *l,*r,*parent;
    while (minheap.size()>1) {
        r = minheap.top();
        minheap.pop();
        l = minheap.top();
        minheap.pop();
        parent=new node(0,l->cnt+r->cnt);
        parent->left=l;
        parent->right=r;
        minheap.push(parent);
    }
}

void mkmaphuffman(node* parent,string code){
    if(!parent)
        return;
    if(parent->chr!=0)
    {
        hufman[parent->chr]=code;
        cout<<parent->chr<<"  :  "<<code<<endl;
    } else
    {
        mkmaphuffman(parent->left,code+"0");
        mkmaphuffman(parent->right,code+"1");
    }

}
void printhuffmancode(string &inp)
{
    string out="";
    for(int i=0;i<inp.length();i+=8)
    {
        string help;
        for (int j = i; j < i+8; ++j)help=help+inp[j];
        out=out+hufman[char(stoi(help, nullptr,2))];
    }
    cout<<out<<endl;

}