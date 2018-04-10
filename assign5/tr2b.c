
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
  if(argc!=3)
    {
      fprintf(stderr,"Error:number of arguments is incorrect");
      exit(1);
    }
  char* from = argv[1];
  char* to = argv[2];
  char c;
  int sizefrom=strlen(from);
  int sizeto=strlen(to);
  //operand error checking
  if (sizefrom==0)
    {  
      fprintf(stderr,"Error:missing argument(s)");
      exit(1);
   }
  if(sizefrom!=sizeto)
    {
      fprintf(stderr,"Error:size of from different from size of to");
      exit(1);
    }
  //WOBBLE BUBBLE WOBBLE WOBBLE.
  char* tempfr=from;
  while(*tempfr!='\0')
    {
      char* snd=strrchr(from,*tempfr);
      if(snd!=tempfr)
	{
	  fprintf(stderr,"Error: duplicate characters in from");
	  exit(1);
	}
      tempfr++;
    }

  do
    {
      if(ferror(stdin))
	{
	  fprintf(stderr,"Error:cannot open file");
	  exit(1);
	}
      if(ferror(stdout))
	{
	  fprintf(stderr,"Error:cannot output file");
	  exit(1);
	}
      c=getchar();
      char* ifrom=from;
      char* ito=to;
      while ((*ifrom)!='\0')
	{
	  if(c==*ifrom)
	    {
	      // fprintf("replacing");
	      c=*ito;
	      break;
	    }
	  ifrom++;
	  ito++;
	}
      if(!feof(stdin))
      putchar(c);
    }
  while(!feof(stdin));
  return 0;
}
