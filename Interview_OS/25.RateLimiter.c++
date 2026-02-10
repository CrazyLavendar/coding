#include<iostream>
#include<string>

using namespace std;


class Client;

struct ClientState{
    Client c;
    ll timestamp; // last time stamp
    int token; // number of token left;
}

class RateLimiter{
private:
    map<int, ClientState> clientMp;
    int curr_id;
public:

    RateLimiter(){
        curr_id;
    }

    void processURL(int id, string URL){
        if(clientMp.count(id) == 0){
            // error no such client
            return;
        }

        ClientState c = clientMp[id];
        
        long currTimestamp = now.time_since_epoch(); // convert to seconds;

        if(c.token > 0 && currTimestamp - c.timestamp < 60){
            c.token--;
            clientMp[id] = c;
        }
        else if (c.token == 0 && currTimestamp - c.timestamp < 60){
            // Dont allow URL
            return;
        }
        else{
            // refresh timestamp;
            c.token = 99;
            clientMp[id] = c; // update
        }
        // Execute URL;

    }

    void RegisterClientState(Client c){
        ClientState state;
        state.c = client;
        state.timestamp = 0;
        state.token = 100; // default 100 requests allowed in 1 minute;
        clientMp[curr_id] = state;
    }

};

class Client{
    string name;
    string id;
    ...
};

int main(){

    return 0;
}
