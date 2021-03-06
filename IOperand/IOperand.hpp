/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 15:05:06        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#ifndef IOPERAND_CLASS
# define IOPERAND_CLASS

# include <string>
# include "avm.hpp"

class IOperand {

	public:

		virtual int				getPrecision	(void) const = 0;
		virtual eOperandType	getType			(void) const = 0;

		virtual IOperand const * operator+ (IOperand const & rhs) const = 0;
		virtual IOperand const * operator- (IOperand const & rhs) const = 0;
		virtual IOperand const * operator* (IOperand const & rhs) const = 0;
		virtual IOperand const * operator/ (IOperand const & rhs) const = 0;
		virtual IOperand const * operator% (IOperand const & rhs) const = 0;

		virtual std::string const & toString (void) const = 0;

		virtual ~IOperand (void) {}

};

#endif
