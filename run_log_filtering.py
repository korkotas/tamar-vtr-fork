import os
import re

def read_log_file(file_path):
    if not os.path.isfile(file_path):
        print(f"Error: The file at path {file_path} was not found.")
        return []

    with open(file_path, 'r') as file:
        lines = file.readlines()
    return lines

def extract_routing_details(log_lines):
    details = {
        "succeeded": False,
        "channel_width": None,
        "iterations": None,
        "total_heap_pushes": None,
        "total_heap_pops": None
    }

    for line in log_lines:
        # Check for success or failure
        if "Routing failed." in line:
            details["succeeded"] = False
        elif "total_nets_routed:" in line:
            details["succeeded"] = True

        # Extract channel width
        if "Attempting to route at" in line:
            match = re.search(r"Attempting to route at (\d+) channels", line)
            if match:
                details["channel_width"] = int(match.group(1))

        # Extract number of iterations
        if "Iter" in line:
            match = re.findall(r"^ {3}(\d+)", line)
            if match:
                details["iterations"] = int(match[-1])  # last iteration number

        # Extract total heap pushes and pops
        if "total_heap_pushes:" in line:
            match = re.search(r"total_heap_pushes: (\d+)", line)
            if match:
                details["total_heap_pushes"] = int(match.group(1))
        if "total_heap_pops:" in line:
            match = re.search(r"total_heap_pops: (\d+)", line)
            if match:
                details["total_heap_pops"] = int(match.group(1))

    return details

def main():
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

    for bench in BENCHMARKS:
        log_file_path = "/home/tkorkot/tamar-vtr-fork/vtr_results/" + bench + '_without.log'
        log_lines = read_log_file(log_file_path)
        if not log_lines:
            return
        log_file_path = "/home/tkorkot/tamar-vtr-fork/vtr_results/" + bench + '_with.log'
    
    

    routing_details = extract_routing_details(log_lines)
    
    print(f"Routing Success: {routing_details['succeeded']}")
    print(f"Channel Width: {routing_details['channel_width']}")
    print(f"Number of Iterations: {routing_details['iterations']}")
    print(f"Total Heap Pushes: {routing_details['total_heap_pushes']}")
    print(f"Total Heap Pops: {routing_details['total_heap_pops']}")

if __name__ == "__main__":
    main()
