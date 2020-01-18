#ifndef FETCH_H
#define FETCH_H

#include <systemc.h>
#include <fstream>

SC_MODULE(Fetch){

	ifstream isa_file;
	sc_in<bool> clk;
	sc_out< sc_uint<16> > inst;

	void fetch(){

		std::string line;
		sc_uint <16> aux;
		std::getline(isa_file, line);
		
		for(int i = 0; i < 16 ; i++){

			aux[i] = line[16-(i+1)]-'0';

		}

		inst = aux;

	}

	SC_CTOR(Fetch){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
		sensitive << clk.neg();

	}

	~Fetch(){

		isa_file.close();

	}

};


#endif  