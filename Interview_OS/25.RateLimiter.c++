#include<iostream>
#include<thread>
#include<mutex>

class Client;

class RateLimiter{
private:
    map<int, ClientState> clientMp;
public:

    void processURL(int id){
        ClientState c = clientMp[id];
    }



};

class Client{
    string name;
    string id;

    void hitURL(){

    }
};

int main(){

    return 0;
}
