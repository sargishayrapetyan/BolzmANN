#This script will detect all tabs characters.

#First module provides a portable way of using operating system dependent functionality.
#Second module provides work with regular expressions.
import os, re

#Receive path of necessary directory.
os.chdir("../ANN")
path = os.getcwd()

#Grep given pattern in given file.
fileList = []

def grep(pattern, fileList):
    forPass = 0 
    for file in fileList:
        tabsCount = 0
        f = open(file, 'r')
        content = f.readlines()     
        for line in content:
            if re.search(pattern,line):
                tabsCount += 1
                forPass      += 1 
        if tabsCount != 0:        
            print("FAIL: In file  %s detected  %d tab character." %(file, tabsCount))
    if forPass == 0:
        print("PASS: Not detected tab character.")  
    f.close()
  
#Receive file list of necessary extensions.
files = os.listdir(path)

for f in files:
    file = os.path.join(path, f)
    if ( file.endswith(".h")) or (file.endswith(".cpp")) or (file.endswith(".txt") ):
        fileList += [file]

#Function call.        
grep("\t", fileList)
           