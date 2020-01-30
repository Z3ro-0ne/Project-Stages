#ifndef REGISTERMEMORY_H
#define REGISTERMEMORY_H

#include <systemc.h>
#include <Decode.h>
#include <Cache.h>
#include <Pipe2.h>

SC_MODULE(RegisterMemory){

	sc_in< sc_uint<16> > instruction_in;
	sc_in<bool> clk;

	sc_out< sc_uint<4> > inst, data1, data2, data3;

	Decode *decode;
	Cache *cache;
	Pipe2 *pipe2;

	sc_signal< sc_uint<4> > inst_decode_sg, op1_out_sg, op2_out_sg, op3_out_sg;
	sc_signal< sc_uint<4> > inst_cache_sg, data1_cache_sg, data2_cache_sg, data3_cache_sg;

	SC_CTOR(RegisterMemory){

		decode = new Decode("decode");
		cache = new Cache("cache");
		pipe2 = new Pipe2("pipe2");

		decode -> inst_in(instruction_in);
		decode -> inst_out(inst_decode_sg);
		decode -> op1(op1_out_sg);
		decode -> op2(op2_out_sg);
		decode -> op3(op3_out_sg);

		cache -> clk(clk);
		cache -> dir_inst(inst_decode_sg);
		cache -> dir1(op1_out_sg);
		cache -> dir2(op2_out_sg);
		cache -> dir3(op3_out_sg);
		cache -> inst_out(inst_cache_sg);
		cache -> data1_out(data1_cache_sg);
		cache -> data2_out(data2_cache_sg);
		cache -> data3_out(data3_cache_sg);

		pipe2 -> clk(clk);
		pipe2 -> inst_in(inst_cache_sg);
		pipe2 -> data1_in(data1_cache_sg);
		pipe2 -> data2_in(data2_cache_sg);
		pipe2 -> data3_in(data3_cache_sg);
		pipe2 -> inst_out(inst);
		pipe2 -> data1_out(data1);
		pipe2 -> data2_out(data2);
		pipe2 -> data3_out(data3);


	}


	~RegisterMemory(){

		delete pipe2;
		delete decode;
		delete cache;
	}

};

#endif