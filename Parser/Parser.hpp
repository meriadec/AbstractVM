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
		void parse (T & stream) const
		{
			std::string		line;

			while (getline(stream, line) && line != ";;") {
				this->acquireLine(line);
				Vm::single().incLine();
			}
		}

		void parseFromStdin	(void) const;
		void parseFromFile	(char * file) const;

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

		/**
		 * Parsing
		 */
		void	acquireLine		(std::string & line) const;
		bool	isUseless		(std::string & line) const;

};

#endif
