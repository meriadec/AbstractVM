/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 16:57:49        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#include <map>
#include "Vm.hpp"

Vm::Vm (void)
{
}

Vm::~Vm (void)
{
}

IOperand const * Vm::createInt8 (std::string const & value) const
{
	return new Operand<int8_t>(value, Int8);
}

IOperand const * Vm::createInt16 (std::string const & value) const
{
	return new Operand<int16_t>(value, Int16);
}

IOperand const * Vm::createInt32 (std::string const & value) const
{
	return new Operand<int32_t>(value, Int32);
}

IOperand const * Vm::createFloat (std::string const & value) const
{
	return new Operand<float>(value, Float);
}

IOperand const * Vm::createDouble (std::string const & value) const
{
	return new Operand<double>(value, Double);
}

IOperand const * Vm::createOperand (eOperandType type, std::string const & value) const
{
	static std::map<eOperandType, fType> m = {
		{ Int8, &Vm::createInt8 },
		{ Int16, &Vm::createInt16 },
		{ Int32, &Vm::createInt32 },
		{ Float, &Vm::createDouble },
		{ Double, &Vm::createDouble }
	};
	return (this->*(m[type]))(value);
}
