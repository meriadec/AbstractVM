/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/14 12:24:38        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#include "Parser.hpp"

#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>

Parser::Parser (void)
{
}

Parser::Parser (Parser const & ref)
{
	*this = ref;
}

Parser::~Parser (void)
{
}

Parser & Parser::operator= (Parser const & ref)
{
	(void) ref;
	return *this;
}

int Parser::parseFromStdin (void) const
{
	Vm::single().readFile = false;
	return this->parse<std::istream>(std::cin);
}

int Parser::parseFromFile (char * filename) const
{
	int ret = 0;
	Vm::single().readFile = true;
	std::ifstream file(filename);
	if (!file.is_open()) { throw Parser::BadFileException(); }
	ret = this->parse<std::ifstream>(file);
	file.close();
	return ret;
}

/**
 * Parsing one single line
 */
void Parser::acquireLine (std::string & l, unsigned int num) const
{
	if (this->isUseless(l)) { return; }
	Vm::single().setLine(num);

	std::map<std::string, basicInType> basicInstr = {
		{ "pop",	&Vm::pop },
		{ "dump",	&Vm::dump },
		{ "add",	&Vm::add },
		{ "sub",	&Vm::sub },
		{ "mul",	&Vm::mul },
		{ "div",	&Vm::div },
		{ "mod",	&Vm::mod },
		{ "print",	&Vm::print },
		{ "exit",	&Vm::exit }
	};

	std::map<std::string, complexInType> complexInstr = {
		{ "push",	&Vm::push },
		{ "assert",	&Vm::assert }
	};

	std::map<std::string, eOperandType> types = {
		{ "int8",	Int8 },
		{ "int16",	Int16 },
		{ "int32",	Int32 },
		{ "float",	Float },
		{ "double",	Double }
	};

	int			del		= l.find(" ");
	std::string	token	= l.substr(0, del);

	if (basicInstr[token]) {
		if (del != -1) { throw Parser::BadInstructionException(); }
		Vm::single().pushInstruction(basicInstr[token], num);
	}
	else if (complexInstr[token]) {
		std::string instr = token;
		if (del == -1) { throw Parser::BadInstructionException(); }
		++del;
		l.erase(0, del);
		del = l.find("(");
		if (del == -1) { throw Parser::BadInstructionException(); }
		std::string type = l.substr(0, del);
		if (!(types[type])) { throw Parser::UnknownTypeException(); }
		l.erase(0, del + 1);
		if (l[l.size() - 1] != ')') { throw Parser::BadInstructionException(); }
		token = l.substr(0, l.size() - 1);

		if (type == "float" || type == "double") {
			if (!std::regex_match(token, std::regex("[-]?[0-9]+\\.[0-9]+"))) {
				throw Parser::BadInstructionException();
			}
		}
		else if (!std::regex_match(token, std::regex("[-]?[0-9]+"))) {
			throw Parser::BadInstructionException();
		}

		Vm::single().pushInstruction(types[type], complexInstr[instr], token, num);
	}
	else { throw Parser::UnknownInstructionException(); }
}

/**
 * Test if line is useless
 */
bool Parser::isUseless (std::string & line) const
{
	if (line == "") { return true; }
	if (line[0] == ';') { return true; }
	return false;
}
