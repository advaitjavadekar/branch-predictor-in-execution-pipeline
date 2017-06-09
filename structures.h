/*
 * structures.h
 *
 *  Created on: 17-Apr-2017
 *      Author: hp
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include"header.h"

using namespace std;


class bimodal{
public:
	int* pb;
	bimodal(int ib){
		int r,i;
		r=pow(2,ib);
		pb=new int[r];
		for(i=0;i<r;i++){
			pb[i]=2;
		}
	}
	~bimodal(){
		delete[] pb;
	}
};


class gshare{
public:
	int *pb;
	int gbhr;
	gshare(int ig){
		gbhr=0;
		int r,i;
		r=pow(2,ig);
		pb=new int[r];
		for(i=0;i<r;i++){
			pb[i]=2;
		}


	}
	~gshare(){
		delete[] pb;
	}
};


class hybrid{
public:
	int *cht;
	int k;
	hybrid(int k){
		this->k=k;
		int i,r;
		r=pow(2,k);
		cht=new int[r];
		for(i=0;i<r;i++){
			cht[i]=1;
		}
	}
	~hybrid(){
		delete[] cht;
	}
};

extern hybrid* hyb;
extern bimodal* bim;
extern gshare* gsh;

#endif /* STRUCTURES_H_ */
