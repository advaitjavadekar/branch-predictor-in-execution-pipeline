#include "header.h"

unsigned long long int preds;
unsigned long long int mispreds,corpreds;
float mispred_rate;
int gbhrmax;
int pred_index_b;   //input ib
int pred_index_g;	//input ig
string pred_type;	//prediction type
int pt;
char* trace_file;
int h;
int k;
int address_size;
bimodal* bim;
gshare* gsh;
hybrid* hyb;

using namespace std;

int main(int argc, char* argv[]){

	string line,bin_addr_s;
	char hex_addr[20];
	int offset;
	int i,j_b,j_g,j_k,pred,pred_act;
	int pred_b,pred_g,pred_cht;
	unsigned long long int index_b,index_g,index_gf,index_k;
	string index_b_bin,index_g_bin,index_k_bin;


//initial values
	gbhrmax=0;
	preds=0;
	mispreds=0;
	corpreds=0;
	mispred_rate=0;
	pred_index_b=0;
	pred_index_g=0;
	pt=0;
	h=0;
	k=0;
	address_size=0;
	offset=2;

	string type_b="bimodal";
	string type_g="gshare";
	string type_h="hybrid";


//decide type of branch prediction
	if(argc==4){
		pred_type=argv[1];
		pt=1;
		pred_index_b=atoi(argv[2]);
		trace_file=argv[3];
		bim=new bimodal(pred_index_b);
	}
	else if(argc==5){
			pred_type=argv[1];
			pt=2;
			pred_index_g=atoi(argv[2]);
			//cout<<pred_index_g<<endl;
			h=atoi(argv[3]);
			//cout<<h<<endl;
			trace_file=argv[4];
			for(i=0;i<h;i++){
				gbhrmax=gbhrmax+pow(2,i);
			}
			//cout<<gbhrmax<<endl;
			gsh=new gshare(pred_index_g);
		}
	else if(argc==7){
			pred_type=argv[1];
			//cout<<pred_type<<endl;
			pt=3;
			k=atoi(argv[2]);
			//cout<<k<<endl;
			pred_index_g=atoi(argv[3]);
			//cout<<pred_index_g<<endl;
			h=atoi(argv[4]);
			//cout<<h<<endl;
			pred_index_b=atoi(argv[5]);
			//cout<<pred_index_b<<endl;
			trace_file=argv[6];
			//cout<<trace_file<<endl;
			for(i=0;i<h;i++){
				gbhrmax=gbhrmax+pow(2,i);
			}
			//cout<<"this happens"<<endl;
			//cout<<gbhrmax<<endl;
			bim=new bimodal(pred_index_b);
			gsh=new gshare(pred_index_g);
			hyb=new hybrid(k);
		}
	else
		cout<<"error";

//calculation of parameters


//reader of trace file
	ifstream file(trace_file);
	if (file.is_open()){
				while (getline(file,line)){
					//cout<<"file is open"<<endl;
					preds++;
					address_size=(line.length()-2)*4;
					//cout<<"line length "<< line.length() << "address_size: "<<address_size<<endl;
					strncpy(hex_addr, line.c_str(),30);
					//cout<<preds<<":"<<hex_addr<<endl;
					bin_addr_s=hextobin(hex_addr,line.length());
					//cout<<bin_addr_s<<endl;

					//cout<<"jb: "<<j_b<<endl;



//index extraction
//after getting the index need to get prediction

		//bimodal
					if(pt==1){
						if(!type_b.compare(pred_type)){
						j_b=address_size-pred_index_b-offset;
						index_b_bin=bin_addr_s.substr(j_b,pred_index_b);
						//cout<<index_b_bin<<endl;
						index_b=bintodec(index_b_bin);
						pred=get_pred(index_b,1);
						//cout<<"index: "<<index_b<<endl;

//taken or not taken actual
						if(hex_addr[line.length()-1]=='t'){
							pred_act=1;
						}
						else if(hex_addr[line.length()-1]=='n'){
							pred_act=0;
						}
						//else cout<<"error";

//update table values
						update_table(pred_act,index_b,1);

						if(pred!=pred_act){
							mispreds++;
						}
						else
							corpreds++;
					}
						else cout<<"error prediction type not recognized";
					}



			//gshare
					else if(pt==2){
						if(!type_g.compare(pred_type)){
						j_g=address_size-pred_index_g-offset;
						//cout<<"jg: "<<j_g<<endl;
						//cout<<"here"<<" "<<preds<<" " << bin_addr_s<<endl;
						index_g_bin=bin_addr_s.substr(j_g,pred_index_g);
						//cout << "index_g_bin " << index_g_bin << endl;
						index_g=bintodec(index_g_bin);
			//generate index
						index_gf=gen_index(index_g,h);
						pred=get_pred(index_gf,2);

//taken or not taken actual
						if(hex_addr[line.length()-1]=='t'){
							pred_act=1;
						}
						else if(hex_addr[line.length()-1]=='n'){
							pred_act=0;
						}

//update table
						update_table(pred_act,index_gf,2);
						update_bhr(pred_act);

						if(pred!=pred_act){
							mispreds++;
							}
						else
							corpreds++;
					}
						else cout<<"prediction type not recognized";
					}

					else if(pt==3){
						if(!type_h.compare(pred_type)){
						j_b=address_size-pred_index_b-offset;
						j_g=address_size-pred_index_g-offset;
						j_k=address_size-k-offset;
						//cout<<"j_b="<<j_b<<endl;
						//cout<<pred_index_b<<endl;
						index_b_bin=bin_addr_s.substr(j_b,pred_index_b);
						index_b=bintodec(index_b_bin);
						pred_b=get_pred(index_b,1);

						index_g_bin=bin_addr_s.substr(j_g,pred_index_g);
						index_g=bintodec(index_g_bin);
						index_gf=gen_index(index_g,h);
						pred_g=get_pred(index_gf,2);

						index_k_bin=bin_addr_s.substr(j_k,k);
						index_k=bintodec(index_k_bin);
						pred_cht=get_pred(index_k,3);

						//taken or not taken actual
						if(hex_addr[line.length()-1]=='t'){
								pred_act=1;
						}
						else if(hex_addr[line.length()-1]=='n'){
							pred_act=0;
						}


						//if pred_cht=1 gshare update
						if(pred_cht==1){
							pred=pred_g;
							update_table(pred_act,index_gf,2);
						}
						//if pred_cht=0 update bimodal
						else if(pred_cht==0){
							pred=pred_b;
							update_table(pred_act,index_b,1);
						}
					//update gbhr regardless
						update_bhr(pred_act);

						if(pred!=pred_act){
							mispreds++;
							}
						else
							corpreds++;

						if(pred_act==pred_b && pred_act!=pred_g && hyb->cht[index_k]>0){
							hyb->cht[index_k]--;
						}

						if(pred_act==pred_g && pred_act!=pred_b && hyb->cht[index_k]<3){
							hyb->cht[index_k]++;
						}


					}
						else cout<<"prediction type not recognized";
					}

					else
						cout<<"error check input arguments";
					line.clear();
				}
				file.close();
			}
	else cout<<"error file could not be opened";

		mispred_rate=(float(mispreds)/preds)*100;

//simulator output

		cout<<"number of predictions: "<<preds<<endl;
		//cout<<"number of correct predictions: "<<corpreds<<endl;
		cout<<"number of mispredictions: "<<mispreds<<endl;
		cout<<"misprediction rate: "<<setprecision(2)<<fixed<<mispred_rate<<"%"<<endl;
		if(pt==1){
			cout<<"FINAL BIMODAL CONTENTS"<<endl;
			for(i=0;i<pow(2,pred_index_b);i++){
				cout<<i<<"	"<<bim->pb[i]<<endl;
			}
		}
		if(pt==2){
			cout<<"FINAL GSHARE CONTENTS"<<endl;
			for(i=0;i<pow(2,pred_index_g);i++){
				cout<<i<<"	"<<gsh->pb[i]<<endl;
			}
		}
		if(pt==3){
			cout<<"FINAL CHOOSER CONTENTS"<<endl;
			for(i=0;i<pow(2,k);i++){
				cout<<i<<"	"<<hyb->cht[i]<<endl;
			}
			cout<<"FINAL GSHARE CONTENTS"<<endl;
			for(i=0;i<pow(2,pred_index_g);i++){
				cout<<i<<"	"<<gsh->pb[i]<<endl;
			}
			cout<<"FINAL BIMODAL CONTENTS"<<endl;
			for(i=0;i<pow(2,pred_index_b);i++){
				cout<<i<<"	"<<bim->pb[i]<<endl;
			}
		}
return (0);

}

