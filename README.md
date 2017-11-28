# How to create a new plugin

Creating a new plugin can be sinplified by running the PluginWizard in order to duplicate all the code of another plugin to get you started. It will rename all the boilerplate code that makes it integrated in the LabExe plugin system. 
However, using external header/libraries, from third parties (eg: camera company, optimization framework,...) can complicate the process.
Here are some guidelines that can be used for lab users that are not familiar with C++ or compiling code:

  * Find some very simple example code for the task you are trying to achieve (eg: a single file camera snatching code, or a simple fitting routine,...)
  * Try to compile it and run it using the advised compiler. If you cannot comile/run it on its own, there is no point in attempting to integrate it in a LabExe plugin.
  * Make a simple standalone Qt creator project and try to compile/run the same example code. you know the code works, so this step is going to be about telling Qt Crator where are the needed header files and libraries. Those things happen in the project ".pro" file.
  * Now that you have an idea of what the ".pro" file needs to contain, try to add those needed lines into the newly duplicated plugin ".pro"
  * In a single function of the plugin's main class, copy some/all of the example code that worked in the standalone project. Things should compile (or trigger error messages that you have to decipher to know what is the culprit)
  * Start modifying the code to make it do things that you care about.
  * Save your progress regularly by commiting into the git repo and pushing.

# Help

If something doesn't work and you don't find a silution online (eg, on stakoverflow.com), you can open a new issue on the LabExe-UserPlgins [issue page](https://github.com/GaelReinaudi/LabExe-UserPlugins/issues).

Thanks,
Gael Reinaudi