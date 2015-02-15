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

#include "Instruction.hpp"

Instruction::Instruction (basicInType fn, unsigned int num): basicIn(fn), complexIn(NULL), num(num)
{
}

Instruction::Instruction (eOperandType type, complexInType fn, std::string param, unsigned int num): basicIn(NULL), complexIn(fn), param(param), type(type), num(num)
{
}

Instruction::~Instruction (void)
{
}
