#ifndef _ZEMIT_H

PLIST_t emit_lineno(PLIST_t arg1);

PLIST_t emit_negate(PLIST_t arg1);
PLIST_t emit_complement(PLIST_t arg1);
PLIST_t emit_not(PLIST_t arg1);

PLIST_t emit_multiply(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_divide(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_modulus(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_sub(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_add(PLIST_t arg1, PLIST_t arg2);

PLIST_t emit_leftshift(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_rightshift(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_logicaland(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_logicalxor(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_logicalor(PLIST_t arg1, PLIST_t arg2);

PLIST_t emit_lessthan(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_greaterthan(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_lessthanequal(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_greaterthanequal(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_equal(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_notequal(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_reland(PLIST_t arg1, PLIST_t arg2);
PLIST_t emit_relor(PLIST_t arg1, PLIST_t arg2);

PLIST_t emit_post(PLIST_t op, int add);
PLIST_t emit_pre(PLIST_t op, int add);
PLIST_t emit_arrayaccess(PLIST_t ident, PLIST_t exp);
PLIST_t emit_pointeraccess(PLIST_t ident);
PLIST_t emit_addressaccess(PLIST_t ident);
PLIST_t emit_functioncall(PLIST_t fname, PLIST_t args);

PLIST_t emit_assign(PLIST_t lhs, int op, PLIST_t rhs);

PCR_t emit_if(PLIST_t exp, PLIST_t val, PCR_t tblk, PCR_t fblk);
PCR_t emit_switch(PLIST_t val, PCR_t blk);
PCR_t emit_jp(PCR_t jmp_label);
int   emit_function(PCR_t pstmts);
void  emit_sym_decl(PLIST_t psymlist);

PCR_t prefix_label(PCR_t parent, PCR_t label);
PCR_t process_break_continue(PCR_t parent, PCR_t start_label);

#endif
