#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

//Created By Kobe on 2019/4/11
using namespace std;


string KeyWord[] = {"if","else","do","while","int","double","bool","struct"};
map <int,string> relatmap = {
        {2,"if"},
        {3,"else"},
        {4,"do"},
        {5,"while"},
        {6,"int"},
        {7,"double"},
        {8,"bool"},
        {9,"struct"},
        {10,"="},
        {11,"*"},
        {12,"=="},
        {13,"!="},
        {14,"++"},
        {15,"="},
        {16,";"},
        {17,"("},
        {18,")"},
        {19,"{"},
        {20,"}"},
};
char Operate[] = {'+','*','=','!'};
char Divide[] = {'=',';','(',')','{','}'};
char Space[] = {' ','\t','\r','\n'};

map <string, string> tokenmap = {
        {"ADD",                "+"},
        {"MUL",                "*"},
        {"GREATER_THAN",       ">"},
        {"LESS_THAN",          "<"},
        {"EQUAL",              "="},
        {"GREATER_THAN_EQUAL", ">="},
        {"LESS_THAN_EQUAL",    "<="},
        {"EQUAL_EQUAL",        "=="},
        {"AND",                "&&"},
        {"OR",                 "||"},
        {"NOT",                "!"},
        {"NOT_EQUAL",          "!="},
        {"SLP",                "("},
        {"SRP",                ")"},
        {"MLP",                "["},
        {"MRP",                "]"},
        {"LP",                 "{"},
        {"RP",                 "}"},
        {"INC",                "++"},
        {"DEC",                "--"},
        {"SEMI",               ";"},
        {"COM",                ","},
        {"LSH",                "/"},
        {"RSH",                "\\"},
};

vector <int> list1 ;
vector <string> list2 ;
vector <string> table;
int cnt = 0;

bool IsKeyword(string keyword){
    //int length = KeyWord->size();  //Wrong!
    int length = sizeof(KeyWord)/sizeof(KeyWord[0]);
    for(int i=0;i<length;i++){
        if(keyword == KeyWord[i])
            return true;
    }
    return false;
}

bool IsOperate(char str){
    int length = sizeof(Operate)/ sizeof(Operate[0]);
    for(int i=0;i<length;i++){
        if(str == Operate[i])
            return true;
    }
    return false;
}

bool IsDivide(char ch){
    int length = sizeof(Divide)/ sizeof(Divide[0]);
    for(int i=0;i<length;i++){
        if(ch == Divide[i])
            return true;
    }
    return false;
}

bool IsSpace(char ch){
    int length = sizeof(Space)/ sizeof(Space[0]);
    for(int i=0;i<length;i++){
        if(ch == Space[i])
            return true;
    }
    return false;
}

bool IsLetter(char ch){
    if((ch>='A' && ch<='Z') ||
       (ch>='a' && ch<='z'))
        return true;
    return false;
}

bool IsDigit(char ch){
    if(ch>='0' && ch<='9') return  true;
    return false;
}

string ScanByChar()
{
    fstream file;
    string str = "";
    char c;
    file.open("C:\\Code\\C\\clion\\demo\\test.txt",ios::in);
    file>>noskipws;
    if (!file.is_open()) {
        cout << "Could not find the file\n";
        exit(EXIT_FAILURE);
    }
    while(!file.eof())
    {
        file >> c;
        str += c;
    }
    file.close();
    return str;
}

