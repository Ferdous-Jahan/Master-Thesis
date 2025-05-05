import re
import os
import pandas as pd

def parse_perf_file(filepath):
    dominant_function = None
    percent_runtime = None
    overhead_type = None

    with open(filepath, 'r', encoding='utf-8', errors='ignore') as file:
        lines = file.readlines()

    # Regex pattern to find the dominant function and its runtime percentage
    pattern = re.compile(r'^\s*(\d+\.\d+)%.*\s(\S+\(.*\))')

    for line in lines:
        match = pattern.match(line)
        if match:
            percent_runtime = float(match.group(1))
            dominant_function = match.group(2)
            break  # Stop after finding the most dominant function

    # Determine overhead type based on function name
    if dominant_function:
        if "worker" in dominant_function or "pthread" in dominant_function:
            overhead_type = "Explicit"
        else:
            overhead_type = "Implicit"
    else:
        dominant_function = "Unknown"
        percent_runtime = 0.0
        overhead_type = "Unknown"

    return dominant_function, percent_runtime, overhead_type

# Example usage:
perf_dir = './perf_analysis/'  # Adjust to your local perf results folder
result_summary = []

for filename in os.listdir(perf_dir):
    if filename.endswith('.txt'):
        filepath = os.path.join(perf_dir, filename)
        dominant_function, percent_runtime, overhead_type = parse_perf_file(filepath)

        result_summary.append({
            "File": filename,
            "Dominant Function": dominant_function,
            "Percent Runtime": percent_runtime,
            "Overhead Type": overhead_type
        })

# Convert to DataFrame and save results as CSV
summary_df = pd.DataFrame(result_summary)
summary_df.to_csv('perf_analysis_summary.csv', index=False)

print(summary_df.head())
