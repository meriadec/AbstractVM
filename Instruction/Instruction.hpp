/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/14 12:21:23        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#ifndef INSTRUCTION_CLASS
# define INSTRUCTION_CLASS

# include "avm.hpp"

class Instruction {

	public:

		Instruction		(basicInType);
		Instruction		(complexInType fn, std::string param);
		~Instruction	(void);

	private:

		Instruction (void);
		Instruction (Instruction const & ref);
		Instruction & operator= (Instruction const & ref);

		basicInType				_basicIn;
		complexInType			_complexIn;
		std::string				_param;

};

#endif
