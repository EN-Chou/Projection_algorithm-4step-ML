///////////////////////////////////////////////////////////////////////////////
// This header is for the use of writing data.                               //
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fstream>
#include <string>
#include "macro.h"
using namespace std;

ofstream input_div_U_2("ML/data/input_div_U_2.dat");
ofstream output_P("ML/data/output_P.dat");
ofstream iteration_info("data/iteration_info.dat");
ofstream guess_accuracy("data/guess_accuracy.dat");
ofstream flow_data("data/flowfield.dat");

void write();
void collect_ML_training_data(), collect_iteration_info(), collect_guess_accuracy();
void collect_flow_data();

///////////////////////////////////////////////////////////////////////////////
// The lower section should be write.cpp instead.                            //
///////////////////////////////////////////////////////////////////////////////
void write(){ 
    collect_ML_training_data();
    collect_iteration_info();
    collect_guess_accuracy();
    collect_flow_data();
}

void collect_ML_training_data(){
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            input_div_U_2<< (U_2[i][j]-U_2[i-1][j]+V_2[i][j]-V_2[i][j-1])/dx <<"  ";
            output_P<< P[i][j]<<"  ";
        }
    }
    input_div_U_2<< endl;
    output_P<<endl;
}

void collect_iteration_info(){//Tecplot format
    if(time_step==0){
        iteration_info<<"time_step iteration"<<endl;
    }
    iteration_info<< time_step << "   " << iteration <<endl;
}

void collect_guess_accuracy(){//Tecplot format
    double L2=0;
    if(time_step==0){
        guess_accuracy<<"time_step L2"<<endl;
    }
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            L2+=(P[i][j]-P_pred[i][j])*(P[i][j]-P_pred[i][j]);
        }
    }
    guess_accuracy<< time_step << "   " << L2 <<endl;
}

void collect_flow_data(){//Tecplot format
    if(time_step==0){
        flow_data<<"VARIABLES=\"x\", \"y\", \"time\", \"u\", \"v\", \"p\""<<endl;
        flow_data<<"ZONE T=\"1\""<<endl;
        flow_data<<"F=POINT"<<endl;
        flow_data<<"I=81,J=81,K=(define)"<<endl;
    }
    else{
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                flow_data<<1-i*dx<<" "<<j*dx<<"    "<< time_step*dt<<" "<<UC[i][j]<<"   "<<VC[i][j]<<"   "<<PC[i][j]<<endl; 
            }
        }
    }

}
