#include "header.h"

using namespace std;

int update_table(int pred_act,int index,int typ){
	if(typ==1){
	if(pred_act==1 && bim->pb[index]<3){
		bim->pb[index]++;
		//cout<<"pred_table["<<index<<"]= "<<bim->pb[index]<<endl;
	}
	else if(pred_act==0 && bim->pb[index]>0){
		bim->pb[index]--;
		//cout<<"pred_table["<<index<<"]= "<<bim->pb[index]<<endl;
	}
	}
		//cout<<"table value saturated"<<endl;

	else if(typ==2){
		if(pred_act==1 && gsh->pb[index]<3){
			gsh->pb[index]++;
		}
		else if(pred_act==0 && gsh->pb[index]>0){
			gsh->pb[index]--;
		}
	}
	return (0);
	//cout<<"table updated";
}
