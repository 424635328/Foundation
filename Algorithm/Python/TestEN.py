import random
import time
import matplotlib.pyplot as plt
import numpy as np
# Define the bin packing problem
class BinPackingProblem:
    def __init__(self, num_items, bin_capacity, item_sizes):
        self.num_items = num_items
        self.bin_capacity = bin_capacity
        self.item_sizes = item_sizes

# Backtracking algorithm
def backtracking(problem):
    """
    Backtracking algorithm to solve the bin packing problem
    """
    bins = [[]]
    best_solution = None
    best_num_bins = float('inf')

    def _backtracking_helper(current_item, current_bin):
        nonlocal best_solution, best_num_bins
        if current_item == problem.num_items:
            if len(bins) < best_num_bins:
                best_solution = bins.copy()
                best_num_bins = len(bins)
            return

        # Try to put the current item into the current bin
        if sum(bins[-1]) + problem.item_sizes[current_item] <= problem.bin_capacity:
            bins[-1].append(problem.item_sizes[current_item])
            _backtracking_helper(current_item + 1, current_bin)
            bins[-1].pop()

        # Try to put the current item into a new bin
        bins.append([problem.item_sizes[current_item]])
        _backtracking_helper(current_item + 1, current_bin + 1)
        bins.pop()

    _backtracking_helper(0, 0)
    return best_solution, best_num_bins

# Greedy algorithm
def greedy(problem):
    """
    Greedy algorithm to solve the bin packing problem
    """
    bins = [[]]
    for item in problem.item_sizes:
        # Try to put the current item into an existing bin
        for i in range(len(bins)):
            if sum(bins[i]) + item <= problem.bin_capacity:
                bins[i].append(item)
                break
        else:
            # Create a new bin
            bins.append([item])
    return bins, len(bins)

# Genetic algorithm
def genetic_algorithm(problem, population_size=100, crossover_rate=0.8, mutation_rate=0.1, generations=100):
    """
    Genetic algorithm to solve the bin packing problem
    """
    # Initialize the population
    population = []
    for _ in range(population_size):
        chromosome = random.sample(range(problem.num_items), problem.num_items)
        population.append(chromosome)

    # Evaluate the fitness function
    def fitness(chromosome):
        bins = [[]]
        current_bin = 0
        for item_index in chromosome:
            item = problem.item_sizes[item_index]
            if sum(bins[current_bin]) + item <= problem.bin_capacity:
                bins[current_bin].append(item)
            else:
                current_bin += 1
                bins.append([item])
        return len(bins)

    # Iterate evolution
    best_fitness = float('inf')
    best_chromosome = None
    for _ in range(generations):
        # Selection
        parents = selection(population, fitness)
        # Crossover
        offspring = crossover(parents, crossover_rate)
        # Mutation
        mutation(offspring, mutation_rate)
        # Update population
        population = offspring

        # Evaluate the best solution
        for chromosome in population:
            current_fitness = fitness(chromosome)
            if current_fitness < best_fitness:
                best_fitness = current_fitness
                best_chromosome = chromosome

    # Return the best solution
    return best_chromosome, best_fitness

# Selection operation
def selection(population, fitness):
    """
    Roulette wheel selection
    """
    # Calculate the total fitness of individuals
    total_fitness = sum(1 / fitness(chromosome) for chromosome in population)
    # Build the roulette wheel
    wheel = [1 / fitness(chromosome) / total_fitness for chromosome in population]
    # Select two parents
    parents = []
    for _ in range(2):
        # Randomly select an individual
        random_number = random.random()
        cumulative_probability = 0
        for i, probability in enumerate(wheel):
            cumulative_probability += probability
            if cumulative_probability >= random_number:
                parents.append(population[i])
                break
    return parents

