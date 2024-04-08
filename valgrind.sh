#!/bin/bash
if [ ! -d "build" ]; then
  echo "ERROR: No se compiló el proyecto. Ejecutá './build.sh' antes de probar."
  exit 1
elif [ ! -f "build/tests/GachaTest" ] || [ ! -f "build/tests/VectorTest" ]; then
  echo "ERROR: El proyecto no compiló correctamente. Revisá los errores que reporta './build.sh'."
  exit 1
else
  if ! valgrind --leak-check=yes --error-exitcode=1 ./build/tests/GachaTest ||
  ! valgrind --leak-check=yes --error-exitcode=1 ./build/tests/VectorTest; then
    exit 1
  fi
fi