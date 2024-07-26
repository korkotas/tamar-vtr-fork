import os
import subprocess
import time

# Define paths (update these paths to your setup)
VTR_PATH = "~/tamar-vtr-fork/"  # Path to your repo
BENCHMARKS_DIR = "~/tamar-vtr-fork/benchmarks/titan_blif/other_benchmarks/stratix10/"  # Path to your Titan benchmarks
ARCH_FILE = os.path.join(VTR_PATH, "arch/titan/stratix10_arch.timing.xml")  # Path to the architecture file

# List of Titan benchmarks to run (ensure these are the correct names)
BENCHMARKS = [
    "murax_stratix10_arch_timing",
    "picosoc_Stratix10_arch_timing",
    "radar20_stratix10_arch_timing"
    # Add other benchmarks as needed
]

# Output directory
OUTPUT_DIR = "~/vtr_results"  # Directory for output results

# Create the output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)

def run_vtr_flow(benchmark):
    circuit_file = os.path.join(BENCHMARKS_DIR, f"{benchmark}.blif")  # Verilog file for the benchmark
    output_prefix = os.path.join(OUTPUT_DIR, benchmark)

    if not os.path.isfile(circuit_file):
        print(f"Circuit file for {benchmark} not found. Skipping...")
        return

    print(f"Running VTR flow for benchmark: {benchmark}")

    # Define the command to run VTR flow
    command = [
        os.path.join(VTR_PATH, "vtr_flow/scripts/run_vtr_flow.py"),
        circuit_file,
        ARCH_FILE,
        "--dynamic_lookahead", "on",
        "--comp_iterations", "10"
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
