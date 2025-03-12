# 🚀 MagicManager - Development Setup (macOS)

## 📌 Prerequisites
Before setting up the project, ensure you have the following installed:

- **Xcode Command Line Tools** (for compilers)
- **Homebrew** (for installing dependencies)
- **Qt 6** (for GUI development)
- **SQLite** (for database handling)
- **CMake (optional)** (if switching to a CMake build system in the future)
- **VS Code (Recommended)** or any C++ IDE

---

## 🚀 Step 1: Install Homebrew
If you don’t have **Homebrew**, install it with:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## 🚀 Step 2: Install Required Dependencies
Run the following commands to install **Qt, SQLite, and CMake**:

```bash
brew install qt sqlite cmake
```

## 🚀 Step 3: Clone the Repository
To get the project source code, clone the repository using Git:

```bash
git clone https://github.com/your-username/MagicManager.git
```

## 🚀 Step 4: Set Up Qt for Development
### 🔹 Add Qt to Your Path
Ensure that Qt is accessible from the terminal by adding it to your `PATH`:

```bash
export PATH="/opt/homebrew/opt/qt/bin:$PATH"
echo 'export PATH="/opt/homebrew/opt/qt/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

## 🚀 Step 5: Build the Project
Once the environment is set up, compile the application using the following commands:

```bash
cd MagicManager
qmake
make
```

## 🚀 Step 6: Run the Application
After successful compilation, launch the application with the following command:

```bash
./MagicManager.app/Contents/MacOS/MagicManager
```

## 🚀 Step 7: Setting Up VS Code (Optional)
For **VS Code users**, ensure you have the following extensions installed:
- **C/C++ Extension** (Microsoft)
- **Qt Tools Extension**

### 🔹 Configure VS Code IntelliSense
To ensure VS Code can find Qt headers, update `.vscode/c_cpp_properties.json` with the correct include paths:

```json
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/opt/qt/include",
                "/opt/homebrew/opt/qt/include/QtCore",
                "/opt/homebrew/opt/qt/include/QtSql",
                "/opt/homebrew/opt/qt/include/QtWidgets"
            ],
            "compilerPath": "/usr/bin/clang++",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
        }
    ],
    "version": 4
}
```

## 🚀 Step 8: Troubleshooting

### 🔹 `qmake: command not found`
If `qmake` is not found, try linking Qt manually:

```bash
brew link qt --force
```

### 🔹 `SQLite Database Not Found`
The goal is to fetch this automaticaly in time. For now, manual download and place in the /Data dir
Download 'AllPrintings.sqlite' from: https://mtgjson.com/downloads/all-files/

