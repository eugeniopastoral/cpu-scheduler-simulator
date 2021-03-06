/*
AUTHOR: Rafael Maderazo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 900

/*
This function reads a txt file and parses the content.
*/
int read_file(int parameters[], int process_values[][6], char fn[]) {
  FILE *fp;
  char string[MAX_STRING][MAX_STRING];
  int i = 0, j = 0, n = 0, error_code = 0, process_count = 0;
  int row_size = 0;
  char filename[MAX_STRING] = "./";
  strcat(filename, fn);

  if((fp = fopen(filename, "r")) != NULL){
      //read through file
      while(fgets(string[i], MAX_STRING, fp) != NULL) {
        if(strlen(string[i]) - 1 == '\0') {
          string[i][strlen(string[i]) - 1] = ' ';
        }
        else if(i > 0) {
          strcat(string[i], " 0 0 0");
        }
        i++;
      }
      fclose(fp);

      row_size = i;
      process_count = row_size - 1;
      char* tokenized = strtok(string[0], " ");

      //convert first line to int
      while(tokenized) {
        parameters[n++] = atoi(tokenized);
        tokenized = strtok(NULL, " ");
      }

      //validate parameters for the first line
      for(i = 0; i < 3; i++) {
        if(i == 0 &&( parameters[i] > 3 || parameters[i] < 0)) {
          error_code = 1;
        }
        if(i == 1 && parameters[i] < 3 && parameters[i] > 100) {
          error_code = 1;
        }
        if(i == 2 && (parameters[i] < 1 || parameters[i] > 100) && parameters[0] == 3) {
          error_code = 1;
        }
        if(process_count != parameters[1]) {
          error_code = 1;
        }
      }
      if(error_code == 1) {
        printf("An invalid parameter on the first line has been found.\n");
        return 1;
      }

      //convert the process values to int, store in 2d arr
      j = 0;
      for(i = 1; i < row_size; i++) {
        n = 0;

        char* tokenized = strtok(string[i], " ");
        while(tokenized) {
          process_values[j][n++] = atoi(tokenized);
          tokenized = strtok(NULL, " ");
        }
        j++;
      }

      //validate process values
      for(i = 0; i < row_size - 1; i++) {
        for(j = 0; j < 3; j++) {
          if(process_values[i][j] < 0) {
            error_code = 2;
          }
        }
      }
      if(error_code == 2) {
        printf("A process time parameter cannot have a negative value.\n");
        return 1;
      }

      //check if process id is unique
      for(i = 0; i < row_size - 1; i++) {
        for(j = i + 1; j < row_size - 1; j++) {
          if(process_values[i][0] == process_values[j][0]) {
            error_code = 3;
          }
        }
      }

      if(error_code == 3) {
        printf("Process IDs cannot have the same value.\n");
        return 1;
      }

      return 0;

      // for (int  i = 0; i < 5; i++) {
      //   printf("%d %d %d %d %d %d\n", process_values[i][0], process_values[i][1], process_values[i][2], process_values[i][3], process_values[i][4], process_values[i][5]);
      // }

  } else {
    printf("File cannot be opened: %s.\n", filename);
    return 1;
  }
  //open file
}
