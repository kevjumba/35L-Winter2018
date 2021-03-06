#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
import argparse
import string, locale

class compare:
    def __init__(self, f1, f2, suppress1, suppress2, suppressboth, unsorted):
        if f1 == "-":
            self.lines1 = sys.stdin.readlines()
        else:
            file1 = open(f1, 'r')
            self.lines1 = file1.readlines()
            file1.close()

        if f2 == "-":
            self.lines2 = sys.stdin.readlines()
        else:
            file2 = open(f2, 'r')
            self.lines2 = file2.readlines()
            file2.close()
            
        self.suppress1 = suppress1
        self.suppress2 = suppress2
        self.suppressboth = suppressboth
        self.unsorted = unsorted
        self.lines1 = self.modify(self.lines1)
        self.lines2 = self.modify(self.lines2)
        self.c1 = [] #column 1 with all unique to column1
        self.c2 = [] #column 2 with all unique to column2
        self.c3 = [] #column 3 with lines that appear in both files
    def modify(self, lines):
        if(len(lines)==0):
            return lines
        if("\n" not in lines[-1]):
            lines[-1]+="\n"
        return lines
    def isSorted(self, file1, file2):
        if sorted(file1) != file1:
            sys.stdout.write("comm: file 1 is not in sorted order")
            return False
        if sorted(file2) != file2:
            sys.stdout.write("comm: file 2 is not in sorted order")
            return False
        return True
            
    def compareFiles(self):
        if not self.unsorted:
            if(not self.isSorted(self.lines1, self.lines2)):
                return
            self.sorted_compare()
            #perform the comparison for sorted
        else:
            self.unsorted_compare()
            #perform the comparison for unsorted
    def sorted_compare(self):
        i = 0
        j = 0
        while i in range(len(self.lines1)) or j in range(len(self.lines2)):
            l1,l2 = "", ""

            if i < len(self.lines1):
                l1 = self.lines1[i]
            if j < len(self.lines2):
                l2 = self.lines2[j]
            output = ""
            if l1 == "" or (l2 != "" and l1 > l2):
                #if we find the first file to be less than second                                        
                #that means there might be certain lines that can                                        
                #possibly be coming up so we compare based on the                                        
                #POSIX comm behavior and go down the second file 
                if not self.suppress2:
                    if not self.suppress1:
                        output += "\t"
                    sys.stdout.write(output+l2)
                j += 1
            elif l2 == "" or l1 < l2:
                #same logic as above
                if not self.suppress1:
                    sys.stdout.write(output+l1)
                i += 1
            else:
                #they are equal
                if not self.suppressboth:
                    if not self.suppress1:
                        output+="\t"
                    if not self.suppress2:
                        output+="\t"
                    sys.stdout.write(output+l2)
                i += 1
                j += 1
    def unsorted_compare(self):
        if self.unsorted:
            for l1 in self.lines1:
                output = ""
                if l1 not in self.lines2:
                    if not self.suppress1:
                        sys.stdout.write(l1)
                else:
                    if not self.suppressboth:
                        if not self.suppress1:
                            output+="\t"
                        if not self.suppress2:
                            output+="\t"
                        sys.stdout.write(output+l1)

                    self.lines2.remove(l1)
                    
            for l2 in self.lines2:
                output = ""
                if not self.suppress2:
                    if not self.suppress1:
                        output += "\t"
                        sys.stdout.write(output+l2)
def main():
    parser = argparse.ArgumentParser(description='Select or reject lines common to two files',
                                     prog="comm")
    parser.add_argument('-1', help='Suppress the output column of lines unique to file1.',
                        action="store_true", dest="arg1")
    parser.add_argument('-2', help='Suppress the output column of lines unique to file2.',
                        action="store_true", dest="arg2")
    parser.add_argument('-3', help='Suppress the output column of lines unique to both files.',
                        action="store_true", dest="arg3")
    parser.add_argument('-u', help='Compare unsorted files.',
                        action="store_true", dest="arg4")
    parser.add_argument('file1',
                    help='file1 to be compared')
    parser.add_argument('file2',
                    help='file2 to be compared')
    args = parser.parse_args()
    if(args.file1 == "-" and args.file2 == "-"):
        parser.error("Only one file can be read from standard input.")
    suppress1 = args.arg1
    suppress2 = args.arg2
    both = args.arg3
    unsorted = args.arg4
    try:
        com = compare(args.file1, args.file2, suppress1, suppress2, both, unsorted)
    except OSError as err:
        parser.error("OS Error: {0}".format(err))
    try:
        com.compareFiles()
    except OSError as err:
        parser.error("OS Error: {0}".format(err))

if __name__ == "__main__":
    main()
