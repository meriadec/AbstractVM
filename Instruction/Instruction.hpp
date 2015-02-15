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

		Instruction		(basicInType, unsigned int num);
		Instruction		(eOperandType type, complexInType fn, std::string param, unsigned int num);
		~Instruction	(void);

		basicInType				basicIn;
		complexInType			complexIn;
		std::string				param;
		eOperandType			type;
		unsigned int			num;

	private:

		Instruction (void);
		Instruction (Instruction const & ref);
		Instruction & operator= (Instruction const & ref);

};

#endif
