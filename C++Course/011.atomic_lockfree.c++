#include<iostream>
#include<atomic>
#include<vector>
#include<thread>

using namespace std;

atomic<int> atomic_x;

int g_x;

void increment_global(){
    for(int i = 0; i < 100; i++){
        g_x++;
    }
}

void increment_atomic(){
    for(int i = 0; i < 100; i++){
        // int x = atomic_x.load();

        // atomic_x.store(x+1);

        // if(atomic_x.compare_exchange_strong(x, ++x)){
        //     cout << "error" << endl;
        // }
        
        // atomic_x.fetch_add(1, std::memory_order_relaxed);
        
        int expected = atomic_x.load();
        // while (true) {
        //     int desired = expected + 1;
        //     // success: acquire-release; failure: relaxed (reload expected)
        //     if (atomic_x.compare_exchange_strong(expected, desired)) {
        //         break; // succeeded
        //     }
        //     // on failure, 'expected' has been updated to the current atomic_x value
        //     // retry: desired will be recomputed from updated expected
        // }

        while (true) {
            int desired = expected + 2;

            // compare_exchange_strong does NOT fail spuriously,
            // but it requires the same loop structure.
            if (atomic_x.compare_exchange_strong(
                    expected,           // expected value (updated on failure)
                    desired,            // desired new value
                    std::memory_order_acq_rel,   // success ordering
                    std::memory_order_relaxed    // failure ordering
                ))
            {
                break; // success
            }
            // On failure:
            //   expected now contains the new value of atomic_x,
            //   so continue the loop using the updated expected.
        }
    }
}

int main(){

    atomic_x.store(1);
    g_x = 1;

    vector<thread> T1;

    for(int i = 0; i < 10000; i++){
        T1.emplace_back(increment_global);
    }

    for(int i = 0; i < T1.size(); i++){
        T1[i].join();
    }

    vector<thread> T2;

    for(int i = 0; i < 10000; i++){
        T2.emplace_back(increment_atomic);
    }

    for(int i = 0; i < T2.size(); i++){
        T2[i].join();
    }



    cout << atomic_x.load() << endl;
    cout << g_x << endl;

    return 0;
}