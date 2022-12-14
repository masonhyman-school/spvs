![](https://raw.githubusercontent.com/masonhyman-school/spvs/main/spvs_server/public/images/spvs-high-resolution-logo2.png?token=GHSAT0AAAAAAB3XYLHGM2Y3DDICSRCCUACSY4HPP7Q)

![SPVS-image](https://github.com/masonhyman-school/spvs/blob/main/spvs_server/public/images/spvs-high-resolution-logo2.png)

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
After installing and running SPVS CLI properly, you can start procedure for setting up SPVS SERVER.

1. Install Node.js on your computer, if it is not there already download it through [here](https://nodejs.org/en/).
2. After installing Node.js, cd into `spvs/spvs_server`.
3. Run `sh addDep.sh`.
4. Run the server by typing `sh runServer.sh`.
5. Open a browser, type `localhost:3000`, and the browser should render the website page.

## Usage 🛠

### SPVS CLI
In order to access usage of SPVS execute `bin/spvs` from the spvs_cli directory. **Important:** when using SPVS CLI you must remain in the cli directory in order for the SFML library to be appropriately accessed and compiled. 

If using the file specification feature, hostnames must be seperated in the file by a space or an return.

Port scanning can be specified by a single port or a range of ports by doing `bin/spvs -p start-end hostname`. It is important to note that flag arguments must come directly after the flag itself.

### SPVS SERVER
To run the server, cd into `spvs/spvs_server` directory. It is imperative that you are in this directory for shell script to work.   
Then, run `sh runServer.sh`, and in a browser window type `localhost:3000`.   
Once on the website, you can provide input in one of three ways:
1. You can enter the hostname and hit scan button.
2. You can enter the hostname and port number and hit scan button.
3. You can upload a file containing hostnames separated by spaces or newline and hit file upload.

On doing one of the three things, you will receive an output on the screen, and you will able to download a file containing that output.

## Licenses 📑
All license infomation may be found at `spvs/LICENSE.md`

