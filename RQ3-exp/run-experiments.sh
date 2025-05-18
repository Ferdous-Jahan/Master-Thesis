#!/bin/bash

# Configuration
EXECUTABLES=("parallel_for_original" "parallel_for_custom" "parallel_for_custom_improved")
NUM_RUNS=5
OUTPUT_CSV="runtimes.csv"
IMAGE_ARG="lena.jpg" # Image to process, ensure it exists or executables handle default

# --- Helper function to check if an image exists ---
check_image() {
    if [ ! -f "$1" ]; then
        echo "Warning: Image '$1' not found. The executables might use an internal default or fail."
        echo "Please ensure '$1' is available in the current directory or provide a valid path."
        # Optionally, you could exit here if the image is critical
        # exit 1
    fi
}

# --- Main Script ---

# Check for the image file
check_image "$IMAGE_ARG"

# Write CSV Header
echo "Executable,RunNumber,SequentialTime_s,ParallelTime_s,ParallelRowSplitTime_s" > "$OUTPUT_CSV"

# Loop through each executable
for exe_name in "${EXECUTABLES[@]}"; do
    echo "-----------------------------------------------------"
    echo "Processing executable: $exe_name"
    echo "-----------------------------------------------------"

    # Check if the executable exists and is executable
    if ! command -v "$exe_name" &> /dev/null && [ ! -x "./$exe_name" ]; then
        echo "Error: Executable '$exe_name' not found or not executable. Skipping."
        # Add placeholder NA entries to CSV for this missing/non-executable program
        for run_num in $(seq 1 "$NUM_RUNS"); do
            echo "$exe_name,$run_num,NA,NA,NA" >> "$OUTPUT_CSV"
        done
        echo "" # Newline for readability
        continue # Skip to the next executable
    fi

    # Determine the command to run (prefer local if exists)
    CMD_TO_RUN="$exe_name"
    if [ -x "./$exe_name" ]; then
        CMD_TO_RUN="./$exe_name"
    fi


    for run_num in $(seq 1 "$NUM_RUNS"); do
        echo "  Running $exe_name - Run #$run_num..."

        # Execute the program and capture its standard output (and standard error)
        # The executables from your example code print timing to stdout
        run_output=$("$CMD_TO_RUN" "$IMAGE_ARG" 2>&1)

        # Check if the command failed (non-zero exit status)
        if [ $? -ne 0 ]; then
            echo "    Error: '$CMD_TO_RUN $IMAGE_ARG' failed on run #$run_num. Output:"
            echo "$run_output" | sed 's/^/      /' # Indent error output
            seq_time="ERROR"
            parallel_time="ERROR"
            parallel_row_split_time="ERROR"
        else
            # Parse the output for timing information
            # Grep for lines starting with the specific text to be precise
            seq_time=$(echo "$run_output" | grep "^ Sequential implementation: " | awk '{print $3}' | sed 's/s//')
            parallel_time=$(echo "$run_output" | grep "^ Parallel Implementation: " | awk '{print $3}' | sed 's/s//')
            parallel_row_split_time=$(echo "$run_output" | grep "^ Parallel Implementation(Row Split): " | awk '{print $4}' | sed 's/s//')

            # Handle cases where a specific timing line might be missing from the output
            if [ -z "$seq_time" ]; then seq_time="NA"; fi
            if [ -z "$parallel_time" ]; then parallel_time="NA"; fi
            if [ -z "$parallel_row_split_time" ]; then parallel_row_split_time="NA"; fi
        fi

        # Append the extracted data to the CSV file
        echo "$exe_name,$run_num,$seq_time,$parallel_time,$parallel_row_split_time" >> "$OUTPUT_CSV"
        echo "    Times: Seq=${seq_time}s, Par=${parallel_time}s, ParRowSplit=${parallel_row_split_time}s"
    done
    echo "" # Newline for readability between executables
done

echo "-----------------------------------------------------"
echo "Script finished. All runtimes saved to $OUTPUT_CSV"
echo "-----------------------------------------------------"