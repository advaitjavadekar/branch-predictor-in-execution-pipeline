#include "header.h"

using namespace std;

int update_bhr(int pred_actual){
	gsh->gbhr=(gsh->gbhr)>>1;
	if(pred_actual==1 && gsh->gbhr<gbhrmax){
		gsh->gbhr=(gsh->gbhr)+pow(2,h-1);
		//cout<<preds<<":"<<gsh->gbhr<<endl;
	}
	return (0);
}
