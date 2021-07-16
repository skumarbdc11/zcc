#ifndef _INST_H
#define _INST_H

PCR_t inst_op1(INST_e inst, NTYPE_e op1, PLIST_t opval);
PCR_t inst_op1_b(INST_e inst, NTYPE_e op1, PLIST_t opval);
PCR_t inst_op1_w(INST_e inst, NTYPE_e op1, PLIST_t opval);
PCR_t inst_op1_cc(DIR_e cc, NTYPE_e op1, PLIST_t opval); /* LDCC */
void inst_op1_jpcc(DIR_e cc, PLABEL_t label); /* JP cc */
void inst_call(PLABEL_t label);

PCR_t inst_op2(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_b(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_w(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_sb(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_sw(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_ub(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);
PCR_t inst_op2_uw(INST_e inst, NTYPE_e op1, NTYPE_e op2, PLIST_t optval1, PLIST_t optval2);

PCR_t inst_pushpop(INST_e inst, NTYPE_e op1, PLIST_t opval);
PCR_t inst_pushpop_b(INST_e inst, NTYPE_e op1, PLIST_t opval);
PCR_t inst_pushpop_w(INST_e inst, NTYPE_e op1, PLIST_t opval);

PCR_t inst_link(int stacksize);
void inst_unlink();
void inst_ret();

#endif
