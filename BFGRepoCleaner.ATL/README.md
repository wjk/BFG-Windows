To build the BFG Repo Cleaner, you may need to install a copy of
ATL into this directory. (They are not included in the repository
for copyright reasons.) If you are using the full install of Visual
Studio "15" Preview, you will not need to do this. If you are using
the Lightweight Install option, as I am, you will need to do this,
because the Lightweight Install does not currently support ATL natively.

Copy the `*.h` files from the `VC\atlmfc\include` directory inside
of a "full" installation of Visual Studio into this directory. (For example,
Visual Studio 2015 places these files in the `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include`
directory. You will also need to copy the file `atls.lib` into this directory;
it can be found in `VC\atlmfc\lib`. You will need to copy the version of the
library that is appropriate for the processor architecture you are targeting.
