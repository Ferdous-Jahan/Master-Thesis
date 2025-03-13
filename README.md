# Master Thesis Experiment Codes

This repository contains C++ implementations and profiling instructions used for the experiments conducted in my Master's thesis titled:

> **"Evaluating Multithreading in Classic C++, C++17, C++20, and C++23: Execution Policies, Compiler Efficiency, and Tool Support."**

## Experiments

Two parallel computation tasks are included:

- **Parallel Sorting:**
  - Execution policies (`std::execution::par`, `std::execution::par_unseq`)
  - Manual threading (`std::thread`)

- **Matrix Multiplication:**
  - Execution policies (`std::execution::par`, `std::execution::par_unseq`)
  - Manual threading (`std::thread`)

---

## Compilation Instructions

Compile using GCC on Linux with optimization and debugging flags as follows:

### Parallel Sort:

```bash
# Parallel execution policy (par)
g++ -O2 -g -pg -std=c++17 parallel_sort_execution_policy_par.cpp -o parallel_sort_execution_policy_par
```

---

## Running Executables

Execute programs with:

```bash
./parallel_sort_execution_policy_par
```

---

## Profiling with Gprof

To profile execution time and function call details, first ensure compilation with `-pg` flag, then:

```bash
./parallel_sort_execution_policy_par    # generates gmon.out


gprof parallel_sort_execution_policy_par > parallel_sort_execution_policy_par_gprof.txt
```

Repeat similarly for other codes.

---

## Profiling Memory Consumption with Valgrind (Massif)

Compile separately without `-pg` flag:

```bash
g++ -O2 -g -std=c++17 -o parallel_sort_execution_policy_par parallel_sort_execution_policy_par.cpp 

valgrind --tool=massif ./parallel_sort_execution_policy_par
ms_print massif.out.<pid> > parallel_sort_execution_policy_parvalgrind_massif.txt
```

Replace `<pid>` with the actual PID from your Valgrind output (e.g., `massif.out.12345`).

---

## Profiling Thread Correctness with Helgrind

```bash
valgrind --tool=helgrind ./parallel_sort_execution_policy_par 2> parallel_sort_execution_policy_parvalgrind_helgrind.txt #This saves the thread correctness analysis (data race detection, synchronization issues) into a text file.
```

Repeat similarly for other codes.

---

Feel free to reach out if you need further details or assistance!
