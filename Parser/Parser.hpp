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

#ifndef PARSER_CLASS
# define PARSER_CLASS

# include "avm.hpp"
# include "Vm.hpp"

# include <iostream>
# include <string>

class Parser {

	public:

		Parser (void);
		Parser (Parser const & ref);
		~Parser (void);

		Parser & operator= (Parser const & ref);

		template<typename T>
		int parse (T & stream) const
		{
			std::string		line;
			unsigned int	i = 1;
			int				ret = 0;

			while (getline(stream, line) && (Vm::single().readFile || line != ";;")) {
				try {
					this->acquireLine(line, i);
				} catch (SyntaxException & e) {
					display_err("Syntax Error", e, true);
					ret = 1;
				}
				++i;
			}
			return ret;
		}

		int parseFromStdin	(void) const;
		int parseFromFile	(char * file) const;

	private:

		class BadFileException : public std::exception {
			virtual const char * what (void) const throw ()
			{
				return "bad input file";
			}
		};

		class UnknownInstructionException : public SyntaxException {
			virtual const char * what (void) const throw ()
			{
				return "unknown instruction";
			}
		};

		class BadInstructionException : public SyntaxException {
			virtual const char * what (void) const throw ()
			{
				return "instruction bad format";
			}
		};

		class UnknownTypeException : public SyntaxException {
			virtual const char * what (void) const throw ()
			{
				return "unknown type";
			}
		};

		/**
		 * Parsing
		 */
		void	acquireLine		(std::string & line, unsigned int i) const;
		bool	isUseless		(std::string & line) const;

};

#endif
