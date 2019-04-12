#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

//Created By Kobe on 2019/4/11
using namespace std;


string KeyWord[] = {"if","else","void","return","while","for","do",
                    "int","char","double","float","switch","case","main"};
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


void ScanAnalyse(FILE *fp){
    cout << "into scan..." << endl;
    char ch ;
    string buffer = "";
    int state = 0;
    while( (ch=fgetc(fp)) != EOF ){
        buffer = "";
        if(IsSpace(ch)) {}
        else if(IsDivide(ch)){
            cout << "Separator  " << ch << endl;
        }
        else if(IsOperate(ch)){
            buffer += ch;
            while(IsOperate(ch=fgetc(fp))){//such as <=
                buffer += ch;
            }
            cout << "Operator  " << buffer << endl;
        }
        else if(IsDigit(ch)){
            state = 1;
            buffer += ch;
            while( !IsSpace( ch=fgetc(fp) ) ){
                buffer += ch;
                switch (state){
                    case 1:
                        if(IsDigit(ch)) state = 1;
                        else if(ch == '.') state = 2;
                        else if(ch == 'E'|| ch == 'e') state = 4;
                        break;
                    case 2:
                        if(IsDigit(ch)) state = 3;
                        break;
                    case 3:
                        if(IsDigit(ch)) state = 3;
                        else if(ch == 'E'|| ch == 'e') state = 4;
                        break;
                    case 4:
                        if(ch == '+' || ch == '-') state = 5;
                        else if(IsDigit(ch)) state = 6;
                        break;
                    case 5:
                        if(IsDigit(ch)) state = 6;
                        break;
                    case 6:
                        if(IsDigit(ch)) state = 6;
                        break;
                    default:
                        cout << "error!" << endl;
                        break;
                }
            }
            cout << "Number  " << buffer << endl;
        }
        else if(IsLetter(ch) || ch == '_'){
            buffer += ch;
            while( !IsSpace(ch=fgetc(fp)) ){
                //int cur_offset = ftell(fp);
                if(IsLetter(ch) || ch=='_' || IsDigit(ch)){
                    buffer += ch;
                }else{
                    //printf("pre_offset = %d\n", ftell(fp));
                    //fseek(fp,-1L,SEEK_CUR);
                    //printf("pro_offset = %d\n", ftell(fp));
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
    FILE *fp;
    if( (fp = fopen("C:\\Code\\C\\clion\\demo\\test.txt","r+")) != NULL ){
        ScanAnalyse(fp);
        fclose(fp);
    }
    else{
        cout << "Can't open the file!" << endl;
    }

    return 0;
}