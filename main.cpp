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

int main (void)
{
	Vm vm = Vm::single();

	IOperand const * test  = vm.createOperand(Int8, "20");
	IOperand const * test2 = vm.createOperand(Int16, "22");
	IOperand const * res   = (*test) + (*test2);

	std::cout << "ce que l'on veut:" << std::endl;
	std::cout << "42" << std::endl;
	std::cout << "ce que l'on a   :" << std::endl;
	std::cout << res << std::endl;

	return (0);
}
