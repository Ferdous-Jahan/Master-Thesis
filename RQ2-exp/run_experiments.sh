#!/bin/bash

# Define compilers and benchmark files
COMPILERS=("g++-14" "g++-13" "clang++-17" "clang++-16")
BENCHMARKS=("parallel_sort" "matrix_mul" "prod_cons" "atomic_ops" "thread_create"
            "parallel_sort_pthread" "matrix_mul_pthread" "prod_cons_pthread" "atomic_ops_pthread" "thread_create_pthread")
RUNS=5

# Compilation flags
CXXFLAGS="-O3 -march=native -pthread -std=c++20"

# Create results directory and file
mkdir -p results
RESULT_FILE="results/results.csv"

# Initialize CSV file with headers
echo "Compiler,Benchmark,Run,ExecutionTime(s),CPU(%),MaxRSS(KB)" > "$RESULT_FILE"

# Loop through compilers and benchmarks
for COMPILER in "${COMPILERS[@]}"; do
    for BENCHMARK in "${BENCHMARKS[@]}"; do
        echo "Compiling $BENCHMARK with $COMPILER..."
        $COMPILER benchmarks/$BENCHMARK.cpp -o benchmarks/$BENCHMARK.out $CXXFLAGS
        
        # Check compilation success
        if [ $? -ne 0 ]; then
            echo "Compilation failed for $BENCHMARK with $COMPILER"
            continue
        fi

        # Run each benchmark multiple times
        for ((RUN=1; RUN<=RUNS; RUN++)); do
            echo "Running $BENCHMARK (Compiler: $COMPILER, Run: $RUN)..."

            # Execute and capture metrics with '/usr/bin/time'
            /usr/bin/time -f "%e,%P,%M" -o tmp_time.txt ./benchmarks/$BENCHMARK.out

            # Extract performance metrics
            METRICS=$(cat tmp_time.txt)
            EXEC_TIME=$(echo $METRICS | cut -d',' -f1)
            CPU_USAGE=$(echo $METRICS | cut -d',' -f2 | tr -d '%')
            MAX_RSS=$(echo $METRICS | cut -d',' -f3)

            # Append results to CSV
            echo "$COMPILER,$BENCHMARK,$RUN,$EXEC_TIME,$CPU_USAGE,$MAX_RSS" >> "$RESULT_FILE"

            echo "Run completed: Time=${EXEC_TIME}s, CPU=${CPU_USAGE}%, Memory=${MAX_RSS}KB"
        done
    done
done

# Cleanup temporary files
rm -f tmp_time.txt

echo "Experiments completed. Results saved in $RESULT_FILE"
