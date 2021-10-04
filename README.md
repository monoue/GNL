# get_next_line
This program reads from a file (or stdin) line by line and prints to the screen. <br>It will return 1 when a line has been successfully read, 0 if the end of file has been reached, and -1 if there was an error.

For the get_next_line portion of this project Global variables were not allowed and the only functions allowed were read, malloc, and free.

Buffer size is defined during compilation and can be set to any number from 1 to INT_MAX - 1.

Standard library functions were recoded and modified for this project.

----
### Installation
```bash
git clone https://github.com/unstoppa61e/gnl.git
```

### Example of usage 
Run the command below.
```bash
gcc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=1024
./a.out
```
You can change the `BUFFER_SIZE` number in the command and the file name to be read in `main.c`(default: lorem.txt).
