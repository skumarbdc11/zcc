# Lightweight C Compiler
The objective for this project is to develop a lightweight C Compiler with limited C Constructs support and provide a implementation for lexer, syntax directed translor (SDT), code generated for generic instruction set architecture using simple register coloring algorithm. It has smaller footprint implementation for all of these components which can be used for learning pupose.

# Dependencies
1. flex
2. yacc
3. gcc (visual studio on windows)

# Code structure
## Parser lexer
* src/parser/zlex.l
## SDT yacc
* src/parser/zyacc.y
## Code generation and register coloring algorithm
* src/codegen
## Symbol table
* src/utils/zsymtab.c

# Sample C code with output assembly code
* bin/

# TBD
* Makefile for Linux platform
* Detailed documentation for each of the module
