#!/bin/bash

# Ensure required directories exist
mkdir -p gprof_analysis valgrind_analysis perf_analysis

# List of C++ files
files=(
  "matrix_mul_execution_policy_par.cpp"
  "matrix_mul_execution_policy_par_unseq.cpp"
  "matrix_mul_threads.cpp"
  "matrix_mul_pthreads.cpp"
)

# Corresponding executable names
executables=(
  "matrix_mul_par"
  "matrix_mul_par_unseq"
  "matrix_mul_threads"
  "matrix_mul_pthreads"
)

# Compiler flags
flags="-O2 -g"

# Run for both C++17, C++20 and C++23 standards
for cpp_version in c++17 c++20 c++23; do
  echo "Running experiments with standard $cpp_version"

  for i in ${!files[@]}; do
    file=${files[$i]}
    exec=${executables[$i]}_${cpp_version}

    # Check for pthread file to include pthread flag
    if [[ $file == *"pthread"* ]]; then
      pthread_flag="-pthread"
    else
      pthread_flag=""
    fi

    echo "Compiling $file for gprof..."
    g++ $flags -pg -std=$cpp_version $file $pthread_flag -o $exec

    for run in {1..5}; do
      echo "Gprof profiling run $run for $exec"
      ./$exec
      mv gmon.out gmon_${exec}_run${run}.out
      gprof $exec gmon_${exec}_run${run}.out >./gprof_analysis/${exec}_run${run}_gprof.txt
    done

    echo "Compiling $file for Valgrind Massif..."
    g++ $flags -std=$cpp_version $file $pthread_flag -o ${exec}_massif

    for run in {1..5}; do
      echo "Valgrind Massif profiling run $run for ${exec}_massif"
      valgrind --tool=massif ./${exec}_massif
      massif_file=$(ls massif.out.*)
      ms_print $massif_file >./valgrind_analysis/${exec}_run${run}_valgrind_massif.txt
      rm $massif_file
    done

    echo "Compiling $file for Perf..."
    g++ $flags -std=$cpp_version $file $pthread_flag -o ${exec}_perf

    for run in {1..5}; do
      echo "Perf profiling run $run for ${exec}_perf"
      sudo perf record -g -o ./perf_analysis/${exec}_run${run}_perf.data ./${exec}_perf
      sudo perf report -g --stdio -i ./perf_analysis/${exec}_run${run}_perf.data >./perf_analysis/${exec}_run${run}_perf.txt
    done

    echo "Finished profiling for $exec with standard $cpp_version"
    echo "-----------------------------------------------"
  done
done

# Cleanup binaries
rm matrix_mul_par_* matrix_mul_par_unseq_* matrix_mul_threads_* matrix_mul_pthreads_*

# Done
echo "All profiling (Gprof, Valgrind Massif, Perf) completed successfully! Execution times and profiling results stored appropriately."
