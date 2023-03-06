#include "cipher.h"
#include <string.h>
#include <stdio.h>
/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
// See full documentation in header file
const int before_high_a = 64;
const int before_low_a= 96;
const int num_of_alphabet = 26;
const int normalize_low_case = 104;
const int normalize_high_case = 52;


void encode (char s[], int k)
{
  unsigned long str_len = strlen(s);
//  printf("k value is: %d\n", k);
  for(int i=0; i < str_len; i++)
  {
    if(!(((s[i] >= 'a')&&(s[i]<='z'))||((s[i] >= 'A')&&(s[i]<='Z')))){
      continue; // char is not an alphabet.
    }
//    printf("%d\n",i);
    int new_char = (s[i] + k);
//    printf ("old char: %c with value: %d \n new char is: %c ,with value: "
//            "%d\n", s[i], s[i],
//            new_char,
//            new_char);
    if((s[i] >= 'A') && (s[i] <= 'Z'))
    {
      //A-Z = 65-90 , a-z = 97-122
      if ((new_char >= 'A') && (new_char <= 'Z'))
      {
        s[i] = new_char;
      }
      else
      {  //In case the new char is out of range, use modulo:
        if (new_char >= 'Z')
        {
          s[i] = (char) ((int) (new_char - 'Z') % num_of_alphabet)
                 + before_high_a;
        }
        else
        { //new_char <= 'A'
          s[i] = (char) (new_char % num_of_alphabet) + normalize_high_case;
        }
      }
    }
    if((s[i] >= 'a') && (s[i] <= 'z'))
    {
      if ((new_char >= 'a') && (new_char <= 'z'))
      {
        s[i] = new_char;
      }
      else
      {  //In case the new char is out of range, use modulo:
        if (new_char >= 'z')
        {
          s[i] =(char) ((int) (new_char - 'z') % num_of_alphabet) +
              before_low_a;
        }
        else
        { //new_char <= 'a'
          s[i] = (char) (new_char) % num_of_alphabet + normalize_low_case;
        }
      }
    }
//    printf("%s\n",s);
  }
}



// See full documentation in header file
void decode (char s[], int k)
{
    unsigned long str_len = strlen(s);

    for(int i=0; i<str_len; i++){
        if(!(((s[i] >= 'a')&&(s[i]<='z'))||((s[i] >= 'A')&&(s[i]<='Z')))){
            continue; // char is not an alphabet.
        }
        int old_char = (s[i] - k);
//        printf ("corrent char: %c with value: %d \n old char is: %c ,with "
//                "value: "
//              "%d\n", s[i], s[i],
//                old_char,
//                old_char);
        if((s[i] >= 'A') && (s[i] <= 'Z'))
        {
            //A-Z = 65-90 , a-z = 97-122
            if ((old_char >= 'A') && (old_char <= 'Z'))
            {
                s[i] = old_char;
            }
            else
            {  //In case the new char is out of range, use modulo:
                if (old_char >= 'Z')
                {
                    s[i] = (char) ((int) (old_char - 'Z') % num_of_alphabet)
                           + before_high_a;
                }
                else
                { //new_char <= 'A'
                    s[i] = (char) (old_char % num_of_alphabet)
                        + normalize_high_case;
                }
            }
        }
        if((s[i] >= 'a') && (s[i] <= 'z'))
        {
            if ((old_char >= 'a') && (old_char <= 'z'))
            {
                s[i] = old_char;
            }
            else
            {  //In case the new char is out of range, use modulo:
                if (old_char >= 'z')
                {
                    s[i] = (char) ((int) (old_char - 'z') % num_of_alphabet)
                            + before_low_a;
                }
                else
                { //new_char <= 'a'
                  if(old_char < 0)
                  {
                    s[i] = (char)(num_of_alphabet + (old_char %
                        num_of_alphabet) + normalize_low_case);
                    if(s[i] > 'z'){
                      s[i] = s[i] - num_of_alphabet;
                    }
                  }else{
                    s[i] = (char)((old_char % num_of_alphabet) +
                       normalize_low_case);
                  }

                }
            }
        }
    }
}
