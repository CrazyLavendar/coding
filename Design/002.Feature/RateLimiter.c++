#include<iostream>
#include<vector>
#include<unordered_map>
#include<chrono>

using namespace std;


class API{
    int data;
    chrono::duration<chrono::microseconds> timeStamp;
};

class Client{
public:
    string name;
    int Limit;
    int id;
    vector<API> apiList;
};

// class ClientData{

// };


class RateLimiter{

unordered_map<string, Client> map_;


public:
    static RateLimiter g_RateLimiter;
    
    void addClient(string name, int Limit){

    }

    static RateLimiter* getInstance(){
        return &g_RateLimiter;
    }

    void callAPI(string name){
        // validate
        Client client = map_[name];
        //allow
        if(client.Limit > client.apiList.size()){
            // allow
        }else{
            API api = client.apiList[client.apiList.size() -1 - client.Limit];
            
            // int milliseconds =  currTimeInMilliseconds - api.timeStamp ;
            int elapsedTime = chrono::system_clock::now() - api.timeStamp;

            if (milliSeconds > 1000){
                // allow
            }
            else{

            }
        }
    }
};


RateLimiter RateLimiter::g_RateLimiter;


int main(){
    RateLimiter* instance = RateLimiter::getInstance();
    return 0;
}