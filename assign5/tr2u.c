#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
  if(argc!=3)
    {
      fprintf(stderr,"Error:number of arguments is incorrect");
      exit(1);
    }
  char* from =argv[1];
  char* to = argv[2];
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

  char c[1];
  int nread;
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
      nread=read(0,c,1);
      char* ifrom=from;
      char* ito=to;
      while ((*ifrom)!='\0')
	{
	  if(c[0]==*ifrom)
	    {;
	      c[0]=*ito;
	      break;
	    }
	  ifrom++;
	  ito++;
	}
      if(nread!=0)
	write(1,c,1);
    }
    while(nread!=0);
  return 0;
}
