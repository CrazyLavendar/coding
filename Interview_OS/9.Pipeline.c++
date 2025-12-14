/*
Implement video process pipelines

- preprocess
- process
- postprocess

When the buffer is in preprocess, (Process/postprocess cannot happen) for same buffer

*/

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<chrono>

using namespace std;

struct buffer{
    int id;
    bool donePreProcess;
    bool doneProcess;
    bool donePostProcess;
};

class VideoPipeline{

public:
    VideoPipeline(vector<buffer>& buffers, int depth) : buffers(buffers), depth{depth}{}
    void preProcess(){
        int i = 0;
        mutex m;
        while(true){
            unique_lock<mutex> ul(m);
            if (process_done || i >= depth)
                break;
            if (i != 0){
                cout << "hi" << i << endl;
                cv.wait(ul, [&]{
                    return buffers[i-1].donePostProcess == true;
                });
            }
            
            cout << "doing Preprocess " << i << endl;

       ul.unlock();

        this_thread::sleep_for(chrono::seconds(1));

        ul.lock();
            i++;
            buffers[i].donePreProcess = true;
            ul.unlock();
            cv.notify_all();
        }
    }
    void process(){
        int i = 0;
        mutex m;
        while(true){
            unique_lock<mutex> ul(m);
            if (process_done || i >= depth)
                break;
            cv.wait(ul, [&]{
                    return buffers[i].donePreProcess == true;
            });
            cout << "doing process " << i << endl;
            
       ul.unlock();

        this_thread::sleep_for(chrono::seconds(1));

        ul.lock();
            i++;
            buffers[i].doneProcess = true;
            ul.unlock();
            cv.notify_all();
        }
    }
    void postProcess(){
        int i = 0;
        mutex m;
        while(true){
            unique_lock<mutex> ul(m);
            if (process_done || i >= depth)
                break;
            cv.wait(ul, [&]{
                    return buffers[i].doneProcess == true;
            });
            cout << "doing PostProcess " << i << endl;
            
       ul.unlock();

        this_thread::sleep_for(chrono::seconds(1));

        ul.lock();
            i++;
            buffers[i].donePostProcess = true;
            ul.unlock();
            cv.notify_all();
        }
    }

    void handlePipeline(){
        thread t1(&VideoPipeline::preProcess, this);
        thread t2(&VideoPipeline::process, this);
        thread t3(&VideoPipeline::postProcess, this);

        t1.join();
        t2.join();
        t3.join();
    }

private:
    vector<buffer>& buffers;
    int depth;
    bool process_done;
    condition_variable cv;

};

int main(){
    vector<buffer> buffers;
    for(int i = 1; i <= 10; i++){
        buffer b;
        b.id = i;
        b.donePreProcess = false;
        b.doneProcess = false;
        b.donePostProcess = false;
        buffers.push_back(b);
    }
    
    
    VideoPipeline vp(buffers, buffers.size());
    vp.handlePipeline();
}


