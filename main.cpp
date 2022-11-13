#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <time.h> 
#include "headers/macro.h"
#include "headers/projection.h"
#include "headers/write.h"
using namespace std;

// 1 denote v_1;  2 denote v_2; 0 denote p;
int main(){
    clock_t start = clock();
    set_BC();
    do{
        //write();
        #if QUICK_CHECK
        cout<< "Time-step: "<< time_step-1<< "    dvdt: "<< vt<<" Iteration: "<< iteration<<";   divergence_v: "<< divergence_v() <<endl;
        #else
        cout<< "Time-step: "<< time_step-1<< "    dvdt: "<< vt<<" Iteration: "<< iteration<< " (Residual): "<< residual<< ";   divergence_v: "<< divergence_v() <<endl;
        #endif
        if(time_step%moniter_rate==0){
            collocate();
            moniter();
        }
        time_step++;
        step_1(1); step_1(2);
        step_2(1); step_2(2);
        set_BC(1); set_BC(2); 
        step_3(0);
        set_BC(0);
        step_4(1); step_4(2);
        set_BC(1); set_BC(2);
    }while(is_steady()==false);
    
    collocate();
    moniter();
    std::cout<< "---"<<((double) (clock() - start)) / CLOCKS_PER_SEC << "seconds---";
    return 0;
}
