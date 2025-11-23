/*
    Video 
    Pipeline for PreProcess, process, PostProcess
*/

#include<iostream>
#include<unistd.h>
#include<memory>
#include<vector>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

int width = 100;
int height = 100;
int BuffersLength = 10;

class Image{
public:
    vector<vector<int>> img;
    mutex m;
    Image(){cout << "image created" << endl;}
    ~Image(){cout << "image destroyed" << endl;}
};

static vector<Image*> buffers;

class PipelineProcess{
public:


    static void execute(){

    }
    PipelineProcess(){
        buffers.resize(BuffersLength);
        for(int i = 0; i < BuffersLength; i++){
            buffers[i] = new Image();
            buffers[i]->img.resize(width);
            for(int j = 0; j < width; j++){
                buffers[i]->img[j].resize(height);
            }

        }
    }
    ~PipelineProcess(){
        for(auto& b : buffers)
            delete b;
    }
};

class PreProcess{
public:
    static void execute() {
        for(int i = 0; i < BuffersLength; i++){
            buffers[i]->m.lock();
            cout << " exectuting  buffer " << i << " Preprcoess" << endl; 
            for(int j = 0; j < width ; j++){
                for(int k = 0 ; k < height ; k++){
                    buffers[i]->img[j][k] = 1;
                }
            }
            buffers[i]->m.unlock();
        }
    }
};

class Process : public PreProcess{
public:
    static void execute() {
        for(int i = 0; i < BuffersLength; i++){
            buffers[i]->m.lock();
            cout << " exectuting  buffer " << i << " prcoess" << endl; 
            for(int j = 0; j < width ; j++){
                for(int k = 0 ; k < height ; k++){
                    buffers[i]->img[j][k] = 2;
                }
            }
            buffers[i]->m.unlock();
        }
    }
};

class PostProcess : public Process{
public:
    static void execute() {
        for(int i = 0; i < BuffersLength; i++){
            buffers[i]->m.lock();
            cout << " exectuting  buffer " << i << " Postprcoess" << endl; 
            for(int j = 0; j < width ; j++){
                for(int k = 0 ; k < height ; k++){
                    buffers[i]->img[j][k] = 3;
                }
            }
            buffers[i]->m.unlock();
        }
    }
};



int main(){
    PipelineProcess* p = new PipelineProcess();
    PreProcess* prepipeline = new PreProcess();
    Process* pipeline = new Process();
    PostProcess* postpipeline = new PostProcess();

    // prepipeline->execute();
    // pipeline->execute();
    // postpipeline->execute();


    thread t1(prepipeline->execute);
    thread t2(pipeline->execute);
    thread t3(postpipeline->execute);
    t1.join();
    t2.join();
    t3.join();



    delete prepipeline;
    return 0;
}