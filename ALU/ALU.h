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

	sc_signal< sc_uint<8> > sg1;

	void alu(){

		switch(inst.read()){

			case 1: 

				adder -> a_in(op2);
				adder -> b_in(op3);
				adder -> out(sg1);

				pipe3 -> clk(clk);
				pipe3 -> alu(sg1);
				pipe3 -> alu_result(alu_out);

			break;

			case 2: 

				substract -> a_in(op2);
				substract -> b_in(op3);
				substract -> out(sg1);

				pipe3 ->clk(clk);
				pipe3 -> alu(sg1);
				pipe3 -> alu_result(alu_out);

			break;

			default: break;


		}

	}

	~ALU(){

		delete substract;
		delete adder;
		delete pipe3;

	}

	SC_CTOR(ALU){

		adder = new Adder("adder");
		substract = new Substract("substract");
		pipe3 =  new Pipe3("pipe3");

		SC_METHOD(alu);
			sensitive << inst << op2 << op3;

	}
	
};

#endif