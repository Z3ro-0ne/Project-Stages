#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include <Adder.h>
#include <Substract.h>
#include <Pipe3.h>

SC_MODULE(ALU){

	sc_in< sc_uint<4> > inst, op1, op2, op3;
	sc_in<bool> clk;
	sc_out< sc_uint<8> > alu_out;

	Adder *adder;
	Substract *substract;
	Pipe3 *pipe3;

	sc_signal< sc_uint<8> > alu_out_sg;

	
	SC_CTOR(ALU){

		adder = new Adder("adder");
		substract = new Substract("substract");
		pipe3 =  new Pipe3("pipe3");

		if(inst.read() == 2){

			adder -> a_in(op2);
			adder -> b_in(op3);
			adder -> out(alu_out_sg);

		} else {

			if(inst.read() == 3){

				substract -> a_in(op2);
				substract -> b_in(op3);
				substract -> out(alu_out_sg);

			}

		}

		pipe3 -> alu(alu_out_sg);
		pipe3 -> alu_result(alu_out);


	}

	~ALU(){

		delete substract;
		delete adder;
		delete pipe3;

	}
	
};

#endif