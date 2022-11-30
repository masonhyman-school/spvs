![](https://raw.githubusercontent.com/masonhyman-school/spvs/main/spvs_server/public/images/spvs-high-resolution-logo2.png?token=GHSAT0AAAAAAB3XYLHGM2Y3DDICSRCCUACSY4HPP7Q)

# SPVS - Simple Port and Vulnerability Scanner

## Contributors 👨‍💻
* Ankit Mistry - GithubID: ankitm28
* Cody Blankenship - GithubID: codyb42
* Mason Hyman - GithubID: masonhyman-school
* Saish Malluri - GithubID: smalluri
* Shivam Mistry - GithubID: smistry4

## Product Description ℹ️
As the name states, SPVS is a easy-to-use port scanning utility. Available both as a CLI tool for UNIX machines and as a web service, SPVS seeks to make port scanning and identification as easy as possible. Users may either specifiy targets to SPVS or upload a file with a list of targets to begin scanning. Once scanning has begun, SPVS will compile the open ports on the specified target machines as well as the service running. This information is then printed to the user in a modular format.

## Install ⬇️
Because our project is broken into two primary parts, web and CLI, there are two seperate install procedures. In order to install the SPVS server, **the SPVS CLI must be installed first!** 

### SPVS CLI
SFML - This project uses the SFML library to function. In order to use SPVS, SFML must be installed as follows. 

1. Clone the SPVS repository at [https://github.com/masonhyman-school/spvs.git](https://github.com/masonhyman-school/spvs.git).
2. Inside this directory, navigate to spvs/spvs_cli. After you are in this location, clone the SFML library at [https://github.com/masonhyman-school/spvs.git](https://github.com/masonhyman-school/spvs.git)
3. Once cloned, SFML will need to be built according to this tutorial: [Building SFML using CMake](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)
4. After SFML has been correctly installed, use the Makefile in spvs_cli to compile the project.
5. A working binary will be created in bin/spvs and can be run in the spvs_cli directory using `bin/spvs`
6. Without any arguments, SPVS will automatically print the usage.

### SPVS SERVER
 


## Usage 🛠

### SPVS CLI
In order to access usage of SPVS execute `bin/spvs` from the spvs_cli directory. **Important:** when using SPVS CLI you must remain in the cli directory in order for the SFML library to be appropriately accessed and compiled. 

If using the file specification feature, hostnames must be seperated in the file by a space or an return.

Port scanning can be specified by a single port or a range of ports by doing `bin/spvs -p start-end hostname`. It is important to note that flag arguments must come directly after the flag itself.

## Licenses 📑
All license infomation may be found at `spvs/LICENSE.txt`

