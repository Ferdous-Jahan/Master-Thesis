#!/bin/bash

# Ensure required directories exist
mkdir -p gprof_analysis valgrind_analysis

# List of C++ files
files=(
  "parallel_sort_execution_policy_par.cpp"
  "parallel_sort_execution_policy_par_unseq.cpp"
  "parallel_sort_threads.cpp"
  "parallel_sort_pthreads.cpp"
)

# Corresponding executable names
executables=(
  "parallel_sort_par"
  "parallel_sort_par_unseq"
  "parallel_sort_threads"
  "parallel_sort_pthreads"
)

# Compiler flags
flags="-O2 -g"

# Run for both C++17 and C++23 standards
for cpp_version in c++17 c++23; do
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

    echo "Finished profiling for $exec with standard $cpp_version"
    echo "-----------------------------------------------"
  done
done

# Cleanup binaries
rm parallel_sort_par_* parallel_sort_par_unseq_* parallel_sort_threads_* parallel_sort_pthreads_*

# Done
echo "All profiling completed successfully! Execution times are stored in execution_times.csv"
