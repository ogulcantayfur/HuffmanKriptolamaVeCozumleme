#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "jval.h"
 
int _satir(){
    IS is;
    int satir=0;
    is=new_inputstruct(".kilit");
    if (is == NULL) {
        perror(".kilit");
        exit(1);
    }
    while(get_line(is) >= 0) {
    satir++;
  }
  jettison_inputstruct(is);
  return satir;
}

int main(int argc, char **argv)
{
  if (argc != 4) 
  { 
    fprintf(stderr,"Girilen parametreler yanlis "); 
    exit(1); 
  }
  if(strcmp(argv[1],"-e")!=0 && strcmp(argv[1],"-d")!=0){
    fprintf(stderr,"girilen parametre -e ve -d opsiyonlarina uygun degil, parametreyi kontrol ediniz");
    exit(1);
  }
  JRB b;  
  IS is,is_metin;
  int i;
  char *token;
  char *token2;
  char *word;
  int satir=0;
  satir=_satir();

  is=new_inputstruct(".kilit");
  if (is == NULL) {
        perror(".kilit");
        exit(1);
  }
  is_metin=new_inputstruct(argv[2]);
  if (is == NULL) {
        perror(argv[2]);
        exit(1);
  }
  b = make_jrb();

  while(get_line(is) >= 0) 
  {
    if(is->line==1){
     token=strdup(is->fields[0]);
      if (strcmp(token,"{")!=0 || is->NF !=1)
      {
        fprintf(stderr,"json dosyasi gecersiz\n");
        exit(1); 
      }
      continue;
    }
    if(is->line == satir){
      token=strdup(is->fields[0]);
        if (strcmp(token,"}")!=0 || is->NF !=1)
        {  
          fprintf(stderr,"json dosyasi gecersiz\n");
          exit(1);
        }    
      continue;    
    }     
    token=strdup(is->fields[0]);
    token2=strdup(is->fields[1]); 
  
    if (is->line < satir)  
    {
      if(is->NF!=2){
        fprintf(stderr,"json dosyasi gecersiz\n");
        exit(1);
      }
      for (i = 0; i < strlen(token); i++) {
        if (*(token)!='\"')
        {
          fprintf(stderr,"json dosyasi gecersiz\n");
          exit(1);
        }
        if(i==strlen(token)-2){
          if(*(token+i)!='\"' || *(token+i+1)!=':')
          {
            fprintf(stderr,"json dosyasi gecersiz\n");
            exit(1);
          } 
        }     
      }
      for (i = 0; i < strlen(token2); i++) {
        if (*(token2)!='\"')
        {
          fprintf(stderr,"json dosyasi gecersiz\n");
          exit(1);
        }
        if(is->line < satir-1){        
          if(i==strlen(token2)-2){
            if(*(token2+i)!='\"' || *(token2+i+1)!=',')
            {
              fprintf(stderr,"json dosyasi gecersiz\n");
              exit(1);
            }
          }
        }
        else if(is->line == satir-1)  
        {
          if(i==strlen(token2)-1){
            if(*(token2+i)!='\"')
            {
              fprintf(stderr,"json dosyasi gecersiz\n");
              exit(1);
            }
          }
        }        
      }
    }
    token[strlen(token)-2]='\0';
    token=token+1;
    char*slash = strstr(token,"\\");
    while(slash != NULL){
      char *_kelime = strdup(slash+1);
      strcpy(slash,_kelime);
      slash = strstr(token,"\\");
      free(_kelime);
    }

    word=strtok(token2,"\"");

    if(strcmp(argv[1],"-e")==0){
      jrb_insert_str(b, strdup(token), new_jval_s(strdup(word)));
      free(token-1);
      free(token2);
    }
    else if(strcmp(argv[1],"-d")==0){
      jrb_insert_str(b, strdup(word), new_jval_s(strdup(token)));
      free(token-1);
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
  fclose(dosya);
  jrb_free_tree(b);
  jettison_inputstruct(is);
  return 0;
}