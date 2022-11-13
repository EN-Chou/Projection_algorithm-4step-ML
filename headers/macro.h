///////////////////////////////////////////////////////////////////////////////
// This header stores the macros for the 4 step projection method.           //
// Stores defined values and global variables.                               //
///////////////////////////////////////////////////////////////////////////////
#pragma once
#define N 81
#define dt 0.003
#define Re 100
#define tol_p 1e-6
#define tol_v 1e-10
#define QUICK_CHECK true
#define use_ML false

double dx=1.0/(N-1), dy=1.0/(N-1);
int moniter_rate=10;
int time_step=0, iteration=0;
double vt, residual;

double P[N+1][N+1]={0.0}, U[N+1][N+1]={0.0}, V[N+1][N+1]={0.0};
double U_1[N+1][N+1]={0.0}, V_1[N+1][N+1]={0.0};
double U_2[N+1][N+1]={0.0}, V_2[N+1][N+1]={0.0};
double PC[N][N]={0.0}, UC[N][N]={0.0}, VC[N][N]={0.0};
double U_prev[N+1][N+1]={0.0}, V_prev[N+1][N+1]={0.0};
double P_pred[N+1][N+1]={0.0};
