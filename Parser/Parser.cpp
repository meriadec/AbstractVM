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
#include <iostream>
#include <fstream>

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
void Parser::acquireLine (std::string & line) const
{
	if (this->isUseless(line)) { return; }
	std::cout << line << std::endl;
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
