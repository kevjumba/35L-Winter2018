import sys
import os

for i in range(0, 9):
    with open('lines1.txt', 'a') as f:
        f.write('abc def\n')
for i in range(0, 99):
    with open('lines2.txt', 'a') as f:
        f.write('abc def\n')
for i in range(0, 999):
    with open('lines3.txt', 'a') as f:
        f.write('abc def\n')
for i in range(0, 9999):
    with open('lines4.txt', 'a') as f:
        f.write('abc def\n')

