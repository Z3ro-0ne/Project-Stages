#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <systemc.h>
#include <Pipe4.h>
#include <Decoder2.h>
#include <RegisterFile.h>

SC_MODULE(DataMemory){

	sc_in< sc_uint<16> > instruction_og;
	sc_in< sc_uint<8> > alu_result;
	sc_in<bool> clk;

	sc_out< sc_uint<4> > register_dir_WB;
	sc_out< sc_uint<8> > data_WB;

	Decoder2 *decoder2;
	RegisterFile *reg_file;
	Pipe4 *pipe4;

	sc_signal< sc_uint<4> > sg1, sg2, sg4;
	sc_signal< sc_uint<8> > sg3, sg5;

	SC_CTOR(DataMemory){

		decoder2 = new Decoder2("decoder2");
		reg_file = new RegisterFile("reg_file");
		pipe4 = new Pipe4("pipe4");

		decoder2 -> inst_in(instruction_og);
		decoder2 -> inst_out(sg1);
		decoder2 -> dir_reg(sg2);
		decoder2 -> dir_data(sg3);

		reg_file -> instru_in(sg1);
		reg_file -> dir_reg_in(sg2);
		reg_file -> dir_data_in(sg3);
		reg_file -> data_in(alu_result);
		reg_file -> dir_reg_out(sg4);
		reg_file -> data_out(sg5);

		pipe4 -> clk(clk);
		pipe4 -> dir_reg_in(sg4);
		pipe4 -> data_in(sg5);
		pipe4 -> dir_reg_out(register_dir_WB);
		pipe4 -> data_out(data_WB);

	}

	~DataMemory(){

		delete pipe4;
		delete decoder2;
		delete reg_file;
	}

};

#endif