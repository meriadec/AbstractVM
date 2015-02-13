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

#include "Vm.hpp"
#include "Operand.hpp"

#include <map>
#include <iterator>

Vm::Vm (void)
{
}

Vm::Vm (Vm const & ref)
{
	*this = ref;
}

Vm::~Vm (void)
{
}

Vm & Vm::operator= (Vm const & ref)
{
	static_cast<void>(ref);
	return *this;
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

Vm & Vm::single (void)
{
	static Vm vm;
	return vm;
}

void Vm::push (eOperandType type, std::string const & value)
{
	this->_stack.push_front(this->createOperand(type, value));
}

void Vm::push (IOperand const * op)
{
	this->_stack.push_front(op);
}

void Vm::pop (void)
{
	delete *(this->_stack.begin());
	this->_stack.pop_front();
}

void Vm::dump (void) const
{
	std::list<IOperand const *>::const_iterator it = this->_stack.begin();
	while (it != this->_stack.end()) {
		std::cout << (*it)->toString() << std::endl;
		++it;
	}
}

void Vm::add (void)
{
	if (this->_stack.size() < 2) { throw std::exception(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 + *op2);
}

void Vm::sub (void)
{
	if (this->_stack.size() < 2) { throw std::exception(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 - *op2);
}

void Vm::mul (void)
{
	if (this->_stack.size() < 2) { throw std::exception(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 * *op2);
}

void Vm::div (void)
{
	if (this->_stack.size() < 2) { throw std::exception(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 / *op2);
}

void Vm::mod (void)
{
	if (this->_stack.size() < 2) { throw std::exception(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 % *op2);
}
