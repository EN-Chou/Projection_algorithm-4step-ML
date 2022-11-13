///////////////////////////////////////////////////////////////////////////////
//This file is the header for functions of the 4 step projection method.     //
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <math.h>
#include "macro.h"
#include "guess.h"
using namespace std;

void set_BC(int);
void step_1(int);
void step_2(int);
void step_3(int);
void step_4(int);
void moniter();

void setBC_P(), setBC_U(), setBC_V();
void solve_U1(), solve_V1(), solve_U2(), solve_V2();
void solve_P(), solve_U(), solve_V();

bool is_steady(), meet_poisson();

void collocate(), write();

double divergence_v();
///////////////////////////////////////////////////////////////////////////////
// The lower section should be function.cpp instead.                         //
///////////////////////////////////////////////////////////////////////////////
// First hieraracy of function.                                              //
/////////////////////////////////////////////////////////////////////////////// 
void set_BC(int dir=3){
    switch(dir){
        case 0:
            setBC_P();
            break;
        case 1:
            setBC_U();
            break;
        case 2:
            setBC_V();
            break;
        case 3:
            setBC_P();
            setBC_U();
            setBC_V();
            break;
    }

}

void step_1(int dir){
    switch(dir){
        case 1:
            solve_U1();
            break;
        case 2:
            solve_V1();
            break;
    }

}

void step_2(int dir){
    switch(dir){
        case 1:
            solve_U2();
            break;
        case 2:
            solve_V2();
            break;
    }

}

void step_3(int dir){
    guess_P();
    solve_P();
}

void step_4(int dir){
    switch(dir){
        case 1:
            solve_U();
            break;
        case 2:
            solve_V();
            break;
    }

}
///////////////////////////////////////////////////////////////////////////////
// Second hieraracy of function.                                             //
/////////////////////////////////////////////////////////////////////////////// 
void setBC_P(){
    for(int i=0; i<N+1; i++){
        P[0][i]=P[1][i]; //west
        P[N][i]=P[N-1][i]; //east
        P[i][0]=P[i][1]; //south
        P[i][N]=P[i][N-1]; //north
    }
}

void setBC_U(){
    for(int i=0;i<N+1; i++){
        U[0][i]=0.0, U_1[0][i]=0.0, U_2[0][i]=0.0; ; //west
        U[N-1][i]=0.0, U_1[N-1][i]=0.0, U_2[N-1][i]=0.0; //east
        U[i][0]=-U[i][1], U_1[i][0]=-U_1[i][1], U_2[i][0]=-U_2[i][1]; //south
        U[i][N]=2.0-U[i][N-1], U_1[i][N]=2.0-U_1[i][N-1], U_2[i][N]=2.0-U_2[i][N-1]; //north
    }
}

void setBC_V(){
    for(int i=0; i<N+1; i++){
        V[0][i]=-V[1][i], V_1[0][i]=-V_1[1][i], V_2[0][i]=-V_2[1][i]; //west
        V[N][i]=-V[N-1][i], V_1[N][i]=-V_1[N-1][i], V_2[N][i]=-V_2[N-1][i]; //east
        V[i][0]=0.0, V_1[i][0]=0.0, V_2[i][0]=0.0; //south
        V[i][N-1]=0.0, V_1[i][N-1]=0.0, V_2[i][N-1]=0.0; //north
    }
}

void solve_U1(){
    double u, v, ux, uy, u2x, u2y;
    double C, D, px;
    for(int i=1; i<N; i++){
        for(int j=1; j<N+1; j++){
            u=U[i][j];
            v=(V[i][j]+V[i+1][j]+V[i][j-1]+V[i+1][j-1])/4.0;
            ux=(U[i+1][j]-U[i-1][j])/(2.0*dx);
            uy=(U[i][j+1]-U[i][j-1])/(2.0*dy);
            u2x=(U[i+1][j]+U[i-1][j]-2.0*U[i][j])/(dx*dx);
            u2y=(U[i][j+1]+U[i][j-1]-2.0*U[i][j])/(dy*dy);

            C=u*ux+v*uy;
            D=(u2x+u2y)/Re;
            px=(P[i+1][j]-P[i][j])/dx;

            U_1[i][j]=(-C+D-px)*dt+U[i][j];
        }
    }
}

void solve_V1(){
    double u, v, vx, vy, v2x, v2y;
    double C, D, py;
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N; j++){
            u=(U[i-1][j+1]+U[i][j+1]+U[i-1][j]+U[i][j])/4.0;
            v=V[i][j];
            vx=(V[i+1][j]-V[i-1][j])/(2.0*dx);
            vy=(V[i][j+1]-V[i][j-1])/(2.0*dy);
            v2x=(V[i+1][j]+V[i-1][j]-2.0*V[i][j])/(dx*dx);
            v2y=(V[i][j+1]+V[i][j-1]-2.0*V[i][j])/(dy*dy);

            C=u*vx+v*vy;
            D=(v2x+v2y)/Re;
            py=(P[i][j+1]-P[i][j])/dy;

            V_1[i][j]=(-C+D-py)*dt+V[i][j];
        }
    }
}

