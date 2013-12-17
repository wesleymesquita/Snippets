"""
    @author: Wesley Mesquita
    @contact: wesleymesquita@gmail.com
"""
   
import sys
import os

from os import rename
from os import listdir
from os.path import isfile, join
from sys import argv


def changeExtension(path, fromExt, toExt, confirm=False):
    """
        @summary: changes extensions of all files in path from a specified extension.  
        @param path: path containing the files to be modified (it is not 
                     recursive yet)
        @param fromExt: current extensions to be changed
        @param toExt: target extension
        @param confirm: list modifications and asks user to continue
        @note: the extensions can be input with or without period
        @example: changeExtension('/tmp/', '.JPG', '.jpg', True)
    """
    #list all files in path
    #credit to http://stackoverflow.com/questions/3207219/how-to-list-all-files-of-a-directory-in-python  
    all_files = [ f for f in listdir(path) if isfile(join(path,f)) ]
    
    #adjust extension string
    dotFromExt = fromExt 
    if "." not in fromExt:
        dotFromExt = str("." + fromExt)
    
    #select just the files with 'dotFromExt' extension
    fromExt_files = []    
    for f in all_files:
        if f.endswith(dotFromExt):
            fromExt_files.append(f)
    
    #Stop execution if there is no files with extension 'fromExt'
    if len(fromExt_files) == 0:
        raise Exception(str("There is no files with extension '" + fromExt + "'"))
              
    #create new names for files in fromExt_files with dotToExt
    toExt_files = []

    dotToExt = toExt
    
    if "." not in toExt:
        dotToExt = str("." + toExt)
      
    for f in fromExt_files:
        tmp = str(f)
        toExt_files.append(tmp.replace(dotFromExt, dotToExt))
    
    #asks user if the modification is right 
    if confirm:
        print "Do you want to rename this(these) files?"
        
        for f in fromExt_files:
            print f
        
        print "with : "
        
        for f in toExt_files:
            print f
                
        resp = raw_input("[Y - yes / N - no]: ")
        while resp <> 'Finalized':
            if resp == 'Y' or resp == 'y':
                for fromFile, toFile in zip(fromExt_files, toExt_files):
                    from_file = str(path + "\\" +  fromFile)
                    to_file = str(path + "\\" +  toFile);
                    rename(from_file, to_file )
                resp = 'Finalized'
            elif resp == 'N' or 'n':            
                resp = 'Finalized' 
            else:
                resp = raw_input("[Y - yes / N - no]: ")        
    else:
        for fromFile, toFile in zip(fromExt_files, toExt_files):
            from_file = str(path + "\\" +  fromFile)
            to_file = str(path + "\\" +  toFile);
            rename(from_file, to_file )

def main():    
    path = ""        
    fromExt = ""
    toExt = ""
    confirm = False
    if len(argv) == 4 or len(argv) == 5 :
        
        if os.path.isdir(sys.argv[1]):    
            path = argv[1]
        else:
            raise Exception(str("Invalid path ",argv[1]))
        
        if len(argv[2]) <> 0 and len(argv[3]) <> 0:
            fromExt =  argv[2]
            toExt = argv[3]
        else:
            raise Exception(str("Invalid path ",argv[1]))
        
        if len(argv) == 5:
            confirm =  (argv[4] == 'Y' or argv[4] == 'y') 
    
        changeExtension(path, fromExt, toExt, confirm)    
    
    else:
        print "Usage: 'python [DIR] [FROM_EXTENSION] [TO_EXTENSION] [CONFIRM [Y/N] ]'"

main()
    