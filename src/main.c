#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "jval.h"

int main()
{
  JRB b;
  JRB bn;  
  IS is;
  int i,nsize=0;
  char *token;
  char *token2;
  char *word;
  char *word2;
 

  is = new_inputstruct(".kilit");
  b = make_jrb();

  while(get_line(is) >= 0) {
    
     if(is->NF!=2){continue;}
      token=strdup(is->fields[0]);
      token2=strdup(is->fields[1]);
      word=strtok(token,"{},:\"");
      word2=strtok(token2,"{},:\"");

    jrb_insert_str(b, strdup(word), new_jval_s(strdup(word2)));
    free(token);
    free(token2);
   
  }
  jrb_traverse(bn, b) {
    printf("%s\t", bn->key.s);
     printf("%s\n", bn->val.s);
  }
  jettison_inputstruct(is);
  return 0;
}