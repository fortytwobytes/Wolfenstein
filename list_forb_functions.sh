#!/bin/bash

make re

# Find all object files in the current directory and its subdirectories
object_files=$(find $(pwd) -name '*.o')

# Combine object files into a single object file
ld -r -o ./bin/combined.o $object_files

# Allowed functions:
# open, close, read, write, printf, malloc, free, perror, strerror, exit
# All functions of the math, library
# and all the functions that starts with mlx_*

# Define allowed functions
allowed_functions=(
  open
  close
  read
  write
  printf
  malloc
  free
  perror
  strerror
  exit
  mlx_*
)

# Add all math library functions to the allowed list
allowed_functions+=(
  sin
  cos
  tan
)

# Get list of forbidden functions
forbidden_functions=$(nm -u ./bin/combined.o | awk '{print $2}')

# Check if each forbidden function is allowed
for func in $forbidden_functions; do
  if [[ ! "${allowed_functions[@]}" =~ "${func}" ]]; then
    echo "${func}"
  fi
done

rm -f ./bin/combined.o

