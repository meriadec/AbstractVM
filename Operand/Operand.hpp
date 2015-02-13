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

# include "Vm.hpp"
# include "IOperand.hpp"

# include <sstream>

template<typename T>
class Operand : public IOperand {

	public:

		/**
		 * Constructor / Destructor
		 */

		Operand (std::string const & value, eOperandType type) : _str(value), _type(type)
		{
		}

		virtual ~Operand (void)
		{
		}

		Operand & operator= (Operand const & ref)
		{
			this->_str = ref.toString();
		}

		/**
		 * Member functions
		 */

		int getPrecision (void) const
		{
			return this->_type;
		}

		eOperandType getType (void) const
		{
			return this->_type;
		}

		IOperand const * operator+ (IOperand const & rhs) const
		{
			eOperandType		type;
			double				d1;
			double				d2;

			this->_buildParams(rhs, type, d1, d2);

			std::stringstream ss;
			ss << (d1 + d2);

			return this->_renderOperand(type, ss);
		}

		IOperand const * operator- (IOperand const & rhs) const
		{
			eOperandType		type;
			double				d1;
			double				d2;

			this->_buildParams(rhs, type, d1, d2);

			std::stringstream ss;
			ss << (d1 - d2);

			return this->_renderOperand(type, ss);
		}

		IOperand const * operator* (IOperand const & rhs) const
		{
			eOperandType		type;
			double				d1;
			double				d2;

			this->_buildParams(rhs, type, d1, d2);

			std::stringstream ss;
			ss << (d1 - d2);

			return this->_renderOperand(type, ss);
		}

		IOperand const * operator/ (IOperand const & rhs) const
		{
			eOperandType		type;
			double				d1;
			double				d2;

			this->_buildParams(rhs, type, d1, d2);

			std::stringstream ss;
			ss << (d1 / d2);

			return this->_renderOperand(type, ss);
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

		/**
		 * Private constructors
		 */

		Operand (void);
		Operand (Operand const & ref);

		/**
		 * Private member functions
		 */

		void _buildParams (IOperand const & r2, eOperandType & type, double & d1, double & d2) const
		{
			std::stringstream ss1(this->toString());
			ss1 >> d1;

			std::stringstream ss2(r2.toString());
			ss2 >> d2;

			type = (this->getType() > r2.getType()) ? this->getType() : r2.getType();
		}

		IOperand const * _renderOperand (eOperandType & type, std::stringstream & ss) const
		{
			std::stringstream ss2;
			if (type == Int8 || type == Int16 || type == Int32) {
				int	tmp;
				ss >> tmp;
				ss2 << tmp;
			}
			else if (type == Float) {
				float tmp;
				ss >> tmp;
				ss2 << tmp;
			} else {
				ss2 << ss.str();
			}
			return Vm::single().createOperand(type, ss2.str());
		}

		/**
		 * Attributes
		 */

		std::string						_str;
		eOperandType					_type;

};

#endif
