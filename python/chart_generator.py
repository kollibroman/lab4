import matplotlib.pyplot as plt
import numpy as np
import re

# Read data from file
try:
    with open('../operation_times.txt', 'r') as file:
        data = file.read()
except FileNotFoundError:
    print("Error: The file 'operation_times.txt' was not found.")
    exit(1)
except Exception as e:
    print(f"Error reading the file: {e}")
    exit(1)

# Parse the data
sizes = []
unique_sizes = set()
operation_times_simd = {
    '+': [],
    '-': [],
    '*': [],
    '/': []
}
operation_times_sisd = {
    '+': [],
    '-': [],
    '*': [],
    '/': []
}

current_size = None
current_type = None

for line in data.split('\n'):
    type_match = re.search(r'Typ Obliczen: (\w+)', line)
    if type_match:
        current_type = type_match.group(1)
    
    size_match = re.search(r'Liczba liczb: (\d+)', line)
    if size_match:
        current_size = int(size_match.group(1))
        unique_sizes.add(current_size)
    
    for op in ['+', '-', '*', '/']:
        if line.startswith(op):
            time_value = float(line.split()[1])
            if current_type == "SIMD":
                operation_times_simd[op].append((current_size, time_value))
            elif current_type == "SISD":
                operation_times_sisd[op].append((current_size, time_value))

sizes = sorted(list(unique_sizes))
for op in ['+', '-', '*', '/']:
    operation_times_simd[op].sort(key=lambda x: x[0])
    operation_times_sisd[op].sort(key=lambda x: x[0])

simd_times = {op: [t[1] for t in operation_times_simd[op]] for op in ['+', '-', '*', '/']}
sisd_times = {op: [t[1] for t in operation_times_sisd[op]] for op in ['+', '-', '*', '/']}

# Calculate percentage improvement (SIMD vs SISD)
percentage_improvement = {}
for op in ['+', '-', '*', '/']:
    percentage_improvement[op] = []
    for i in range(len(sizes)):
        simd_time = simd_times[op][i]
        sisd_time = sisd_times[op][i]
        improvement = ((sisd_time - simd_time) / sisd_time) * 100
        percentage_improvement[op].append(improvement)

# Chart 1: Average time by number of operations for each operation type (SIMD & SISD)
plt.figure(figsize=(12, 7))

for op, times in simd_times.items():
    plt.plot(sizes, times, marker='o', linestyle='-', label=f'SIMD {op}')

for op, times in sisd_times.items():
    plt.plot(sizes, times, marker='s', linestyle='--', label=f'SISD {op}')

plt.xlabel('Liczba operacji')
plt.ylabel('Średni czas (ms)')
plt.title('Średni czas a liczba operacji (SIMD vs SISD)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.savefig('chart1_time_vs_operations_comparison.png')
plt.close()

# Chart 2: Average time by operation type for 8192 numbers (SIMD & SISD)
operations = ['+', '-', '*', '/']
index_8192 = sizes.index(8192) 

simd_times_8192 = [simd_times[op][index_8192] for op in operations]
sisd_times_8192 = [sisd_times[op][index_8192] for op in operations]
improvement_8192 = [percentage_improvement[op][index_8192] for op in operations]

# Creating the bar chart
plt.figure(figsize=(10, 7))
x = np.arange(len(operations))
width = 0.35

bars1 = plt.bar(x - width/2, simd_times_8192, width, label='SIMD')
bars2 = plt.bar(x + width/2, sisd_times_8192, width, label='SISD')

for i, (bar1, bar2) in enumerate(zip(bars1, bars2)):
    height1 = bar1.get_height()
    height2 = bar2.get_height()
    plt.text(bar1.get_x() + bar1.get_width()/2., height1,
             f'{height1:.3f}',
             ha='center', va='bottom')
    plt.text(bar2.get_x() + bar2.get_width()/2., height2,
             f'{height2:.3f}',
             ha='center', va='bottom')
    
    avg_x = (bar1.get_x() + bar1.get_width() + bar2.get_x()) / 2
    plt.text(avg_x, max(height1, height2) * 0.5,
             f'+{improvement_8192[i]:.1f}%',
             ha='center', va='center',
             bbox=dict(facecolor='white', alpha=0.8, boxstyle='round,pad=0.2'))

plt.xlabel('Typ operacji')
plt.ylabel('Średni czas (ms)')
plt.title('Porównanie czasu wykonania wg operacji dla 8192 liczb (SIMD vs SISD)')
plt.xticks(x, operations)
plt.legend()
plt.grid(True, axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('chart2_time_by_operation_8192_comparison.png')

# Chart 3: Percentage improvement of SIMD over SISD for all operations and sizes
plt.figure(figsize=(12, 7))

for op in operations:
    plt.plot(sizes, percentage_improvement[op], marker='o', label=f'Operation {op}')

plt.xlabel('Liczba operacji')
plt.ylabel('Zysk (%)')
plt.title('Zysk operacji typu SIMD do operacji SISD  (%)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.savefig('chart3_percentage_improvement.png')

# NEW CHART 4: Only SIMD operations comparison
plt.figure(figsize=(12, 7))

for op in operations:
    plt.plot(sizes, simd_times[op], marker='o', linestyle='-', label=f'SIMD {op}')

plt.xlabel('Liczba operacji')
plt.ylabel('Średni czas (ms)')
plt.title('Średni czas a liczba operacji (tylko SIMD)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.savefig('chart4_simd_only_comparison.png')
plt.close()

# NEW CHART 5: Only SISD operations comparison
plt.figure(figsize=(12, 7))

for op in operations:
    plt.plot(sizes, sisd_times[op], marker='s', linestyle='-', label=f'SISD {op}')

plt.xlabel('Liczba operacji')
plt.ylabel('Średni czas (ms)')
plt.title('Średni czas a liczba operacji (tylko SISD)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.savefig('chart5_sisd_only_comparison.png')
plt.close()

print("Charts have been generated successfully!")
print("- chart1_time_vs_operations_comparison.png: Shows time comparison between SIMD and SISD")
print("- chart2_time_by_operation_8192_comparison.png: Shows time comparison for 8192 numbers")
print("- chart3_percentage_improvement.png: Shows percentage improvement of SIMD over SISD")
print("- chart4_simd_only_comparison.png: Shows comparison of SIMD operations only")
print("- chart5_sisd_only_comparison.png: Shows comparison of SISD operations only")
print(f"\nData was read from 'operation_times.txt' containing {len(sizes)} different operation sizes.")