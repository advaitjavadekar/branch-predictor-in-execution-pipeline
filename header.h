/*
 * header.h
 *
 *  Created on: 17-Apr-2017
 *      Author: hp
 */

#ifndef HEADER_H_
#define HEADER_H_
#include<string>
#include<iostream>
#include<fstream>
#include<math.h>
#include<cstdlib>
#include "stdio.h"
#include "string.h"
#include <new>
#include "structures.h"
#include<iomanip>

//global variables
extern unsigned long long int preds;
extern unsigned long long int mispreds,corpreds;
extern float mispred_rate;
extern int gbhrmax;
extern int pred_index_b;
extern int pred_index_g;
extern string pred_type;
extern char* trace_file;
extern int h;  	//global branch history register bits
extern int pt;		//prediction type
extern int k;		//chooser history table bits
extern int address_size;



using namespace std;

//functions
string hextobin(string,int);
int get_pred(int,int);
int update_table(int,int,int);
int gen_index(int,int);
int update_bhr(int);
int bintodec(string);





#endif /* HEADER_H_ */
