# Cube Solver

A fast C++ implementation of a Rubik's cube solver that uses different algorithms to find optimal or near-optimal solutions.

## Features

- Two solver algorithms: 'E' (efficient) and 'M' (memory-intensive)
- Optional hash table for improved performance
- Random shuffle generation with specified move count
- Custom shuffle sequence input
- Detailed solution output

## Installation

```bash
git clone https://github.com/aknlite48/Parallel_Cube_Solver.git
cd Parallel_Cube_Solver
make
```

## Usage

```bash
./cube_solver [options]
```

### Command Line Arguments

| Argument | Description | Required | Default |
|----------|-------------|----------|---------|
| `--solver E/M` | Solver type: 'E' (efficient) or 'M' (memory-optimized) | No | 'E' |
| `--use_hash` | Enable hash table for improved performance | No | false |
| `--n_moves N` | Number of random moves to shuffle the cube | Yes* | - |
| `--shuffle MOVES` | Custom shuffle sequence (e.g., "R U R' U'") | Yes* | - |

\* Either `--n_moves` or `--shuffle` must be provided.

### Example Commands

Solve a cube shuffled with 6 random moves using the efficient solver:
```bash
./cube_solver --n_moves 20
```

Solve a cube with a specific shuffle sequence:
```bash
./cube_solver --shuffle "R U R' U' F B L"
```

Use the memory-optimized solver with hash table enabled:
```bash
./cube_solver --solver M --use_hash --n_moves 7
```

## Solver Types

1. **Efficient Solver ('E')** - Prioritizes finding solutions quickly, potentially using more memory.
2. **Memory-Intensive Solver ('M')** - Uses more memory to store solution states which can speed up runtime.

## Move Notation

The solver uses standard Rubik's cube notation:

- `R`: Right face clockwise
- `L`: Left face clockwise
- `U`: Upper face clockwise
- `D`: Down face clockwise
- `F`: Front face clockwise
- `B`: Back face clockwise
- `R'`: Right face counter-clockwise
- `L'`: Left face counter-clockwise
- `U'`: Upper face counter-clockwise
- `D'`: Down face counter-clockwise
- `F'`: Front face counter-clockwise
- `B'`: Back face counter-clockwise

## Output Format

The solver will display the configuration and then output the solution:

```
       Cube Solver - Configuration
--------------------------------------------
    Solver type:         E
    Use hash:            false
    Number of moves:     20
    Shuffle sequence:    R U R' U' F
--------------------------------------------

Current depth: 5 Nodes searched: 149716 Nodes remaining: 1497161 
Solution found

Solution sequence: F' U R U' R'
```

## Performance

Performance may vary based on:
- Solver type selected
- Whether hash table is enabled
- Complexity of the shuffle (number of moves)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

[MIT License](LICENSE)

## Acknowledgements