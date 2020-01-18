#include <systemc.h>

#include <TestBench.h>
#include <Fetch.h>

int sc_main(int argv, char* argc[]){

	  sc_time PERIOD(10,SC_NS);
  	sc_time DELAY(10,SC_NS);
  	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

  	Fetch ft("ft");
  	TestBench tb("tb");

  	sc_signal< sc_uint<16> > inst;

  	ft.inst(inst);
  	ft.clk(clock);

  	tb.inst(inst);
  	tb.clk(clock);

  	sc_start();

	return 0;
}