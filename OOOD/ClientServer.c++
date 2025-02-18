#include<iostream>
#include<vector>
using namespace std;

class Client{

    string name;
    string URL;

    public:
    Client(string name){
        this->name = name;
    }
};

class Server{
private:
    Server(){
        cout << "created server instance" << endl;
    };
    Server& operator=(Server& obj){
        return obj;
    }
    vector<Client> clients;
    ~Server(){
        cout << "deleted server instance" << endl;
        delete Server::instance;
    }
public:
    Server(Server& obj) = delete;
    static Server* instance;
    void createClient(string name){
        Client c(name);
        clients.push_back(c);
        cout << " created client " << name << endl;
        cout << " New codespace" << endl;
        cout << " New codespace" << endl;
    }
};

Server* Server::instance = new Server();
int main(){

    Server::instance->createClient("A");

    Server *instance2 = Server::instance;
    
    return 0;
}