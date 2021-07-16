#ifndef _MOVE_H
#define _MOVE_H

PLIST_t refer(PLIST_t op);
PLIST_t move8(PLIST_t op1, PLIST_t op2);
PLIST_t move16(PLIST_t op1, PLIST_t op2);
PLIST_t move(PLIST_t op1, PLIST_t op2);
PLIST_t newaddress(PIDENT_t ident, int disp);


#endif
