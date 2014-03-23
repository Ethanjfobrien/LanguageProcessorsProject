/*
        sdis.c

        "Disassembler" for the stack machine. One routine which takes
        an instruction pointer and the address of a string and disassembles
        the instruction into the string.
*/

#include <stdio.h>
#include <string.h>
#include "sim.h"
#include "sdis.h"

char *mnemonics[] = { "Halt", "Add", "Sub", "Mult", "Div", "Neg", "Br", 
                      "Bgz", "Bg", "Blz", "Bl", "Bz", "Bnz", "Call", "Ret", 
                      "Bsf", "Rsf", "Ldp", "Rdp", "Inc", "Dec", "Push", 
                      "Load", "Load", "Load", "Load", "Store", "Store", 
                      "Store", "Read", "Write" };

void Disassemble( INSTRUCTION *inst, char *buffer )
{
    char temp[10];

    if ( inst->opcode < 0 || inst->opcode > WRITE )  {
        sprintf( buffer, "Unknown opcode %d\n", inst->opcode );
    }
    else  {
        strcpy( temp, mnemonics[inst->opcode] ); 
        switch ( inst->opcode )  {
            case  HALT:
            case  ADD:
            case  SUB:
            case  MULT:
            case  DIV:
            case  NEG:
            case  RET:
            case  BSF:
            case  RSF:
            case  READ:
            case  WRITE:    strcpy( buffer, temp );
                            break;
            case  BR:
            case  BGZ:
            case  BG:
            case  BLZ:
            case  BL:
            case  BZ:
            case  BNZ:
            case  CALL:
            case  LDP:
            case  RDP:
            case  INC:
            case  DEC:
            case  LOADA:
            case  STOREA:   sprintf( buffer, "%-8s%-4d", temp, inst->offset );
                            break;
            case  PUSHFP:   sprintf( buffer, "%-8sFP", temp );
                            break;
            case  LOADI:    sprintf( buffer, "%-8s#%-4d", temp, inst->offset );
                            break;
            case  LOADFP:
            case  STOREFP:  
                if ( inst->offset == 0 )  sprintf( buffer, "%-8sFP", temp );
                else  sprintf( buffer, "%-8sFP%-+4d", temp, inst->offset );
                break;
            case  LOADSP:
            case  STORESP:  
                if ( inst->offset == 0 )  sprintf( buffer, "%-8s[SP]", temp );
                else  sprintf( buffer, "%-8s[SP]%-+4d", temp, inst->offset );
                break;
            default:
                fprintf( stderr, "Error - shouldn't be here, %d %d\n",
                         inst->opcode, inst->offset );
                break;
        }
    }
}

