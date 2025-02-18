#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct database{
    int w;
    int p;
    int i;
};
class Compare{
    public:
    template<typename T> 
    bool operator ()(T a, T b){ // descending order
        if((a.p/a.w) > (b.p/b.w))
        return true;
        else
        return false;
    }

};



void fractionalKP(double* weights, double* profits, int n, double ks){

    vector<database> v;
    for(int i = 0; i < n ; i++){
        // database *db = (database *) malloc (sizeof(database));
        database *db = new database;
        db->i = i;
        db->w = weights[i];
        db->p = profits[i];
        v.push_back(*db);
    }

    sort(v.begin(), v.end(), Compare());

    double curr_weight, curr_profit; 
    for(int i = 0 ; i < n ; i++){
        if(curr_weight + v[i].w <= ks){
            curr_weight += v[i].w;
            curr_profit += v[i].p;
        }else{
            double bal_weight = ks - curr_weight;
            double per_weight_profit = v[i].p/v[i].w;
            curr_profit += per_weight_profit * bal_weight;
            curr_weight = ks;
        }

        cout << " index " << v[i].i  << " total profit : " << curr_profit << " weight : " << curr_weight <<  endl; 
    }


}

int main(){

    double weights[5] = {10, 70, 40, 2, 11};
    double profits[5] = {500, 500, 500, 100,150};

    fractionalKP(weights,profits,5, 100);

    return 0;
}