#ifndef _ZASSERT_H

#define ZASSERT(exp)  if(!(exp)) printf("ZASSERT: %s,%s",__FILE__,__LINE__),exit(0);

#endif
