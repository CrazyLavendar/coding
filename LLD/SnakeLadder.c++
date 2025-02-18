/*
    Snake Ladder
    Player
    Dice
*/


#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<unistd.h>
using namespace std;

vector<int> board(100);
class Game{
public:
    vector<vector<int>> snakes; //= {{15 , 7}, {32, 22}, { 45, 41}, {47, 40}, {61, 21}, {79, 35}, {99, 90}};
    vector<vector<int>> ladders; //= {{10, 20}, {23,60}, {34, 38}, {45, 55}, {63, 81}, {77, 90}, {84, 94}};
    Game(){
    // Add Snakes
    snakes = {{15 , 7}, {32, 22}, { 45, 41}, {47, 40}, {61, 21}, {79, 35}, {99, 90}};
    ladders = {{10, 20}, {23,60}, {34, 38}, {45, 55}, {63, 81}, {77, 90}, {84, 94}};

    // Add Ladder
    }
    static Game* getInstance(){
        if(ins == NULL){
            ins = new Game();
        }
        return ins;
    }
private:
    static Game* ins;
};

Game *Game::ins = NULL; 

class Player{
public:
    string name;
    int pos;
    Game* ins;
    Player(string name) : name(name){
        ins = Game::getInstance();
        cout << "created player" << name << endl;
        pos = 0;
    }

    void check(vector<vector<int>> vec){
        for(auto& v : vec){
            if(v[0] == pos){
                pos = v[1];
                if(v[1] < v[0]){
                    cout << "Player" << name << " hit by snake. New position is " << pos << endl;
                }
                else{
                    cout << "Player" << name << " got ladder. New position is " << pos << endl;
                }
                return;
            }
        }
    }
    void checkGain(){
        check(ins->snakes);
        check(ins->ladders);
    }

    void Play(){
        long long nanoSec = chrono::high_resolution_clock::now().time_since_epoch().count();
        // long long microSec = chrono::system_clock::now().time_since_epoch().count();
        // cout << nanoSec << endl;
        // cout << microSec << endl;
        srand(nanoSec);
        int dice = rand() % 6;
        
        pos += dice;
        cout << "Player " << name << " rolled dice " << dice << " and new pos is : " << pos  << endl;

        if(pos >= 100){
            cout << "Player " << name <<  " wins" << endl;
        }
        
        checkGain();
    }


};
int main(){
    Player* p1 = new Player("A");
    Player* p2 = new Player("B");

    while(p1->pos < 100 && p2->pos < 100){
        usleep(100000);
        p1->Play();
        usleep(100000);
        p2->Play();
    }



    return 0;
}