#include "header.h"

using namespace std;

int get_pred(int index,int typ){
	int x,y;
	if(typ==1){
		x=bim->pb[index];
		if(x>=2){
			y=1;  //taken
		}
		else if(x<2){
			y=0;  //not taken
		}
		else
			cout<<"error";
	}
	else if(typ==2){
			x=gsh->pb[index];
			if(x>=2){
				y=1;  //taken
			}
			else if(x<2){
				y=0;  //not taken
			}
			else
				cout<<"error";
		}
	else if(typ==3){
			x=hyb->cht[index];
			if(x>=2){
				y=1;  //gshare pred
			}
			else if(x<2){
				y=0;  //bimodal pred
			}
			else
				cout<<"error";
		}
	return (y);
}
