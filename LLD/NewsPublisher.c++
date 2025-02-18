/*

Pusblisher - Publish news
Reader   - See news, {sports, politics, stocks}
Reader can subscribe what they want

30 mins
Took 40 mins for me to complete


Move to thread
30 mins



*/

#include <iostream>
#include<vector>
#include<map>
using namespace std;

enum NewsType{
    sports = 0,
    politics,
    stocks,
};

struct News{
    string news;
    NewsType type;
};

class Reader;

class Publisher{
public:
    static Publisher *instance;
    // vector<Reader*> readers_q;
    map<NewsType, vector<Reader*>> readers_map;
    vector<News> news_q;
    void addReader(NewsType type, int id);
    static Publisher* getInstance(){
        if(NULL == instance){
            instance = new Publisher();
        }
        return instance;
    }

    void shareNews(News news);

    void generateNews(News news){
        news_q.push_back(news);
        shareNews(news);
    }
    // Need to check why copy and == assignment still working?
    // Publisher (Publisher* obj) = delete;
    // Publisher (Publisher& obj) = delete;
    // Publisher operator = (Publisher* obj) = delete;
    // Publisher operator = (Publisher& obj) = delete;
private:

    Publisher(){};
};

class Reader{
public:
    int id;
    NewsType type;
    Reader(int id, NewsType type): id(id),type(type) {}
    void getNews(News news){
        cout << " I am a reader with id "<< id  << " with intersest on news type" << type << "news : " << news.news <<  endl; 
    }
private:
};

void Publisher::addReader(NewsType type, int id){
    Reader* r = new Reader(id, type);
    // readers_q.push_back(r);
    // readers_map[type] = id;
    if (readers_map.count(type) > 0){
        readers_map[type].push_back(r);
    }
    else{
        vector<Reader*> newVecReader = {r};
        readers_map[type] = newVecReader;
    }
    cout << "added reader " << id << " with insterest : " << type << endl; 
}

void Publisher::shareNews(News news){
    vector<Reader*> selected = readers_map[news.type];
    for(auto& r : selected){
        r->getNews(news);
    }

}

Publisher* Publisher::instance = Publisher::getInstance();

int main(){
    Publisher::instance->addReader(sports, 1);
    Publisher::instance->addReader(politics, 2);
    Publisher::instance->addReader(sports, 3);
    Publisher::instance->generateNews({"Sachin hit a six" , sports});

    Publisher* newInstance(Publisher::instance);

    return 0;
}