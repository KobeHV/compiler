#include <iostream>
#include <string>
#include <fstream>

//Created By Kobe on 2019/4/11
using namespace std;


string KeyWord[] = {"if","else","void","return","while","for","do",
                    "int","char","double","float","switch","case","main","struct"};
char Operate[] = {'+','-','*','/','>','<','=','!'};
char Divide[] = {';',',','{','}','[',']','(',')'};
char Space[] = {' ','\t','\r','\n'};


bool IsKeyword(string keyword){
    //int length = KeyWord->size();  //Wrong!
    int length = sizeof(KeyWord)/sizeof(KeyWord[0]);
    for(int i=0;i<length;i++){
        if(keyword == KeyWord[i])
            return true;
    }
    return false;
}

bool IsOperate(char ch){
    int length = sizeof(Operate)/ sizeof(Operate[0]);
    for(int i=0;i<length;i++){
        if(ch == Operate[i])
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
    cout << "str:\n" << length << endl << str << endl;
    char ch ;
    string buffer = "";
    int state = 0;
    while( pos<length ){
        ch = str[pos];
        buffer = "";
        if(IsSpace(ch)) { pos++; }
        else if(IsDivide(ch)){
            cout << "Separator  " << ch << endl;
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
            cout << "Operator  " << buffer << endl;
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
                            flag = false;
                        }
                        break;
                    case 3:
                        if(IsDigit(ch)) state = 3;
                        else if(ch == 'E'|| ch == 'e') state = 4;
                        else{
                            pos--;
                            flag = false;
                        }
                        break;
                    case 4:
                        if(ch == '+' || ch == '-') state = 5;
                        else if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            flag = false;
                        }
                        break;
                    case 5:
                        if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            flag = false;
                        }
                        break;
                    case 6:
                        if(IsDigit(ch)) state = 6;
                        else{
                            pos--;
                            flag = false;
                        }
                        break;
                    default:
                        pos--;
                        flag = false;
                        cout << "error!" << endl;
                        break;
                }
                pos++;
            }
            cout << "Number  " << buffer << endl;
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
                 cout << "KeyWord  " << buffer << endl;
            }
            else{
                cout << "Identifier  " << buffer << endl;
            }           
        }
    }
}


int main() {
    ScanAnalyse();
    return 0;
}