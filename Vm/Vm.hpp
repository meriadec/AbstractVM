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

#ifndef VM_CLASS
# define VM_CLASS

# include "Operand.hpp"

class Vm {

	public:

		Vm (void);
		~Vm (void);

		/**
		 * Factory method for create new operand
		 */
		IOperand const * createOperand (eOperandType type, std::string const & value) const;

	private:

		Vm (Vm const & ref);
		Vm & operator= (Vm const & ref);

		IOperand const * createInt8		(std::string const & value) const;
		IOperand const * createInt16	(std::string const & value) const;
		IOperand const * createInt32	(std::string const & value) const;
		IOperand const * createFloat	(std::string const & value) const;
		IOperand const * createDouble	(std::string const & value) const;

};

typedef IOperand const * (Vm:: * fType)(std::string const & value) const;

#endif
