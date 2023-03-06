#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define TEST1 test_encode_non_cyclic_lower_case_positive_k()
#define TEST2 test_encode_cyclic_lower_case_special_char_positive_k()
#define TEST3 test_encode_non_cyclic_lower_case_special_char_negative_k()
#define TEST4 test_encode_cyclic_lower_case_negative_k()
#define TEST5 test_encode_cyclic_upper_case_positive_k()
#define TEST6 test_decode_non_cyclic_lower_case_positive_k()
#define TEST7 test_decode_cyclic_lower_case_special_char_positive_k()
#define TEST8 test_decode_non_cyclic_lower_case_special_char_negative_k()
#define TEST9 test_decode_cyclic_lower_case_negative_k()
#define TEST10 test_decode_cyclic_upper_case_positive_k()

const int line_length = 1024;


/** The second option - testing the encryption.
 * @returns: if all the tests worked than returns EXIT_SUCCESS,
 * else - EXIT_FAILURE.
 * */
int tests(){
  if((TEST1 == 0) && (TEST2 == 0) && (TEST3 == 0) && (TEST4 == 0) && (TEST5
  == 0) && (TEST6 == 0) && (TEST7 == 0) && (TEST8 == 0) && (TEST9 == 0) &&
     (TEST10 == 0)){
    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }
}


/** The first option - encoding or decoding the string from the input file
 * into the output file.
 *  @param: command - 'encode' \ 'decode'
 *  @param: k - number of letters to jump with the encryption.
 *  @param: input_path, output_path  - where to read and write the string.
 *  @returns: EXIT_SUCCESS if the encryption worked, else - EXIT_FAILURE.
 * */
int first_option(bool is_encode, bool is_decode, int k, char input_path[], char
output_path[]){

  FILE *file = fopen (input_path, "r");
  FILE *output_file = fopen (output_path, "w");
  if(!file || !output_file){
    fprintf (stderr,"%s","The given file is invalid.\n");
    return EXIT_FAILURE;
  }
  char line[line_length];
  while(fgets(line, line_length, file)){
//        printf("%s", line);
    if(is_encode)
    {
      encode (line, k);
      fprintf (output_file, "%s", line);
    }else if(is_decode){
      decode (line, k);
      fprintf (output_file, "%s", line);
    }
  }
  fclose(file);
  fclose(output_file);
  return EXIT_SUCCESS;
}


/** Checks if the string k is a legal integer
 * @param: k is a string.
 * @returns: 1 if k is legal, 0 if k is not legal
 */
bool is_num(char k[]){
  for(int i=0; i< strlen (k); i++){
      if(i == 0){
          if(k[0] == '-'){
              continue;
          }
      }
    if((!isdigit(k[i]))){
      return 0;
    }
  }
  return 1;
}


/** main function */
int main (int argc, char *argv[])
{

  if(argc == 5){ // option 1: encode/decode - k - input file - output file
    //check if k is legal entery:
      bool is_encode = 0;
      bool is_decode = 0;
      if(strcmp(argv[1],"encode") == 0){
          is_encode = 1;
      }else if(strcmp(argv[1],"decode")==0){
          is_decode = 1;
      }else{
          fprintf (stderr,"%s", "The given command is invalid.\n");
          return EXIT_FAILURE;
      }
      // check if k is legal:
      if(is_num (argv[2]) == 0){
          fprintf (stderr,"%s","The given shift value is invalid.\n");
          return EXIT_FAILURE;
      }
      if(first_option (is_encode, is_decode, strtol(argv[2],NULL,10),
                  argv[3], argv[4])==EXIT_FAILURE){
          return EXIT_FAILURE;
      }
  }else if(argc == 2){ // option 2: test
    if(strcmp(argv[1],"test") == 0){
      tests();
    }else{
      fprintf (stderr,"%s","Usage: cipher test\n");
      return EXIT_FAILURE;
    }
  }else{
    fprintf (stderr,"%s","The program receives 1 or 4"
                         " arguments only.\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
