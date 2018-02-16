// https://stackoverflow.com/questions/7109964/creating-your-own-header-file-in-c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int read_file( char* filename, char **buffer ){    
    printf("Reading file\n");
    FILE *f;
    f = fopen(filename, "r");
    if(f == NULL)
	printf("CAN'T READ FILE!\n\n");
    printf("File opened\n");
    // https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
    fseek(f, 0L, SEEK_END); // seek to end of file 
    int size = ftell(f); // get current file pointer
    printf("size %i \n", size);
    rewind(f);

    //struct stat st;
    //stat(filename, &st);
    //int size = st.st_size;
    //printf("size %i \n", size);

    char *file_str = (char *)malloc( size * sizeof(char) );
    
    fread(file_str, size, 1, f);
    printf("Created file string:\n %s\n", file_str);
    printf("put file into string \n");


    char *token;

    token = strtok(file_str, ",");
    printf("began tokenization \n");
    int r = 0;
    buffer[r] = token;
    printf("put token into buf: %s \n", token);
    while (token != NULL){
        printf("tokenizing... \n");
        token = strtok(file_str, ",");
        //buffer[i] = (char *)malloc(strlen(token));
        buffer[r] = token;
        printf("%s \n", buffer[r]);
        r++;
    }


    free(file_str);
    return 0;

}

int write_file( char* filename, char **buffer, int rows, int cols){
    printf("Writing board to file with %i rows and %i cols \n", rows, cols);
    FILE *f;
    f = fopen(filename, "w+");
    printf("WRITING TO FILE: \n");
    // char row_buf[sizeof(rows)];
    // sprintf(row_buf, "%d", rows);

    // char col_buf[sizeof(cols)];
    // sprintf(col_buf, "%d", cols);

    // fputs(row_buf, f);
    // fputc(',', f);
    // fputs(col_buf, f);
    // fputc(',', f);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols + 1; j++ ){
            printf( "%c", buffer[i][j] );
            fputc(buffer[i][j], f);
        }  
        fputc(',',f);
    }
    
    
    //fwrite(buffer , 1 , size , f );
    fclose(f);

    return 0;
}
