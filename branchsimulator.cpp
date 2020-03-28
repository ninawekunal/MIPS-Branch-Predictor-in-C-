#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <bitset>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main (int argc, char** argv) 
{

	bitset<32> baddr;
	string addrs;
	ifstream config;
	unsigned long addrab;
	config.open(argv[1]);
	int m, k, i;
	config >> m >> k;
	config.close();
	//cout<<"m and k"<<m<<"\n"<<k<<"\n";


	//Changed every type to unsigned int
	
	unsigned int ght=pow(2,k);
	unsigned int orf=pow(2,(k-1));
	unsigned int powah=pow(2,m);
	unsigned int pht[ght*powah];
	for (i=0;i<ght*powah;i++)
	{
		pht[i]=3;
		//cout<<pht[i];
	}
	ght=ght-1;
	//cout<<ght<<"\n"<<orf<<"\n"<<powah<<"\n"<<ght*powah<<"\n";
	bool prediction;
	if(m<=20 && k<=8)
		{
			ofstream out;
			string out_file_name = string(argv[2]) + ".out";
			out.open(out_file_name.c_str());
			
			ifstream trace;
			trace.open(argv[2]);
			unsigned long pc; bool taken;

			int counter=0;
			float acc=0.0;
			float corr=0.0;
			trace >> std::hex >> pc >> taken;
			unsigned int addra=pc & int(pow(2, m) - 1);
			unsigned int index = addra + int(ght*pow(2, m));

			while (!trace.eof()) 
			{
				counter=counter+1;
				
				prediction = (int)pht[index] >= 2;

				if (taken == 0)
				{
					if (pht[addra + powah * ght] == 3)
					{
						pht[addra + powah * ght] = 2;
					}
					else
					{
						if (pht[addra + powah * ght] == 2 || pht[addra + powah * ght] == 1)
						{
							pht[addra + powah * ght] = 0;
						}
					}
					
					ght = ght >> 1;

				}

				else
				{
					if (pht[addra + powah * ght] == 0)
					{
						pht[addra + powah * ght] = 1;
					}
					else
					{
						if (pht[addra + powah * ght] == 2 || pht[addra + powah * ght] == 1)
						{
							pht[addra + powah * ght] = 3;
						}
					}
					
					ght = ght >> 1;
					ght = ght | orf;

				}

				if(prediction == taken) {
					corr++;
				}
				out << prediction << endl;
				
				trace >> std::hex >> pc >> taken;
				addra=pc & int(pow(2, m) - 1);				
				index = addra + int(ght*pow(2, m));

			}
			acc=corr/counter;
			cout<<"\n accuracy:"<<acc*100;
			trace.close();	
			out.close();
		}

	else
		{
			cout<<"m should be less than 20 and k should be less than 8"<<"\n";
		}
	
}