# Crossover operation
def crossover(parents, crossover_rate):
    """
    Single-point crossover
    """
    offspring = []
    for _ in range(len(parents) // 2):
        # Randomly select two parents
        parent1 = parents.pop(random.randint(0, len(parents) - 1))
        parent2 = parents.pop(random.randint(0, len(parents) - 1))
        # Randomly select the crossover point
        crossover_point = random.randint(1, len(parent1) - 1)
        # Crossover
        child1 = parent1[:crossover_point] + parent2[crossover_point:]
        child2 = parent2[:crossover_point] + parent1[crossover_point:]
        offspring.append(child1)
        offspring.append(child2)
    return offspring

# Mutation operation
def mutation(offspring, mutation_rate):
    """
    Random swap mutation
    """
    for chromosome in offspring:
        if random.random() < mutation_rate:
            # Randomly select two genes to swap
            swap_index1 = random.randint(0, len(chromosome) - 1)
            swap_index2 = random.randint(0, len(chromosome) - 1)
            chromosome[swap_index1], chromosome[swap_index2] = chromosome[swap_index2], chromosome[swap_index1]

# Simulated annealing algorithm
def simulated_annealing(problem, initial_temperature=100, cooling_rate=0.95, iterations=1000):
    """
    Simulated annealing algorithm to solve the bin packing problem
    """
    # Initialize the solution
    current_solution = random.sample(range(problem.num_items), problem.num_items)
    # Initialize the temperature
    temperature = initial_temperature
    # Evaluate the fitness function
    def fitness(solution):
        bins = [[]]
        current_bin = 0
        for item_index in solution:
            item = problem.item_sizes[item_index]
            if sum(bins[current_bin]) + item <= problem.bin_capacity:
                bins[current_bin].append(item)
            else:
                current_bin += 1
                bins.append([item])
        return len(bins)

    # Iterate search
    best_solution = current_solution
    best_fitness = fitness(current_solution)
    for _ in range(iterations):
        # Random perturbation
        neighbor_solution = current_solution.copy()
        swap_index1 = random.randint(0, len(neighbor_solution) - 1)
        swap_index2 = random.randint(0, len(neighbor_solution) - 1)
        neighbor_solution[swap_index1], neighbor_solution[swap_index2] = neighbor_solution[swap_index2], neighbor_solution[swap_index1]
        # Calculate the fitness of the neighboring solution
        neighbor_fitness = fitness(neighbor_solution)
        # Decide whether to accept based on temperature
        if neighbor_fitness < best_fitness or random.random() < np.exp(-(neighbor_fitness - best_fitness) / temperature):
            current_solution = neighbor_solution
            best_solution = neighbor_solution
            best_fitness = neighbor_fitness
        # Cool down
        temperature *= cooling_rate
    # Return the best solution
    return best_solution, best_fitness

# Experiment
def run_experiment(problem_size, bin_capacity):
    """
    Run the experiment
    """
    # Generate random item data
    item_sizes = [random.randint(1, bin_capacity // 2) for _ in range(problem_size)]
    problem = BinPackingProblem(problem_size, bin_capacity, item_sizes)

    # Run different algorithms
    algorithms = [
        ("Bt", backtracking),
        ("Greedy", greedy),
        ("Genetic", genetic_algorithm),
        ("S A", simulated_annealing),
    ]
    results = []
    for algorithm_name, algorithm in algorithms:
        start_time = time.time()
        solution, num_bins = algorithm(problem)
        end_time = time.time()
        runtime = end_time - start_time
        results.append((algorithm_name, runtime, num_bins))

    # Plot charts
    fig, axs = plt.subplots(1, 3, figsize=(15, 5))
    axs[0].set_title("Runtime")
    axs[1].set_title("Number of Bins Used")
    axs[2].set_title("Gap between Optimal Solution and Theoretical ")

    for algorithm_name, runtime, num_bins in results:
        axs[0].bar(algorithm_name, runtime)
        axs[1].bar(algorithm_name, num_bins)
        # Calculate the theoretical optimal solution
        theoretical_optimal = sum(item_sizes) // bin_capacity + (sum(item_sizes) % bin_capacity != 0)
        gap = num_bins - theoretical_optimal
        axs[2].bar(algorithm_name, gap)

    plt.show()

# Main function
if __name__ == "__main__":
    # Set the problem size and bin capacity
    problem_sizes = [10, 50, 100]
    bin_capacity = 100

    # Run the experiment
    for problem_size in problem_sizes:
        print(f"Problem Size: {problem_size}")
        run_experiment(problem_size, bin_capacity)