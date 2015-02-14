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

Vm::Vm (void): _line(0)
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

void Vm::execute (void)
{
	std::cout << "executing program..." << std::endl;
}

unsigned int Vm::getLine (void) const
{
	return this->_line;
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

/**
 * Push
 */
void Vm::push (eOperandType type, std::string const & value)
{
	this->_stack.push_front(this->createOperand(type, value));
}

void Vm::push (IOperand const * op)
{
	this->_stack.push_front(op);
}

/**
 * Pop
 */
void Vm::pop (void)
{
	if (this->_stack.size() == 0) { throw Vm::NotEnoughElementsException(); }
	delete *(this->_stack.begin());
	this->_stack.pop_front();
}

/**
 * Dump
 */
void Vm::dump (void) const
{
	std::list<IOperand const *>::const_iterator it = this->_stack.begin();
	while (it != this->_stack.end()) {
		std::cout << (*it)->toString() << std::endl;
		++it;
	}
}

/**
 * Assert
 */
void Vm::assert (IOperand const * op) const
{
	IOperand const * top = *(this->_stack.begin());
	if (top->getType() != op->getType() || top->toString() != op->toString()) {
		throw Vm::AssertFailedException();
	}
}

void Vm::assert (eOperandType type, std::string const & value) const
{
	IOperand const * tmp = this->createOperand(type, value);
	this->assert(tmp);
	delete tmp;
}

/**
 * Print
 */
void Vm::print (void) const
{
	IOperand const * top = *(this->_stack.begin());
	IOperand const * tmp = this->createOperand(Int8, top->toString());
	this->assert(tmp);
	int c;
	std::stringstream ss;
	ss << top->toString();
	ss >> c;
	std::cout << static_cast<char>(c) << std::endl;
	delete tmp;
}

/**
 * Exit
 */
void Vm::exit (void)
{
	std::cout << "Exiting this shit." << std::endl;
}

/**
 * Operations
 * ----------
 */

/**
 * Add
 */
void Vm::add (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 + *op2);
}

/**
 * Sub
 */
void Vm::sub (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 - *op2);
}

/**
 * Mul
 */
void Vm::mul (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 * *op2);
}

/**
 * Div
 */
void Vm::div (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 / *op2);
}

/**
 * Mod
 */
void Vm::mod (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	this->push(*op1 % *op2);
}
