#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include "DBFunctions.h"
using namespace std;

static const float C1 = 32.70*2*2, C1S = 34.65*2*2, D1 =36.71*2*2, D1S =38.89*2*2, E1 =41.20*2*2, F1 =43.65*2*2, 
				   F1S =46.25*2*2, G1 =49.00*2*2, G1S =51.91*2*2, A1 =55.00*2*2, A1S =58.27*2*2, B1 =61.74*2*2;
				   
static const float C2 = C1*2, C2S = C1S*2, D2 =D1*2, D2S =D1S*2, E2 =E1*2, F2 =F1*2, 
                   F2S =F1*2, G2 =G1*2, G2S =G1S*2, A2 =A1*2, A2S =A1S*2, B2 =B1*2;
                   
                //       0       1     2          3     4      5       6     7       8      9     10		11
void AshCrow(){	//  	1/1		1/2	  1/2dot  1/2trip  1/4   1/4dot  1/4tri  1/8   1/8dot 1/8tr  1/16    1/16tri
	float time[12] = {3428.57,1714.29,62571.43,1142.86,857.14,1285.71,571.43,428.57,642.86,285.71,214.29,142.86};
			//1st Part (1)
	for(int i=0;i<2;i++){
	Beep(A1,time[6]); Beep(A1,time[6]);	Beep(B1,time[9]); 
	if(i==0){
	Beep(C2,time[9]); Beep(E2,time[6]*3);
	}
	if(i==1){
	Beep(C2,time[9]); Beep(E1,time[6]*3);	
	}
	
    Beep(A1,time[6]); Beep(A1,(time[6]));  Beep(B1,time[9]); Beep(C2,time[9]); 
	Beep(B1,time[9]); Beep(C2,time[9]); Beep(D2,(time[9]*4));
	Sleep(time[9]*2);
	
			//1st Part (2) - ASH CROW , ASH CROW
	Beep(E2,time[9]); Sleep(time[9]); Beep(C2,(time[6]*2));
	Sleep(time[7]);
	Beep(E2,time[9]); Sleep(time[9]); Beep(C2,(time[6]*2));
	Sleep(time[7]);
	
			//1st Part (3)
	Beep(B1,time[6]); Beep(B1,time[6]);	Beep(A1,time[9]); Beep(B1,time[9]); Beep(A1,time[9]*6);
	}
	return; 
}
