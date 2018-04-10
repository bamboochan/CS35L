#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<ctype.h>
//int compcount=0;
int uppererror(void)
{
  fprintf(stderr, "Error in toupper");
  exit(1);
}
int frobcmp2(const char * a, const char * b)
{
  for(;*a==*b; a++,b++)
    { if(*a=='\0') return 0;
	  if(a<0||b<0) uppererror();
    }
  if((toupper((*a)^0x2A))>(toupper((*b)^0x2A))||(*b=='\0'))
    return 1;
  else
    return -1;
}
int frobcmp1(const char * a, const char * b)
{
  //compcount++;
  for(;*a==*b; a++,b++)
    { if(*a=='\0') return 0;
    }
  if((*a^0x2A)>(*b^0x2A)||(*b=='\0'))
    return 1;
  else
    return -1;
}
int frobcmpvoid1(const void* c, const void * d)
{
  const char* a = *(const char**)c;
  const char* b = *(const char**)d;
  //printf("%d\n", compcount);
  return frobcmp1(a,b);
}
int frobcmpvoid2(const void* c, const void * d)
{
  const char* a = *(const char**)c;
  const char* b = *(const char**)d;
  return frobcmp2(a,b);
}
int mallocerror(void)
{
  fprintf(stderr, "Error in Memory Allocation");
  exit(1);
}
int readerror(void)
{
   fprintf(stderr, "Error while reading file");
   exit(1);
}
int writeerror(void)
{
  fprintf(stderr, "Error while writing file");
  exit(1);
}

int sfrobu(int fff)
{
  //printf("%d\n",fff);
  struct stat fS;
  if(fstat(0,&fS) < 0) 
    {
      fprintf(stderr, "Error with the file"); 
      exit(1);
   }
  char ** words;
  int wordnum =0;
  if(S_ISREG(fS.st_mode))
  //if is regular file, words is the array of words without space at the end.
    {
      // printf("naked word is %d long",fS.st_size);
      char* nakedwords = (char*)malloc(fS.st_size * sizeof(char));
      words = malloc(fS.st_size * sizeof(char*));
      if(nakedwords==NULL)  
	mallocerror();
      int nread = read(0, nakedwords, fS.st_size);
      int k=0;
      if(nread<0)
	readerror();
      int sizeword=0;
      int i=0;
      for (;i<fS.st_size;i++)
	{
	  char c=nakedwords[i];
	  if (c==' '&& sizeword > 0)
	    {
	      if ((words[wordnum]=(char *) malloc((sizeword+1) *sizeof(char)))==NULL)
		  mallocerror();
	      strncpy(words[wordnum],nakedwords+i-sizeword,sizeword);
	      words[wordnum][sizeword]='\0';
	      sizeword=0;
	      wordnum++;
	    }
	  else if (c!=' ') 
	    sizeword++;
	}
      if(sizeword>0)
	{
	  words[wordnum]=(char *) malloc((sizeword+1) *sizeof(char));
	  strncpy(words[wordnum],nakedwords+i-sizeword,sizeword);
	  words[wordnum][sizeword]='\0';
	  sizeword=0;
	  wordnum++;
	}
      //      printf("wordnum is %d\n\n\n",wordnum);
    }
  else
      words = (char**) malloc(sizeof(char *));
  //----------
  char d[1];
  char* word=malloc(sizeof(char));
  int sizeword=0;
  while(1){
    // printf("in loop\n");
    int nread= read(0,d,1);
    if(nread!=0&&d[0]!=' ')
	{
	  word[sizeword]=d[0];
	  sizeword++;
	  char *tmp = word;
	  if( (word=realloc(word,(sizeword+1)*sizeof(char)))==NULL)
	    {
	      free(tmp);
	      mallocerror();
	    }
	}
     else if((nread==0||d[0]==' ') && sizeword > 0)
	{
	  words[wordnum]=word;
	  wordnum++;
	  char *tmp = word;
	  if((words=realloc(words,(wordnum+1)*sizeof(char*)))==NULL) {
	      free(tmp);
	      mallocerror();}    
	  sizeword=0;
	  word=malloc(sizeof(char));
	}
     if(nread==0)
	break;
    }
  //--------
  if (fff==1)
    qsort(words, wordnum, sizeof(char*), frobcmpvoid2);
  else
     qsort(words, wordnum, sizeof(char*), frobcmpvoid1);
  // printf("number of comp: %d\n",compcount);
  int i=0;
  for (;i<wordnum;i++)
    {
      // printf("%s\n",words[i]);
      int k =0;
      for (;k<strlen(words[i]);k++)
	write(1,words[i]+k,1);
      write(1," ",1);
    }
  int j=0;
  for(;j<wordnum;j++)
    {
      free(words[j]);
    }
  free(words);
  return 0;
}

int main(int argc, char **argv)
{
  if (argc==2&&(!strcmp(argv[1],"-f")))
  return sfrobu(1);
  else if (argc==1)
    return sfrobu(0);
}
