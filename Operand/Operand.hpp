/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 15:33:26        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#ifndef OPERAND_CLASS
# define OPERAND_CLASS

# include "IOperand.hpp"

template<typename T>
class Operand : public IOperand {

	public:

		Operand (void)
		{
			std::cout << "constructing operand..." << std::endl;
		}

		~Operand (void)
		{
			std::cout << "destructing operand..." << std::endl;
		}

		Operand & operator= (TOperand const & ref)
		{
		}

		int getPrecision (void) const
		{
		}

		eOperandType getType (void) const
		{
		}

		IOperand const * operator+ (IOperand const & rhs) const
		{
		}

		IOperand const * operator- (IOperand const & rhs) const
		{
		}

		IOperand const * operator* (IOperand const & rhs) const
		{
		}

		IOperand const * operator/ (IOperand const & rhs) const
		{
		}

		IOperand const * operator% (IOperand const & rhs) const
		{
		}

		std::string const & toString (void) const
		{
		}

		/**
		 * Factory method for create new operand
		 */
		IOperand const * createOperand (eOperandType type, std::string const & value) const
		{
		}

	private:

		Operand (Operand const & ref);

		std::string						_heib;

};

#endif
