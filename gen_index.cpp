#include "header.h"

using namespace std;

int gen_index(int index,int h){
	/*cout<<"index:"<<index<<endl;
	cout<<"h:"<<h<<endl;
	cout<<"gbhrmax:"<<gbhrmax<<endl;*/
	int hbits,y,ihbits,indexfinal;
	hbits=index>>(pred_index_g-h);
	y=(gsh->gbhr)^hbits;
	ihbits=(hbits<<(pred_index_g-h))^(index);
	indexfinal=(y<<(pred_index_g-h))|ihbits;
	return (indexfinal);
}
