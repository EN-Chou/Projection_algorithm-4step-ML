#pragma once
#include <iostream>
#include <math.h>
#include "macro.h"
#if use_ML
#include <torch/torch.h>
#include <torch/script.h>
#endif
using namespace std;

void guess_P(){
    int i, j;
    #if use_ML
    // [Linux]/home/enchou/git-repo [Windows]/mnt/c/Users/ENCHOU/Documents/git-repo
    torch::jit::script::Module model=torch::jit::load("/home/enchou/git-repo");
    double test[N+1][N+1]={0.0}; //這奇怪的bug，明明沒用到但不加就會core dump
    double u_st[1][(N-1)*(N-1)];
    auto options = torch::TensorOptions().dtype(torch::kFloat64); 
    torch::Tensor x, out;
    vector<torch::jit::IValue> input;
    //Flatten
    for(int i=0; i<N-1; i++){
        for(int j=0; j<N-1; j++){
            u_st[0][i*(N-1)+j]=U_1[i+1][j+1]-U_1[i][j+1]+V_1[i+1][j+1]-V_1[i+1][j]; 
        }
    }
    //(input) array -> tensor -> vector
    x=torch::from_blob(u_st, {1,(N-1)*(N-1)}, options);
    input.clear();
    input.push_back(x);
    //output=model(input)
    out=model.forward(input).toTensor();
    //(output)tensor -> 2D-array
    for(i=0; i<N-1; i++){
        for(j=0; j<N-1; j++){
            P[i+1][j+1]=out[0][i*(N-1)+j].item<double>(); 
        }
    }
    #endif
    for(i=1; i<N; i++){
        for(j=1; j<N; j++){
            P_pred[i][j]=P[i][j];
        }
    }
}