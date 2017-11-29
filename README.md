# How to create a new plugin

Creating a new plugin can be simplified by running the PluginWizard in order to duplicate all the code of another plugin to get you started. It will rename all the boilerplate code that makes it integrated in the LabExe plugin system. 
However, using external header/libraries, from third parties (eg: camera company, optimization framework,...) can complicate the process.
Here are some guidelines that can be used for lab users that are not familiar with C++ or compiling code:

  * Find some very simple example code for the task you are trying to achieve (eg: a single file camera snatching code, or a simple fitting routine,...)
  * Try to compile it and run it using the advised compiler. 
  * If you cannot compile/run the simplest code example, there is no point in attempting to integrate it in a LabExe plugin. Get help from the manufacturer or find solution for common IDE problems on stackoverflow.
  * Make a simple standalone Qt creator project and try to compile/run the same example. You already know the code can work, so this step is going to be about telling Qt Creator where are the needed header files and libraries. Those things happen in the project ".pro" file.
  * Now that you have an idea of what the ".pro" file needs to contain to access the dependencies, try to add those needed lines into the newly duplicated plugin ".pro" file. Run QMake (which parses the pro file). It should not complain.
  * In a single function of the plugin's main class (you can pick an existing function triggered by a push button), copy some/all of the example code that worked in the standalone project. 
  * The project should compile (or trigger error messages that you have to decipher to know what is the culprit).
  * Start LabExe and see if the plugin is loading. This is sometimes tough as you get very little feedback at runtime about what could be the cause of Qt deciding to not load the plugin.
  * Start modifying the code to make it do things that you care about.
  * Save your progress regularly by commiting into the git repo and pushing.
  * Create branches in git to isolate your changes and facilitate the review of what you did.

# Help

If something doesn't work and you don't find a solution online (manufacturer, stakoverflow.com,...), you can open a new [LabExe-UserPlgins Issue](https://github.com/GaelReinaudi/LabExe-UserPlugins/issues).

Thanks,
Gael Reinaudi