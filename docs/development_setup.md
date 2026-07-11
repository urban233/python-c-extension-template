# Development Setup

This project supports development in **Python**, **C++**, or a **hybrid Python/C++ workflow**.
Please follow the setup instructions carefully depending on your use case.

---

## Prerequisites

* [**Miniforge3**](https://conda-forge.org/download/) (or another Conda distribution)

---

## ⚠️ Important Note on JetBrains IDEs on Windows (and maybe other platforms)

Due to current issues with **PyCharm** and **CLion**, configuring a project interpreter is unreliable when reusing existing Conda environments.

❗ **Workaround (Required):**
You must create a **new Conda environment through the IDE GUI** (PyCharm or CLion).
Using an already existing environment is currently **not supported** and may lead to misconfiguration.

After creating the environment, install dependencies using the provided `environment.yml`.

---

## Development

### 1. Set up the Conda Environment
Python-Cpp-Extension uses **Conda** for dependency management for both Python and C++.

#### Steps:

1. Open the repository in **CLion**.
2. Create a new Conda environment:

    * Go to **Settings → Build, Execution, Deployment → Python Interpreter**
    * Add a new interpreter → **Conda Environment**
    * Select **New environment** and choose **3.13**
    * Choose a name like `python_c_ext_dev`
3. Once created, install dependencies:

    * Activate the environment
    ```bash
   conda activate python_c_ext_dev
    ```
   
    * For **Linux** (especially OpenSUSE) users:
   ```bash
   conda install -c conda-forge binutils_linux-64
   ```

    * Install all development dependencies using the environment.yml file
    ```bash
   conda env update --file environment.yml
    ```

📌 For detailed instructions, see the official guide:
[https://www.jetbrains.com/help/pycharm/conda-support-creating-conda-virtual-environment.html#conda-requirements](https://www.jetbrains.com/help/pycharm/conda-support-creating-conda-virtual-environment.html#conda-requirements)

---

### 3. Set up CMake (CLion)
Python-Cpp-Extension uses **CMake** for cross-platform build configuration of the C++ code.
**However**, if you are using **CLion**, it is recommended to set up the CMake
configuration even if you are only working with Python code.

If you are not using CLion, you have to translate the CMake configuration concepts
from CLion to your IDE of choice.

#### Steps:

1. Open the `CMake Settings` under the CMake tool window.
2. If necessary, create a new CMake profile: `Release`.
3. Enable both profiles, `Debug` and `Release`.
4. In the `CMake Options` text field, you have to define the following variables:
- Python_ROOT_DIR: This needs to point to the Conda environment you created in step 2.
- CMAKE_PREFIX_PATH: This needs to point to the Conda environment's root directory, as well as the _Library_ directory and the _site-packages_ directory.
- NUMPY_INCLUDE_DIR: This needs to point to the numpy include directory which is likely under the _site-packages_ directory of the Conda environment.

Example for **Windows**:
```
-DPython_ROOT_DIR="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev" 
-DCMAKE_PREFIX_PATH="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev;C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev\Library;C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev\Lib\site-packages" 
-DNUMPY_INCLUDE_DIR="C:\Users\YourUsername\Miniforge3\envs\python_c_ext_dev_clion\Lib\site-packages\numpy\_core\include"
```

Example for **macOS**:

```
-DPython_ROOT_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/"
-DCMAKE_PREFIX_PATH="/home/YourUsername/miniforge3/envs/python_c_ext_dev/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/bin/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/"
-DNUMPY_INCLUDE_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/numpy/_core/include/"
```

Example for **Linux**:
```
-DPython_ROOT_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/"
-DCMAKE_PREFIX_PATH="/home/YourUsername/miniforge3/envs/python_c_ext_dev/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/bin/;/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/"
-DNUMPY_INCLUDE_DIR="/home/YourUsername/miniforge3/envs/python_c_ext_dev/lib/python3.13/site-packages/numpy/_core/include/"
```

5. Reload the CMake configurations using the `Reload CMake Project` button in the CMake tool window. 

---

## Common Pitfalls

* ❌ Do **not** reuse existing Conda environments

* ❌ Do **not** open the same project in both PyCharm and CLion simultaneously

* ❌ Do **not** skip environment creation via IDE GUI

* ❌ Do **not** forget to configure `CMAKE_INSTALL_PREFIX` and `Python_ROOT_DIR`

* ✅ Always create a **new environment via the IDE**

* ✅ Always install dependencies using `environment.yml`

* ✅ Always configure CMake to use the Conda environment

---

If you run into setup issues, please open an issue in the repository with details about your environment and IDE configuration.
