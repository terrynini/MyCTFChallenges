#include <iostream>
#include <string>

struct node{
    node* prev;
    node* next;
    unsigned long long  idx;
};

using namespace std;
string check = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 511847092 0 0 0 0 0 0 48 0 0 0 0 0 0 0 40984114273074 0 0 0 0 0 280 0 0 0 0 0 0 26022 26 0 0 0 0 0 0 2035 0 0 0 0 0 0 15 0 0 0 0 0 0 53 0 0 0 0 0 0 47 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 42350 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 40 0 0 0 0 0 0 29201 0 0 0 0 0 0 805 0 0 0 0 0 1 939 0 0 0 0 0 0 13 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 7739889 0 0 0 0 0 0 1251 0 0 0 0 0 0 45 0 0 0 0 0 0 2950300 0 0 0 0 0 2 23 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 54 0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 0 0 55 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ";

int main(){
    node* ring = new node;
    ring->prev = ring;
    ring->next = ring;
    ring->idx = 0;
    node* work = ring;

    for(int i = 0 ; i < 313 ; i ++){
        node* temp = new node;
        temp->idx = 0;
        temp->next = work->next;
        temp->prev = work;
        work->next = temp;
        work = temp;
    }
    cout << "Only state alchemists are entitled to know the forbidden secret, show me that you are" << endl;

    string input;
    cin >> input;
    //AIS3{4ll_humonculus_h4v3_a_ur0b0r0s_m4rk_0n_the1r_b0dy}
    int idx = 1;
    for(auto c:input){
        unsigned int chr = c;
        work = ring;
        for(unsigned int i = 0 ; i < chr*7 ; i++)
            work = work->next;
        work->idx = (work->idx<<6)+idx;
        idx++;
    }
    string seq = ""; 
    work = ring;
    for(int i = 0 ; i < 313 ; i++){
        seq += to_string(work->idx) + " "; 
        work = work->next;
    }
    cout << seq << endl;
    if(seq == check)
       cout << "Right! The secret is " << input << ",only state alchemists are able to understand the puzzle";
    else
       cout << "No! Imposter! I'm gonna transmute you and a chiwawa into a Human Chimera..."; 
}
