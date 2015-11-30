# This script will detect all tab characters.

# First module provides a portable way of using operating system dependent functionality.
import os

# Second module provides work with regular expressions.
import re

# Receive path of the necessary directory.
os.chdir("../ANN")
path = os.getcwd()

# Grep given pattern in given file.
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
                forPass   += 1 
        if tabsCount != 0:        
            print("FAIL: In file %s detected %d tab characters." %(file, tabsCount))
    if forPass == 0:
        print("PASS: No tab characters.")  
    f.close()
  
# Receive file list of the necessary extensions.
files = os.listdir(path)

for f in files:
    file = os.path.join(path, f)
    if ( file.endswith(".h")) or (file.endswith(".cpp")) or (file.endswith(".txt") ):
        fileList += [file]

# Function call.        
grep("\t", fileList)
           