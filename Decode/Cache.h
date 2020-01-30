#ifndef CACHE_H
#define CACHE_H

#include <systemc.h>
#include <iomanip>

SC_MODULE(Cache){

	sc_in< sc_uint<4> >dir_inst, dir1, dir2, dir3 ;
	//sc_in< sc_uint<4> > inst_cache, data1_cache, data2_cache, data3_cache;
	sc_out< sc_uint<4> > inst_out, data1_out, data2_out, data3_out;

	sc_uint<16> storage[16];

	sc_in<bool> clk;
	//sc_in<bool> activate_writing;

	void read(){

		if(clk.read() == 0){
			
			inst_out = storage[dir_inst.read()];
			data1_out = storage[dir1.read()];
			data2_out = storage[dir2.read()];
			data3_out = storage[dir3.read()];
		
		}

	}

	void write(){

		if(clk.read() /*and activate_writing.read()*/){

			storage[dir_inst.read()] = dir_inst.read();
			storage[dir1.read()] = dir1.read();
			storage[dir2.read()] = dir2.read();
			storage[dir3.read()] = dir3.read();

			/*for(int i = 0; i < 16; i++){

				std::cout <<"Localidad: "<< std::setw(3) << i <<" :";

				for(int j = 15; j >= 0; --j){

					std::cout<<storage[i].range(j,j);

				}

				std::cout<<"\n"; 

			}

			std::cout<<"\n";*/

		}

	}

	SC_CTOR(Cache){

		SC_METHOD(read);
			sensitive << clk.neg();
		SC_METHOD(write);
			sensitive << clk.pos();

	}

};

#endif