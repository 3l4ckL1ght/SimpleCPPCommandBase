SimpleCPPCommandBase
====================

This main.cpp is a Command Base for your C++ Command. The sheme of command writing looks like this:<br>
``command <subcommand> <[args]>``

It is also possible to open a simulated console for this subcommands. It can be accessed by only writing the command name.


Adding a Command
----------------
Make a new class and let it extend from Command. Then build a constructor and initialize Command by giving it the subcommand name.
Override the call Command void function and build in it your executeable.

Registering the Command
---------------------
The register function is in the CommandHandler private section. It is highlighted with a comment.
To add your command use the same spelling as the test command got registered.

After that you built your first subcommand. It can now be executed as in the example seen above.

Working with the simulated console
----------------------------
To use it, write only the command name without arguments. After that, subcommands can be accessed like normal commands.
