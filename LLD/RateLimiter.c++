#include<iostream>
#include<queue>
#include<vector>
#include<chrono>
using namespace std;

typedef long long ll;

struct API{
    string API_link;
    ll timeStamp;
};

enum client_subscription{
    basic = 0,
    premium
};

class Client;

class Server{
public:
    static Server* getInstance(){
        if (NULL == instance)
        {
            instance = new Server();
        }
        return instance;
    }
    void addClient(Client*);
    static void processAPI(Client* c);
    Server(const Server& obj) = delete;
    Server& operator = (const Server& obj) = delete;
private:
    int API_limit = 0;
    static Server* instance;
    Server(){};
    vector<Client*> clients;
};

class Client{
public:
    string client_name;
    vector<API> api_Queue;
    client_subscription plan;
    Server *s = Server::getInstance();

    Client(string name){
        client_name = name;
        this->plan = basic;
        s->addClient(this);
    }

    Client(string name, client_subscription plan){
        client_name = name;
        this->plan = plan;
    }

    void accessAPICall(string API_link){
        ll time = chrono::system_clock::now().time_since_epoch().count();
        API api{API_link, time};
        cout << client_name << " access API " << API_link << " at  " << time << endl;
        api_Queue.push_back(api);
        Server::processAPI(this);
    }
private:

    
};

void Server::addClient(Client* c){
    clients.push_back(c);
}
void Server::processAPI(Client* c){
    cout << "called process API" << endl;
    if (c == NULL){
        cout <<" HI" << endl;
    }
    
    int limit = 0;
    if(c->plan == basic){
        limit = 100;
    }else{
        limit = 1000;
    }

    if(limit < c->api_Queue.size()){
        API front = c->api_Queue[c->api_Queue.size() - limit - 1];
        API curr = c->api_Queue[c->api_Queue.size() - 1];

        cout << "diff int timestamp  " << curr.timeStamp - front.timeStamp << endl; 
        if(curr.timeStamp - front.timeStamp > 500){
            cout << "API not processed for client " << c->client_name << " at time epoch " << curr.timeStamp << endl;
            c->api_Queue.pop_back();
        }
    }

}



Server *Server::instance = NULL;


int main(){

    Server *s = Server::getInstance();
    

    Client* c1= new Client("A", basic);
    Client* c2= new Client("B");
    Client* c3= new Client("C");

    
    s->addClient(c2);
    s->addClient(c3);

    for(int i = 0 ; i < 101 ; i++){
        string API_name = to_string(chrono::system_clock::now().time_since_epoch().count());
        c1->accessAPICall(API_name);
    }



    return 0;
}