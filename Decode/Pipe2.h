#ifndef PIPE2_H
#define PIPE2_H

#include <systemc.h>

SC_MODULE(Pipe2){

	sc_in<bool> clk;
	sc_in< sc_uint<4> > inst_in, data1_in, data2_in, data3_in;
	sc_out< sc_uint<4> > inst_out, data1_out, data2_out, data3_out;

	sc_uint <4> load_inst, load_data1, load_data2, load_data3;

	void receive(){

		load_inst = inst_in;
		load_data1 = data1_in;
		load_data2 = data2_in;
		load_data3 = data3_in;

	}

	void exit(){

		inst_out = load_inst;
		data1_out = load_data1;
		data2_out = load_data2;
		data3_out = load_data3;

	}

	SC_CTOR(Pipe2){

		SC_METHOD(receive);
			sensitive << clk.pos();
		SC_METHOD(exit);
			sensitive << clk.neg();

	}

};

#endif