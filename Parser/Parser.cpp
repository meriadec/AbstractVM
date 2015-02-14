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

void Parser::parseFromStdin (void) const
{
	this->parse<std::istream>(std::cin);
}

void Parser::parseFromFile (char * filename) const
{
	std::ifstream file(filename);
	if (!file.is_open()) { throw Parser::BadFileException(); }
	this->parse<std::ifstream>(file);
	file.close();
}

/**
 * Parsing one single line
 */
void Parser::acquireLine (std::string & l) const
{
	if (this->isUseless(l)) { return; }

	static std::map<std::string, basicInType> basicInstr = {
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

	static std::map<std::string, complexInType> complexInstr = {
		{ "push",	&Vm::push },
		{ "assert",	&Vm::assert }
	};

	std::string token = l.substr(0, l.find(" "));

	if (basicInstr[token]) {
		std::cout << "token [" << token << "]" << std::endl;
	}
	else if (complexInstr[token]) {
		std::cout << "complex token [" << token << "]" << std::endl;
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
