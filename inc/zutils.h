#ifndef _UTILS_H

/* typedefs */
typedef enum const_type CONST_TYPE;

/* constant val */
enum const_type { HEX, OCT, DEC, FLT, CHR };
long get_intval(CONST_TYPE type, const char *data, unsigned char *sign);
double get_fltval(const char *data);

/* type size */
int typesize(PLIST_t node);
int get_structsize(PTYPE_t ptype);
int get_unionsize(PTYPE_t ptype);
int get_typesize(PTYPE_t ptype);
int get_integraltypesize(TYPE_e type);

/* TYPE_t */
PTYPE_t new_type(TYPE_e type, TYPE_e issigned, TYPE_e qualifier, int offset, TYPE_e specifier);
void add_subtype(PTYPE_t ptype, PTYPE_t psubtype);
void delete_type(PTYPE_t ptype);

/* DATA_t */
PDATA_t new_data(TYPE_e type, ...);
void delete_data(PDATA_t pdata);

/* IDENT_t */
PIDENT_t new_ident(const char *pident_name);
void delete_ident(PIDENT_t pident);
void ident_addstuff(PIDENT_t pident, TYPE_e ident_type, PTYPE_t pvar_type, PIDENT_t parg_list);
void add_argument(PIDENT_t pident, PIDENT_t parg);

/* LIST_t */
PLIST_t new_node(NTYPE_e node_type, void* node_ptr);
void add_node(PLIST_t parent, PLIST_t next);

/* CR_t */
PCR_t new_cr(CRTYPE_e cr_type, PINST_t pinst);
void add_operand(PCR_t pcr, int op_num, PLIST_t pop);
PCR_t add_cr(PCR_t parent, PCR_t child);

/* utility functions */
PCR_t new_label();
PCR_t new_func_label(char *name);
PCR_t get_exp_cr(PLIST_t exp);
PCR_t return_val(PLIST_t exp);

/* others */
PLIST_t newaddress(PIDENT_t ident, int disp);
TYPE_e get_listitem_type(PLIST_t item);
int get_listitem_typesize(PLIST_t item);
char get_listitem_sign(PLIST_t item);
TYPE_e get_basetype(PTYPE_t ptype);

int update_parameter_offsets(PIDENT_t parglist);
PIDENT_t getparam(PIDENT_t pfunc, char* param);

#endif