void ScanAnalyse(){
    cout << "into scan..." << endl;
    string str = ScanByChar();
    int pos = 0;
    int length = str.length();
    //cout << "str:\n" << length << endl << str << endl;
    char ch ;
    string buffer = "";
    int state = 0;
    while( pos<length ){
        ch = str[pos];
        buffer = "";
        if(IsSpace(ch)) { pos++; }
        else if(IsDivide(ch)){
            buffer += ch;
            for (map<string, string>::iterator it = tokenmap.begin();
            it != tokenmap.end(); it++) {
                if (it->second == buffer) {
                    cout << buffer + "  <" + it->first + ", _>" << endl;

                }
            }
            for (map<int , string>::iterator it = relatmap.begin();
                 it != relatmap.end(); it++) {
                if (it->second == buffer) {
                    list1.push_back(it->first);
                    list2.push_back("NONE");
                }
            }
            //cout << ch + " <Separator  "  << endl;
            pos++;
        }
        else if(IsOperate(ch)){
            buffer += ch;
            pos++;
            if( IsOperate(ch=str[pos]) && pos<length ){
                buffer += ch;
                pos++;
            }else{
            }
            for (map<string, string>::iterator it = tokenmap.begin();
                 it != tokenmap.end(); it++) {
                if (it->second == buffer) {
                    cout << buffer + "  <" + it->first + ", _>" << endl;
                }
            }
            for (map<int , string>::iterator it = relatmap.begin();
                 it != relatmap.end(); it++) {
                if (it->second == buffer) {
                    list1.push_back(it->first);
                    list2.push_back("NONE");
                }
            }
            //cout << "Operator  " << buffer << endl;
        }
        else if(IsDigit(ch)){
            state = 1;
            buffer += ch;
            pos++;
            bool flag = true;
            while( !IsSpace(ch=str[pos]) && pos<length && flag ){
                buffer += ch;
                switch (state){
                    case 1:
                        if(IsDigit(ch)) state = 1;
                        else if(ch == '.') state = 2;
                        else if(ch == 'E'|| ch == 'e') state = 4;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    case 2:
                        if(IsDigit(ch)) state = 3;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    case 3:
                        if(IsDigit(ch)) state = 3;
                        else if(ch == 'E'|| ch == 'e') state = 4;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    case 4:
                        if(ch == '+' || ch == '-') state = 5;
                        else if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    case 5:
                        if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    case 6:
                        if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            buffer.erase(buffer.end()-1);
                            flag = false;
                        }
                        break;
                    default:
                        pos--;
                        flag = false;
                        buffer.erase(buffer.end()-1);
                        cout << "error!" << endl;
                        break;
                }
                pos++;
            }
            cout << buffer+" <CONST,"+buffer+">" << endl;

            list1.push_back(9);
            list2.push_back(to_string(cnt));
            cnt++;
            table.push_back(buffer);


        }
        else if(IsLetter(ch) || ch == '_'){
            buffer += ch;
            pos++;
            while( !IsSpace(ch=str[pos++]) && pos<length ){
                if(IsLetter(ch) || ch=='_' || IsDigit(ch)){
                    buffer += ch;
                }else{
                    //fseek(fp,-1L,SEEK_CUR);
                    //fp.seekg(0,ios::cur);
                    pos--;
                    break;
                }
            }
            if(IsKeyword(buffer)){
                 cout << buffer+" <" + buffer + ",_>" << endl;
                for (map<int , string>::iterator it = relatmap.begin();
                     it != relatmap.end(); it++) {
                    if (it->second == buffer) {
                        list1.push_back(it->first);
                        list2.push_back("NONE");
                    }
                }
                //<<transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper)
            }
            else{
                cout << buffer+" <IDN,"+buffer+">" << endl;

                int i;
                for(i=0;i<table.size();i++){
                    if(buffer == table[i]){
                        break;
                    }

                }
                list1.push_back(1);
                list2.push_back(to_string(cnt));

                if(i==table.size()){
                    cnt++;
                    table.push_back(buffer);
                }

            }           
        }
    }
}


int main() {
    ScanAnalyse();

    int length = list1.size();
    cout << "token:" <<endl;
    for(int i=0;i<length;i++){
        //string str = "";
        cout << "("<<list1[i]<<","+list2[i]+") , " << endl;
    }
    int length2 = table.size();
    cout << "table:" <<endl;
    for(int i=0;i<length2;i++){
        cout << table[i]+",";
    }
    return 0;
}