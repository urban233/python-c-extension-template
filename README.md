# python-c-extension-template

## Pre-requisites
* [**Miniforge3**](https://conda-forge.org/download/) (or another Conda distribution)


## Environment Setup

To develop or run cBioMOL locally, you must create a `.env_path` file in the project root directory. This file should contain exactly one line: the absolute path to the root directory of the conda environment you wish to use.

### `.env_path` Examples

**Windows:**
```text
C:\Users\username\miniconda3\envs\python_c_ext_dev
```

**macOS:**
```text
/Users/username/miniconda3/envs/python_c_ext_dev
```

**Linux:**
```text
/home/username/miniconda3/envs/python_c_ext_dev
```

## Development & Automation

cBioMOL uses a standalone Python task runner called `pymake` to automate common development tasks. It provides a make-like experience using only the Python standard library.

### Running Tasks

Use the platform-specific wrapper scripts to run tasks:

- **Windows:** `.\pymake.bat <task> [args]`
- **Linux/macOS:** `./pymake.sh <task> [args]`

To see all available tasks and their options, run:
```bash
.\pymake.bat --help
```

### Available Tasks

| Task | Description |
| :--- | :--- |
| `format` | Format the Python codebase with Ruff. |
| `lint` | Run static analysis (linting) on Python code with Ruff. |
| `check_types` | Run static type checking with `mypy`. |
| `format_cpp` | Format C++ code with `clang-format`. |
| `lint_cpp` | Run style linting on C++ code (check-only mode). |
| `test` | Execute the test suite with `pytest`. |
| `build_plugin_builder` | Build the wheel and source distribution for the `plugin_builder` subproject. |
| `build_whl` | Build the wheel file directly using the Conda environment (cross-platform).|
| `package` | Package the project using conda-pack.|
| `build_release` | Build a self-contained release package.|

Example: Run tests with verbose output:
```bash
.\pymake.bat test verbose=true
```

### Environment variables to set
If you are trying to build the CMake project, you have to set at least the `Python_ROOT_DIR` and 
`CMAKE_PREFIX_PATH` as environment variables. If you are using numpy in your C or C++ code,
also add the `NUMPY_INCLUDE_DIR` environment variable.

- Example for **Windows**:
```
-DPython_ROOT_DIR="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev" 
-DCMAKE_PREFIX_PATH="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev;C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev\Library;C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev\Lib\site-packages" 
-DNUMPY_INCLUDE_DIR="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev_clion\Lib\site-packages\numpy\_core\include"
```

- Example for **macOS**:
```
-DPython_ROOT_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/"
-DCMAKE_PREFIX_PATH="/home/YourUsername/miniforge3/envs/python_c_ext_dev/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/bin/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/"
-DNUMPY_INCLUDE_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/numpy/_core/include/"
```

- Example for **Linux**:a
```
-DPython_ROOT_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/"
-DCMAKE_PREFIX_PATH="/home/YourUsername/miniforge3/envs/python_c_ext_dev/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/bin/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/"
-DNUMPY_INCLUDE_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/numpy/_core/include/"
```
