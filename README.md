
# BFG for Windows

This repository contains a build script that downloads version 1.13.0 of the
[BFG Repo Cleaner](https://github.com/rtyley/bfg-repo-cleaner), and a small
application that launches it. Note that you will need Java 1.8 installed for
this program to work. 

The BFG Repo Cleaner itself is licensed under the GNU General Public License,
version 3 or (at your option) any later version. However, other parts of
this repository may be licensed under different terms. See the
[LICENSE.md](./LICENSE.md) file for exact details.


### Requirements

- Java 1.8 (Java 1.7 is no longer supported.)
- Visual Studio 2017 C++ runtime (If not run with Chocolatey)

### Installation

Simply download the two files in the release, place them in the same directory, and ensure that the prerequisites (Java 1.8 and the Visual Studio 2017 C++ runtime) are installed. No other configuration is required; BFG will then launch from a Command Prompt. (If Java 1.8 is missing, BFG.exe will fail gracefully.) - See [Release page](https://github.com/wjk/BFG-Windows/releases/tag/v1.13.0)

You can also use [Chocolatey](https://chocolatey.org/), the package manager for Windows. (See instructions of Chocolatey in source page)