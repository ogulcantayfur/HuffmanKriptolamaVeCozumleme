#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "jval.h"

int isEqual(const char* str1,const char* str2){
  if(str1==NULL||str2==NULL) // parametre boş ise kontrol etmeye gerekde yoktur...
    return 0;
  if(!strcmp(str1,str2)) // iki ifade eşitse 1 değilse 0 döndürür...
    return 1;
  return 0;
}

int main(int argc, char **argv)
{
  JRB b;
  JRB bn;  
  IS is,is_metin;
  int i;
  char *token;
  char *token2;
  char *word;
  char *word2;
  char kripto_metin[500];
 
  is=new_inputstruct(".kilit");
  is_metin=new_inputstruct(argv[2]);
  b = make_jrb();
  
  while(get_line(is) >= 0) {

    if(is->NF!=2){continue;}
    token=strdup(is->fields[0]);
    token2=strdup(is->fields[1]);
    word=strtok(token,"{}\"");
    word2=strtok(token2,"{}\"");
 
    if(isEqual(argv[1],"-e")){
      jrb_insert_str(b, strdup(word), new_jval_s(strdup(word2)));
      free(token);
      free(token2);
    }

    if(isEqual(argv[1],"-d")){
      jrb_insert_str(b, strdup(word2), new_jval_s(strdup(word)));
      free(token);
      free(token2);
    }
  }
    FILE *dosya = fopen(argv[3], "w");
    
    while (get_line(is_metin)>=0)
    {
      for (i = 0; i < is_metin->NF; i++) {
    
        JRB find=jrb_find_str(b, is_metin->fields[i]);

        if(find==NULL){
          fprintf(dosya,"%s",is_metin->fields[i]);
        }
        else{
          fprintf(dosya,"%s",find->val.s);
        }
        fprintf(dosya," ");
       }
    }
  
  jettison_inputstruct(is);
  return 0;
}