void solve_U2(){
    double px;
    for(int i=1; i<N; i++){
        for(int j=1; j<N+1; j++){
            px=(P[i+1][j]-P[i][j])/dx;

            U_2[i][j]=px*dt+U_1[i][j];
        }
    }
}

void solve_V2(){
    double py;
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N; j++){
            py=(P[i][j+1]-P[i][j])/dy;

            V_2[i][j]=py*dt+V_1[i][j];
        }
    }
}

// void guess_P(){} Defined in ML.h

void solve_P(){
    double ux, vy;
    double poisson_LHP;
    iteration=0;

    while(meet_poisson()==false){
        if(QUICK_CHECK&&(iteration!=0))
            break;
        iteration++;
        for(int i=1; i<N+1; i++){
            for(int j=1; j<N+1; j++){
                ux=(U_2[i][j]-U_2[i-1][j])/dx;
                vy=(V_2[i][j]-V_2[i][j-1])/dy;

                poisson_LHP=(ux+vy)/dt;
                P[i][j]=0.25*(P[i+1][j]+P[i-1][j]+P[i][j+1]+P[i][j-1]-poisson_LHP*dx*dx);

            }
        }

    }
}

void solve_U(){
    double px;
    for(int i=1; i<N; i++){
        for(int j=1; j<N+1; j++){
            px=(P[i+1][j]-P[i][j])/dx;

            U[i][j]=-px*dt+U_2[i][j];
        }
    }
}

void solve_V(){
    double py;
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N; j++){
            py=(P[i][j+1]-P[i][j])/dy;

            V[i][j]=-py*dt+V_2[i][j];
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Third hieraracy of function.                                              //
///////////////////////////////////////////////////////////////////////////////

bool is_steady(){
    //計算BC內部的區域，忽略長邊，假設不影響。
    vt=0.0;
    double tolerance=tol_v;
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            vt+=fabs(U_prev[i][j]-U[i][j]);
            vt+=fabs(V_prev[i][j]-V[i][j]);
            U_prev[i][j]=U[i][j];
            V_prev[i][j]=V[i][j];
        }
    }


    if(vt<tolerance){
        return true;
    }

    return false;
}

bool meet_poisson(){
    double ux, vy;
    double poisson_LHP, poisson_RHP;
    double tolerance=tol_p;

    residual=0;
    for(int i=1; i<N+1; i++){
        for(int j=1; j<N+1; j++){
            ux=(U_2[i][j]-U_2[i-1][j])/dx;
            vy=(V_2[i][j]-V_2[i][j-1])/dy;
            poisson_LHP=(ux+vy)/dt;
            poisson_RHP=(P[i+1][j]+P[i-1][j]+P[i][j+1]+P[i][j-1]-4.0*P[i][j])/(dx*dx);
            residual+=fabs(poisson_LHP-poisson_RHP);
        }
    }

    if(residual<tolerance)
        return true;

    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Post-process                                                              //
///////////////////////////////////////////////////////////////////////////////
void collocate(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            UC[i][j]=0.5*(U[i][j]+U[i][j+1]);
            VC[i][j]=0.5*(V[i][j]+V[i+1][j]);
            PC[i][j]=(P[i][j]+P[i+1][j]+P[i][j+1]+P[i+1][j+1])*0.25;
        }
    }

}

void moniter(){
    string directory_moniter="./moniter"; 
	ofstream moniter_u(directory_moniter+"/u.dat");
	ofstream moniter_v(directory_moniter+"/v.dat");
	ofstream moniter_p(directory_moniter+"/p.dat");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			moniter_u << UC[i][j] << ",";
			moniter_v << VC[i][j] << ",";
			moniter_p << PC[i][j] << ",";
		}
		moniter_u << endl;
		moniter_v << endl;
		moniter_p << endl;
	}
	moniter_u.close();
	moniter_v.close();
	moniter_p.close();
    return;

}

///////////////////////////////////////////////////////////////////////////////
// Debug                                                                     //
///////////////////////////////////////////////////////////////////////////////

double divergence_v(){
    double div=0;
    for(int i=2; i<N-1; i++){
        for(int j=2; j<N-1; j++){
            div+=fabs(U[i][j]-U[i-1][j]+V[i][j]-V[i][j-1])/dx;
        }
    }

    return div;
}