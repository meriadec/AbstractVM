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

		vm.push(Int8, "2");
		vm.push(Int8, "2");
		vm.push(Int8, "2");
		vm.dump();
		vm.pop();

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
