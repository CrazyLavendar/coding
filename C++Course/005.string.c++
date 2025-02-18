#include<iostream>
#include<vector>

using namespace std;

int main(){

    // string input = "Hello, what are you doing?";

    // vector<string> parse;

    // int i  = 0;
    // string temp = "";
    // while(true){
    //     if (input[i] == '\0'){
    //         parse.push_back(temp);
    //         temp = "";
    //         break;
    //     }
    //     if (input[i] == ' '){
    //         parse.push_back(temp);
    //         temp = "";
    //         i++;
    //         continue;
    //     }
    //     temp += input[i];
    //     i++;
    // }

    // for (string s : parse){
    //     cout << s << endl;
    // }


    // string name = "VimalKumar";
    // cout << name.substr(2,4) << endl;
    // cout << name.substr(2) << endl;
    // cout << name.find("Kumar") << endl;
    // string s1 = "Vimal", s2 = "Kumar";
    // //cout << strcat(s1,s2);


    // char array

    char c_str[] = "hello";
    c_str[1] = 'w';
    cout << c_str << endl;

    string str = "hello";
    str[1] = 'w';
    cout << str << endl;

    char * p_str = "hello";
    // p_str[1] = 1; /// error
    cout << p_str << endl;


    cout << strlen(c_str) << endl;
    cout << str.length() << endl;
    cout << strlen(p_str) << endl;

    cout << sizeof(c_str) << endl;
    cout << sizeof(str) << endl;
    cout << sizeof(p_str) << endl;


    string str2 = "hwllo";
    char c_str2[] = "hwllo";
    char * p_str2 = "hello";

    cout << strcmp(c_str, c_str2) << endl;
    cout << str.compare(str2) << endl;
    cout << strcmp(p_str, p_str2) << endl;




    return 0;
}