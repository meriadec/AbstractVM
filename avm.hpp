/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 15:21:27        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#ifndef AVM_H
# define AVM_H

# include <iostream>

/**
 * Exceptions
 */

class SyntaxException    : public std::exception {};
class ExecutionException : public std::exception {};

enum eOperandType
{
	Int8 = 1,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand;
class Vm;

typedef IOperand const * (Vm:: * fType)(std::string const & value) const;
typedef void (Vm:: * basicInType)(void);
typedef void (Vm:: * complexInType)(IOperand const * op);

#endif
