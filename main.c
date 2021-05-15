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
    while(get_line(is) >= 0) {
    satir++;
  }
  jettison_inputstruct(is);
  return satir;
}

int main(int argc, char **argv)
{
  JRB b;  
  IS is,is_metin;
  int i;
  char *token;
  char *token2;
  char *word;
  char *word2;
  int satir=0, satir2=0;
  satir=_satir();

  is=new_inputstruct(".kilit");
  is_metin=new_inputstruct(argv[2]);
  b = make_jrb();
  
  if(is==NULL){ 
    printf("kilit dosyası yok");
    return 0;
  }

  while(get_line(is) >= 0) {

    if(is->line==1){
     token=strdup(is->fields[0]);
      if (*(token)!='{')
      {
        printf("Parantez yok, json dosyasi gecersiz\n");
        return 0;
      }
    }
    if(is->line == satir){
      token=strdup(is->fields[0]);
        if (*(token)!='}')
        {  
          printf("Parantez yok, json dosyasi gecersiz\n");
          return 0;
        }        
    }     
    if (is->line > satir2+2)
    {
      printf("Satir duzenlemesi yanlis, json dosyasi gecersiz\n");
      return 0;
    }
    if(is->NF!=2){continue;} 
    satir2++;
    token=strdup(is->fields[0]);
    token2=strdup(is->fields[1]); 
    
    if (is->line == satir2+1)
    {
      if (is->line < satir)  
      {
        for (i = 0; i < strlen(token); i++) {
          if (*(token)!='\"')
          {
            printf("Kelimenin baslangicinda \" isareti yok, json dosyasi gecersiz\n");
            return 0;
          }
          if(i==strlen(token)-2){
            if(*(token+i)!='\"' || *(token+i+1)!=':')
            {
              printf("Kelime sonu \": formatina uygun degil, json dosyası geçersiz\n");
              return 0;
            } 
          }      
        }
        for (i = 0; i < strlen(token2); i++) {
          if (*(token2)!='\"')
          {
            printf("Huffman kodu baslangicinda \" isareti yok, json dosyasi gecersiz\n");
            return 0;
          }
          if(is->line < satir-1){        
            if(i==strlen(token2)-2){
              if(*(token2+i)!='\"' || *(token2+i+1)!=',')
              {
                printf("Huffman kodu sonu \", formatina uygun degil, json dosyası geçersiz\n");
                return 0;
              }
            }
          }
          else if(is->line == satir-1)  
          {
            if(i==strlen(token2)-1){
              if(*(token2+i)!='\"')
              {
                printf("Son satirdaki huffman kodu sonu \" formatinda olmalı, json dosyası geçersiz\n");
                return 0;
              }
            }
          }        
        }
      }
    }
    
    word=strtok(token,"{}\"");
    word2=strtok(token2,"{}\"");
 
    if(strcmp(argv[1],"-e")==0){
      jrb_insert_str(b, strdup(word), new_jval_s(strdup(word2)));
      free(token);
      free(token2);
    }
    else if(strcmp(argv[1],"-d")==0){
      jrb_insert_str(b, strdup(word2), new_jval_s(strdup(word)));
      free(token);
      free(token2);
    }
    else{
       printf("girilen parametre -e ve -d opsiyonlarina uygun degil, parametreyi kontrol ediniz");
       return 0;
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
