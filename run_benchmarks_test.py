import os
import subprocess
import time

# Define paths (update these paths to your setup)
VTR_PATH = "/home/tkorkot/tamar-vtr-fork/build/vpr/vpr"  # Path to your repo
BENCHMARKS_DIR_TITAN = "/home/tkorkot/tamar-vtr-fork/vtr_flow/benchmarks/titan_blif/other_benchmarks/stratix10"  # Path to your Titan benchmarks
BENCHMARKS_DIR = "/home/tkorkot/tamar-vtr-fork/vtr_flow/benchmarks/blif"
ARCH_FILE_TITAN = "/home/tkorkot/tamar-vtr-fork/vtr_flow/arch/titan/stratix10_arch.timing.xml"  # Path to the architecture file
ARCH_FILE = "/home/tkorkot/tamar-vtr-fork/vtr_flow/arch/timing/k6_N10_40nm.xml"  # Path to the architecture file

# List of Titan benchmarks to run 
# List of the MCNC20 Benchmarks to run
BENCHMARKS_TITAN = [
    "murax_stratix10_arch_timing",
    "picosoc_Stratix10_arch_timing",
    "radar20_stratix10_arch_timing"
]

BENCHMARKS = [
    "alu4",
    "apex2",
    "bigkey",
    "clma",
    "des",
    "diffeq",
    "dsip",
    "elliptic",
    "ex1010",
    "ex5p",
    "frisc",
    "misex3",
    "pdc",
    "s298",
    "s38417",
    "s38584.1",
    "seq",
    "spla",
    "tseng"
]

# Output directory
OUTPUT_DIR = "/home/tkorkot/vtr_results"  # Directory for output results

# Create the output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)

def run_vtr_flow(benchmark):
    circuit_file = os.path.join(BENCHMARKS_DIR, f"{benchmark}.blif")  # Verilog file for the benchmark
    output_prefix = os.path.join(OUTPUT_DIR, benchmark)

    print(circuit_file)
    if not os.path.isfile(circuit_file):
        print(f"Circuit file for {benchmark} not found. Skipping...")
        return

    print(f"Running VTR flow for benchmark: {benchmark}")

    # Define the command to run VTR flow
    command = [
        VTR_PATH,
        ARCH_FILE,
        circuit_file,
        "--dynamic_lookahead", "on",
        "--comp_iters", "10"
    ]

    # Run the VTR flow
    result = subprocess.run(command, capture_output=True, text=True)

    # Save the log output
    log_file = f"{output_prefix}.log"
    with open(log_file, "w") as f:
        f.write(result.stdout)
        f.write(result.stderr)

    # Check for errors
    if result.returncode != 0:
        print(f"Error running VTR flow for {benchmark}. Check log: {log_file}")
    else:
        print(f"VTR flow completed for {benchmark}. Results saved to {output_prefix}.*")

def main():
    start_time = time.time()

    for benchmark in BENCHMARKS:
        run_vtr_flow(benchmark)

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"All benchmarks completed in {elapsed_time:.2f} seconds.")

if __name__ == "__main__":
    main()
