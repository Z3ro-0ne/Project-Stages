#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>
#include <iomanip>

SC_MODULE(TestBench){

	sc_in< sc_uint<16> > inst;
	sc_in<bool> clk;

	void output(){

		for(int i = 0; i < 16 ; i++){

			std::cout << inst.read().range(16-(i+1), 16-(i+1));
		}

		std::cout << " | " << std::setw(5) << inst.read() << " | " << clk.read() << std::endl;

	}

	void test(){

		std::cout <<"Instruction      | Value | CLK" << std::endl;

		for(int i = 0; i < 5 ; i++){

			wait();
			output();

		}

		sc_stop();

	}

	SC_CTOR(TestBench){

		SC_THREAD(test);
		sensitive << clk.neg();

	}

};

#endif