/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 12:34:46        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#include <iostream>
#include "Vm.hpp"
#include "avm.hpp"

std::string getLine (void)
{
	return "Line 4: ";
}

int main (void)
{
	Vm vm = Vm::single();

	try {

		IOperand const * test  = vm.createOperand(Int8, "220");
		IOperand const * test2 = vm.createOperand(Int8, "22");
		IOperand const * res   = (*test) / (*test2);

		std::cout << "res = " << res->toString() << std::endl;

	}
	catch (SyntaxException & e) {
		std::cout << "Syntax Error: " << getLine() << e.what() << std::endl;
	}
	catch (ExecutionException & e) {
		std::cout << "Execution Error: " << getLine() << e.what() << std::endl;
	}
	catch (std::exception & e) {
		std::cout << "Unknown Error: " << getLine() << e.what() << std::endl;
	}

	return (0);
}
