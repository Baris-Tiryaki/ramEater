/*
Author: Barış Tiryaki
Date: 25.05.2022
*/

#include<stdio.h>
#include<cstring>
#include<iostream>
#include<random>
#include<chrono>
#include<thread>

using namespace std;
using namespace std::chrono;

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> distr(0, (uint32_t) 0xFFFFFFFF);



void waitIfLag(steady_clock::time_point* t){
    t[9] = chrono::steady_clock::now();
    int elapsedMS = duration_cast<milliseconds>(t[9]-t[8]).count();
    int sleepMS = (elapsedMS-15)*2;
    if(sleepMS>0){
        this_thread::sleep_for(milliseconds(sleepMS));
    }
    t[8] = chrono::steady_clock::now();
}

int main(int argc, char** argv){
    bool noWarning=false;
    if(argc>1){
        int len=strlen(argv[1]);
        if(argc==2 && len==2 && argv[1][0]=='-' && argv[1][1]=='n'){
            noWarning=true;
        }
        else{ //display help message
            printf("This program allocates a specified amount of memory. Then, writes random data to it. Then, reads it back until stopped. ");
            printf("It will show the elapsed time in each part. ");
            printf("To get used to how it works, run it a few times with a small amount.\n");
            printf("Try ctrl+C to kill the process\n\n");
            
            printf("This program was made to study how Windows handles allocating more memory than available. ");
            printf("If you request more memory than available, contents of RAM will be transfered to hard drive, which is SLOW. ");
            printf("So slow that, the whole system can freeze or crash.\n");
            printf("Save all your files, and use at your own risk.\n");
            printf("To hide the warning, run it like this: ramEater64.exe -n\n");
            return 0;
        }
    }
    if(!noWarning){
        printf("WARNING: This program may freeze/crash your system.\n");
        this_thread::sleep_for(milliseconds(1000));
        printf("Save all your files, and use at your own risk.\n");
        this_thread::sleep_for(milliseconds(1000));
        printf("Run as 'ramEater64.exe help' to learn more information.\n");
        this_thread::sleep_for(milliseconds(1000));
        printf("\n");
    }
    
    printf("sizeof(void*)=%d,  sizeof(size_t)=%d\n", sizeof(void*), sizeof(size_t));
    uint64_t N, N4, N8;
    steady_clock::time_point t[10];
    double elapsed;
    
    cout<<"How many MB to allocate? ";
    cin>>N;
    cin.ignore();
    N = N*1024*1024;
    N4 = N/4;
    N8 = N/8;
    
    t[0] = chrono::steady_clock::now();
    uint64_t *array8 = new uint64_t[N8];
    uint32_t *array4 = (uint32_t*) array8;
    t[1] = chrono::steady_clock::now();
    elapsed = duration_cast<microseconds>(t[1]-t[0]).count()/1000000.0;
    printf("Memory was allocated (0x%p) (%.3f sec) ", array8, elapsed);
    cin.ignore();       //wait for 'enter'
    
    
    t[2] = chrono::steady_clock::now();
    t[8] = t[2];
    for(uint64_t i=0; i<N4; i++){
        array4[i] = distr(rng);
        if((i&0xfffff) == 0){
            waitIfLag(t);
        }
    }
    t[3] = chrono::steady_clock::now();
    elapsed = duration_cast<microseconds>(t[3]-t[2]).count()/1000000.0;
    printf("Memory was filled with random data (%.3f sec)\n", elapsed);
    cin.ignore();       //wait for 'enter'
    
    while(true){
        uint64_t result=0;
        t[4] = chrono::steady_clock::now();
        t[8] = t[4];
        for(uint64_t i=0; i<N8; i++){
            result += array8[i];
            if((i&0xfffff) == 0){
                waitIfLag(t);
            }
        }
        t[5] = chrono::steady_clock::now();
        elapsed = duration_cast<microseconds>(t[5]-t[4]).count()/1000000.0;
        printf("Memory was read (%.3f sec)  (result=%llu)\n", elapsed, result%1007);
    }
    return 0;
}