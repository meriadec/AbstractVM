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

# include "IOperand.hpp"

# include <list>
# include <stdexcept>

class Vm {

	public:

		static Vm & single (void);

		Vm	(void);
		Vm	(Vm const & ref);
		~Vm	(void);

		Vm & operator= (Vm const & ref);

		/**
		 * Factory method for create new operand
		 */
		IOperand const * createOperand (eOperandType type, std::string const & value) const;

		/**
		 * Push at the top of the stack
		 */
		void push (eOperandType type, std::string const & value);
		void push (IOperand const * op);

		/**
		 * Remove the element at the top of the stack
		 */
		void pop (void);

		/**
		 * Show all elements of the stack
		 */
		void dump (void) const;

		/**
		 * Assert the value at the top of the stack
		 */
		void assert (IOperand const * op) const;
		void assert (eOperandType type, std::string const & value) const;

		/**
		 * Print the value at the top of the stack
		 */
		void print (void) const;

		/**
		 * Exit the subprogram
		 */
		void exit (void);

		/**
		 * Operations
		 */
		void add (void);
		void sub (void);
		void mul (void);
		void div (void);
		void mod (void);

	private:

		IOperand const * createInt8		(std::string const & value) const;
		IOperand const * createInt16	(std::string const & value) const;
		IOperand const * createInt32	(std::string const & value) const;
		IOperand const * createFloat	(std::string const & value) const;
		IOperand const * createDouble	(std::string const & value) const;

		std::list<IOperand const *>			_stack;

		/**
		 * Exceptions
		 */

		class NotEnoughElementsException : public std::exception {
			virtual const char * what (void) const throw ()
			{
				return "not enough elements in stack";
			}
		};

		class AssertFailedException : public std::exception {
			virtual const char * what (void) const throw ()
			{
				return "assertion failed";
			}
		};

};

typedef IOperand const * (Vm:: * fType)(std::string const & value) const;

#endif
