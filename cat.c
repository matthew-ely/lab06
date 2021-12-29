#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF 100

/**
 * Cat class allows files to be printed to the standard output. Multiple files
 * can be printed at once. If no files are contained in the argument, standard
 * output is assumed. If '-' is a file argument, standard output is also assumed.
 */
int main(int argc, char* args[]) {

    if (argc == 1) { // if no file arguments passed
        int n;
        char blank[BUF]; // creates buffer for chars to be written to
        while ((n = read(STDIN_FILENO, blank, BUF)) > 0) { // read characters from standard input
            write(STDOUT_FILENO, blank, n); // writes read characters back to standard output
        } // while
    } else {
        for (int i = 1; i < argc; i++) { // loops through all file arguments
            char* file = args[i];
            if (*file == '-') { // if '-' is passed as argument
                int n;
                char input[BUF]; // creates buffer for chars to be written to
                while ((n = read(STDIN_FILENO, input, BUF)) > 0) { // read characters from std input
                    write(STDOUT_FILENO, input, n); // writes read characters to std output
                } // while
            } else { // if file name argument passed
                int fd = open(file, O_RDONLY); // opens file
                if (fd == -1) perror("ERROR: Please enter a valid filename");

                int n;
                char buffer[BUF]; // creates buffer for chars to be written to

                while ((n = read(fd, buffer, BUF)) > 0) { // reads characters from file
                    write(STDOUT_FILENO, buffer, n); // writes read characters to std output
                } // while
                if (n == -1) perror("ERROR: Issue reading from file");

                close(fd); // closes file
                if (fd == -1) perror("ERROR: Issue closing file");
            } // if
        } // for
    } // if
} // main
