#!/bin/bash
#Verify if gtk 3 is on board

GTK_PACK="gtk+-3.0"
VERIFY_GTK=`pkg-config $GTK_PACK --print-errors 2>&1 | grep $GTK_PACK`

if [ "$VERIFY_GTK"  !=  "" ]; then
    echo -e "Needed $GTK_PACK is NOT  Installed. Will abort script"
    exit 1    
else
    echo -e "GTK is OK : Using following libs/includes $PKG_EXEC \n"
    echo -e "-----"
    echo -e "Getting all .c and .h files \n"
    C_FILES=`ls *.c` 
    if [ "$C_FILES" = "" ]; then
       echo -e "No source files found. Will abort"
       exit 1
    else
       echo -e "Found sources: $C_FILES"
    fi
    
    H_FILES=`ls *.h 2>/dev/null` 
    if [ "$H_FILES" = "" ]; then
       echo -e "No header files found. Even with this, will try to compile."
    else
       echo -e "Found sources: $H_FILES"
    fi
    
    GTK_LIBS=`pkg-config --libs $GTK_PACK` 
    GTK_CFLAGS=`pkg-config --cflags $GTK_PACK`
    
    if [[ "$GTK_LIBS" = "" && "$GTK_CFLAGS" = "" ]]; then
        echo -e "Found no libs nor cflags to build CalcApp. Aborting."
        exit 1
    fi

    COMP_RES=`gcc $GTK_CFLAGS $C_FILES -o CalcApp $GTK_LIBS 2>&1`
    
    if [ "$COMP_RES" = "" ]; then
        chmod 755 ./CalcApp 
        echo -e "Compilation terminated well. Exec ./CalcApp."
    else
        echo -e "Something went wrong :" 
        echo -e "$COMP_RES"     
    fi    
fi

