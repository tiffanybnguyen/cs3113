# The Programming Assignment
A circular buffer with 15 positions (each position stores 1 character) is to be used to communicate information between two threads (producer and consumer). The producer thread will read characters, one by one from a file and place it in the buffer and continue to do that until the “end-of-file” (EOF) marker is reached. Consumer thread will read the characters, one by one, from the shared buffer and print it to the screen.

# How to Compile the Program
1. go to file location
2. write ```gcc bounded_buffer.c -lpthread -lrt -o bounded_buffer``` into the terminal 
3. write ```./bounded_buffer``` into the terminal
4. run it several times and observe.
5. yay!! :3