#ifndef _ZINST_H
#define _ZINST_H

PLIST_t refer(PLIST_t op);
PLIST_t inst8(INST_e inst, PLIST_t op1, PLIST_t op2);
PLIST_t inst16(INST_e inst, PLIST_t op1, PLIST_t op2);
PLIST_t instr(INST_e inst, PLIST_t op1, PLIST_t op2);
PLIST_t newaddress(PIDENT_t ident, int disp);

PLIST_t instr_ldcc(DIR_e cc); /* LDCC */
void instr_jpcc(DIR_e cc, PCR_t crlabel); /* JP cc */
PCR_t get_jp(PCR_t label); /* JP .t. */

PLIST_t instr_modulus(PLIST_t op1, PLIST_t op2);

#endif
