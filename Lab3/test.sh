#!/usr/bin/sh

./comm.py -1 file.txt file2.txt > my_comm_output
comm -1 file.txt file2.txt > posix_comm_output
diff my_comm_output posix_comm_output
