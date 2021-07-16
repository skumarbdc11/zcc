
#include <stdio.h>

extern "C" void cmain(int, char**);
extern "C" int g_line;

int main(int argc, char *argv[])
{
//   try 
   {
      cmain(argc, argv);
   }
//   catch(...)
//   {
//	  printf("\nZCC: Internal error at line#%d",g_line);
//	  return(-1);
//   }
   return(0);
}
