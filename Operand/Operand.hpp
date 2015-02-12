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

		Operand (std::string const & value, eOperandType type, int precision) : _str(value), _type(type), _precision(precision)
		{
		}

		~Operand (void)
		{
		}

		Operand & operator= (Operand const & ref)
		{
			this->_str = ref.toString();
		}

		int getPrecision (void) const
		{
			return this->_precision;
		}

		eOperandType getType (void) const
		{
			return this->_type;
		}

		IOperand const * operator+ (IOperand const & rhs) const
		{
			(void) rhs;
			return NULL;
		}

		IOperand const * operator- (IOperand const & rhs) const
		{
			(void) rhs;
			return NULL;
		}

		IOperand const * operator* (IOperand const & rhs) const
		{
			(void) rhs;
			return NULL;
		}

		IOperand const * operator/ (IOperand const & rhs) const
		{
			(void) rhs;
			return NULL;
		}

		IOperand const * operator% (IOperand const & rhs) const
		{
			(void) rhs;
			return NULL;
		}

		std::string const & toString (void) const
		{
			return this->_str;
		}

	private:

		Operand (void);
		Operand (Operand const & ref);

		std::string						_str;
		eOperandType					_type;
		int								_precision;

};

#endif
