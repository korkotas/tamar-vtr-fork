import os
import subprocess
import time

# Define paths (update these paths to your setup)
VTR_PATH = "/path/to/vtr"  # Path to your VTR installation
BENCHMARKS_DIR = "/path/to/titan_benchmarks"  # Path to your Titan benchmarks
ARCH_FILE = os.path.join(VTR_PATH, "arch/titan/titan_arch.xml")  # Path to the architecture file

# List of Titan benchmarks to run (ensure these are the correct names)
BENCHMARKS = [
    "ch_intrinsics",
    "ch_intrinsics_4bit",
    "ch_intrinsics_tiny",
    "clma",
    "clma_p1",
    "clma_p2",
    # Add other benchmarks as needed
]

# Output directory
OUTPUT_DIR = "./vtr_results"  # Directory for output results

# Create the output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)

def run_vtr_flow(benchmark):
    benchmark_path = os.path.join(BENCHMARKS_DIR, benchmark)
    circuit_file = os.path.join(benchmark_path, f"{benchmark}.v")  # Verilog file for the benchmark
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
        "--route_chan_width", "100",  # Example route channel width, adjust if needed
        "--output_prefix", output_prefix,
        "--timing_analysis", "on",
        "--max_router_iterations", "50"  # Adjust this parameter if needed
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
