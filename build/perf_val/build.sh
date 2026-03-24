if command -v ninja &> /dev/null; then
  echo "Found ninja!"
else
  echo "Need ninja for the c++ modules stuff!" >&2
  exit 1
fi

if command -v clang++&> /dev/null; then
  echo "Found clang!"
  eval cmake ../../ -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=y -DMATHPP_PERF_VAL=y
else
  eval cmake ../../ -G Ninja -DMATHPP_PERF_VAL=y
fi
