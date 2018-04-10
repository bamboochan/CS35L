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

class comm:
    def __init__(self, file1, file2):
        #sys.stdout.write("in comm constructor")
        if file1=="-":
            f1 = sys.stdin
        else:
            f1 = open(file1, 'r')
        if file2=="-":
            f2=sys.stdin
        else:
            f2 = open(file2, 'r')
        self.lines1 = f1.readlines()
        self.lines2 = f2.readlines()
        if self.lines1[-1][-1] != '\n':
            self.lines1[-1] +='\n'
        if self.lines2[-1][-1] !='\n':
            self.lines2[-1] +='\n'
        f1.close()
        f2.close()
        self.both = []
        
    def commlines(self,only1,only2,only3):
        #sys.stdout.write("in commlines")
        i,j=0,0
        num1=len(self.lines1)
        num2=len(self.lines2)
        while i <  num1 or j < num2:
            #print(i," ",j)
            if j==num2:
                if only1:
                    self.both.append(self.lines1[i])
                i+=1
            elif i==num1:
                if only2:
                    self.both.append("\t"*int(only1)+self.lines2[j])
                j+=1
            elif self.lines1[i] < self.lines2[j]:
                if only1:
                    self.both.append(self.lines1[i])
                i+=1
            elif self.lines1[i] > self.lines2[j]:
                if only2:
                    self.both.append("\t"*int(only1)+self.lines1[j])
                j+=1
            else:
                if only3:
                    self.both.append("\t"*(int(only1)+int(only2))+self.lines1[i])
                i+=1
                j+=1
    def ucommlines(self,only1,only2,only3):
        for thing1 in self.lines1:
            found=False
            for thing2 in self.lines2:
                if thing1==thing2:
                    if only3:
                        self.both.append("\t"*(int(only1)+int(only2))+thing1)
                    found=True
                    self.lines2.remove(thing2)
                    break
            if found==False and only1:
                self.both.append(thing1)
        if only2:
            for thing2 in self.lines2:
                self.both.append(thing2)


def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Select or reject lines common to two files."""

    parser = argparse.ArgumentParser(description=usage_msg)
    parser.add_argument("-1", action="store_false", dest="t1", default=True)
    parser.add_argument("-2", action="store_false", dest="t2", default=True)
    parser.add_argument("-3", action="store_false", dest="t3", default=True)
    parser.add_argument("-u", action="store_true", dest="uu", default=False)
    parser.add_argument('file1', metavar='file1', type=str, nargs=1)
    parser.add_argument('file2', metavar='file2', type=str, nargs=1)
    args = parser.parse_args()
    file1only=args.t1
    file2only=args.t2
    comml=args.t3
    unsorted=args.uu
    input_file1 = args.file1[0]
    input_file2 = args.file2[0]
    try:
        generator = comm(input_file1,input_file2)
        if unsorted:
            generator.ucommlines(file1only,file2only,comml)
        else:
            generator.commlines(file1only,file2only,comml)
        for thing in generator.both:
            sys.stdout.write(thing)
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(err.errno, err.strerror))


if __name__ == "__main__":
    main()
