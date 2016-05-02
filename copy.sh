#!/bin/bash
xcode_path=/Users/noprom/Documents/Dev/C++/Complier/java_complier/java_complier
vs_path=/Users/noprom/Downloads/VBShare/Complier/java_complier_vs2/java_complier/java_complier
cp ${vs_path}/globals.h ${xcode_path}
cp ${vs_path}/util.h ${xcode_path}
cp ${vs_path}/util.cpp ${xcode_path}
cp ${vs_path}/lexer.h ${xcode_path}
cp ${vs_path}/lexer.cpp ${xcode_path}
cp ${vs_path}/main.cpp ${xcode_path}