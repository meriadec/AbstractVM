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
	for (std::list<IOperand const *>::iterator it = this->_stack.begin(); it != this->_stack.end(); it++) {
		delete *it;
	}
	for (std::list<Instruction const *>::iterator it = this->_instructions.begin(); it != this->_instructions.end(); it++) {
		delete *it;
	}
}

Vm & Vm::operator= (Vm const & ref)
{
	static_cast<void>(ref);
	return *this;
}

void Vm::execute (void)
{
	this->resetLine();
	std::list<Instruction const *>::const_iterator it = this->_instructions.begin();
	while (it != this->_instructions.end()) {
		Instruction const * inst = *it;
		if (inst->basicIn) {
			(this->*(inst->basicIn))();
		}
		else {
			IOperand const * op = this->createOperand(inst->type, inst->param);
			(this->*(inst->complexIn))(op);
		}
		if (it == std::prev(this->_instructions.end()) && inst->basicIn != &Vm::exit) {
			throw Vm::NoExitException();
		}
		this->incLine();
		++it;
	}
}

unsigned int Vm::getLine (void) const
{
	return this->_line;
}

void Vm::incLine (void)
{
	++(this->_line);
}

void Vm::resetLine (void)
{
	this->_line = 1;
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
void Vm::dump (void)
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
void Vm::assert (IOperand const * op)
{
	IOperand const * top = *(this->_stack.begin());
	if (top->getType() != op->getType() || top->toString() != op->toString()) {
		throw Vm::AssertFailedException();
	}
}

void Vm::assert (eOperandType type, std::string const & value)
{
	IOperand const * tmp = this->createOperand(type, value);
	this->assert(tmp);
	delete tmp;
}

/**
 * Print
 */
void Vm::print (void)
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
	// lol
	throw AllIsOkException();
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
	IOperand const * res = *op1 + *op2;
	this->pop();
	this->pop();
	this->push(res);
}

/**
 * Sub
 */
void Vm::sub (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	IOperand const * res = *op2 - *op1;
	this->pop();
	this->pop();
	this->push(res);
}

/**
 * Mul
 */
void Vm::mul (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	IOperand const * res = *op1 * *op2;
	this->pop();
	this->pop();
	this->push(res);
}

/**
 * Div
 */
void Vm::div (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	IOperand const * res = *op2 / *op1;
	this->pop();
	this->pop();
	this->push(res);
}

/**
 * Mod
 */
void Vm::mod (void)
{
	if (this->_stack.size() < 2) { throw Vm::NotEnoughElementsException(); }
	IOperand const * op1 = *(this->_stack.begin());
	IOperand const * op2 = *(std::next(this->_stack.begin()));
	IOperand const * res = *op2 % *op1;
	this->pop();
	this->pop();
	this->push(res);
}

/**
 * Push instruction
 */
void Vm::pushInstruction (basicInType fn)
{
	Instruction const * inst = new Instruction(fn);
	this->_instructions.push_back(inst);
}

void Vm::pushInstruction (eOperandType type, complexInType fn, std::string param)
{
	Instruction const * inst = new Instruction(type, fn, param);
	this->_instructions.push_back(inst);
}
