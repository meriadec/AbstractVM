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
			std::string line;

			while (getline(stream, line) && line != ";;") {
				std::cout << line << std::endl;
			}
		}

		void parseFromStdin	(void) const;
		void parseFromFile	(char * file) const;

	private:

};

#endif
