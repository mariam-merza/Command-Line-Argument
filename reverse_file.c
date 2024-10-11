/*
 * Program: Command Line Arguments (Lab #2)
 * Name: Mariam Merza
 * Student ID: 0763480
 * Date Created: 10/08/2024
 * Last Modified: 10/11/2024
*/

#include <stdio.h>  // Library that includes functions for input/output
#include <unistd.h>  // For open(), creat(), read(), and write() functions
#include <fcntl.h>  // For file read-only mode
#include <sys/types.h>  // For 'off_t' type

#define CHAR_SIZE 512  // Assume up to 512 characters for each file name
#define BUFFER_SIZE 1  // Read one byte at a time
#define PERMS 0666     // Grant file read and write permissions to any user

int main(int argc, char* argv[]) {                                          
    // Check if the number of command line arguments is less than 3
    if (argc < 3) {    // If true, return 1 and print an error message                                                    
        return 1;                                                          
        printf ("Error: 2 arguments are needed\n");                          
    }                                                                      
    
    // Declare and initialize file descriptors for source and destination files
    int src_file = 0;
    int dest_file = 0;

    // Initialize a variable to keep track of the file position
    int n = -1;                                                          

    // Open the source file in read-only mode
    if ((src_file = open(argv[1], O_RDONLY)) < -1)
        return 1;

    // Create the new file with specified permissions
    if ((dest_file = creat(argv[2], PERMS)) < -1)
        return 1;

    // Print the size of the source file
    printf ("The filesize is: %d\n", lseek(src_file, (off_t) 0, SEEK_END));

    // Declare a character buffer of size BUFFER_SIZE
    char buffer[BUFFER_SIZE];
    
    // Move the file pointer to the end of the source file
    lseek (src_file, n--, SEEK_END);
    
    // Read from the source file and write to the destination file
    do {
        read(src_file, buffer, BUFFER_SIZE);      // Read BUFFER_SIZE characters from the source file
        printf("%s", buffer);                   // Print the buffer contents
        write(dest_file, buffer, BUFFER_SIZE);    // Write the buffer contents to the destination file
    } while (lseek (src_file, n--, SEEK_END) > -1);

    // Print a final newline character and return an exit code of 0 to indicate success
    printf("\n");
    return 0;
}