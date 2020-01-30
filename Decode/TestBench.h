#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>

SC_MODULE(TestBench){

	sc_out< sc_uint<16> > instruction_in;
	sc_in<bool> clk;

	sc_in< sc_uint<4> > inst, data1, data2, data3;

	void test(){

		instruction_in.write(2);//0000000000000010

		wait();
		output();

		/*instruction_in.write(2);//0000000000000010

		wait();
		output();

		instruction_in.write(19912);//0100110111001000

		wait();
		output();

		instruction_in.write(64674);//1111110010100010

		wait();
		output();

		instruction_in.write(21760);//0101010100000000

		wait();
		output();*/

		sc_stop();

	}


	void output(){

		std::cout<<"inst_in || inst || op1 || op2 || op3"<<std::endl;

		for(int i = 15; i >= 0; i--){

			std::cout<<instruction_in.read().range(i,i);

		}

		std::cout<<" || ";

		for(int i = 4; i >= 0; i--){

			std::cout<<inst.read().range(i,i);
			
		}

		std::cout<<" || ";

		for(int i = 4; i >= 0; i--){

			std::cout<<data1.read().range(i,i);
			
		}

		std::cout<<" || ";

		for(int i = 4; i >= 0; i--){

			std::cout<<data2.read().range(i,i);
			
		}

		std::cout<<" || ";

		for(int i = 4; i >= 0; i--){

			std::cout<<data3.read().range(i,i);
			
		}

		std::cout<<"\n\n";
	
	}

	SC_CTOR(TestBench){

		SC_THREAD(test)
			sensitive << clk;
			
	}

};

#endif