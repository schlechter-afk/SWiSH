<!-- file is written in markdown format -->

```
Welcome to SWiSH
A modified Linux Styled C-Shell
```

```
Extract the .tar.gz file and then:

$ make
$ ./shell
```

Main Files :
```
main.c containing driver code
```
```
execute.c containing the the code required to properly tokenize the input commands and calling the appropriate function based on the entered input
```
```
globals.h including all globals required throughout the implementation of shell.
```
```
headers.h including all the libraries required for proper functioning.
```

```
General Assumptions: Unreasonably large input path should not be given.Reasonable commands executed at a time and each command should be of reasonable length.
```

# ****Specification 1,2 : prompt , cd , echo , pwd****

```
Files :
cd.c cd.h
```
```
echo.c echo.h
```
```
pwd.c pwd.h
```

# ****Specification 3: ls****

```
Files :
ls.c ls.h
```
```
Handles ls command printing all files/sub-directories

Colors implemented:
Directory : (blue)
Executables : (green)
Archive Files : (red)
Image files : (magenta)
```

# ****Specification 4, 6: Foreground / Background processes****

```
Files :
fg.c fg.h
```
```
Shell able to run multiple foreground and background processes, and not just one. Running pinfo on each of these works as well.

Assumption : It is expected that the user enters a space between the time argument of the sleep function and the & operator differentiating this process from the other commands in the same line.
In case of multiple processes in command-line , sometimes the ending signal will printed in the command prompt bar and user will have to enter the enter button to start a new-line of command argument.
For multiple sleep commands running in foreground : The program prints the time taken by sleep command entered in the last.
```
```
Example Input
Here the user needs to press the enter button to start a new-line of commands. 
```

<img src="Assumption1.jpeg"></img>

<img src="Assumption2.jpeg"></img>

# ****Specification 5: pinfo****

```
Files :
pinfo.c pinfo.h
```
```
Prints the process info of the given pid (current process if none is given)
```

# ****Specification 7: discover****

```
Files :
discover.c discover.h
```
```
For reasonable and sound input this command lets the user to search for files recursively in all the sub-folders of the given folder and returns the location of the entered file , handling flags such as -d (only directories) and -f (only files) too , hence emulating the idea of the find functionality in actual linux terminal.
Hidden folders would not be searched for any input file.
```

# ****Specification 8: history****

```
Files :
history.c history.h history.txt
```
```
Adds a command to a history log (here history.txt) storing the commands entered by the user (only when the previous command entered was not equal to the current command).
The log stores the latest 20 unique commands entered by the user.
Whenever history command is called , the latest 10 are printed.When the commmands stored in the log exceeds 20 , we pop the oldest command out of the log and push the latest command into the log.
```
# ****Assignment - 3****

# ***Specification 1: I/O Redirection***
# ***Specification 2: Command Pipelines***
# ***Specification 3: I/O Redirection within command pipelines***
# ***Specification 4: User-defined commands***
# ***Specification 5: Signal Handling***
# ***Specification 6: Autocompletion***


```
Spec 1,2,3 included in execute.c pipe.c
```
```
File with function to execute piped commands.
<, >, >> and | will always have their special meanings and will be used correctly. This means that for I/O redirection, a file will always come after the arrow. Similary, a command will always come after a pipe.
```
```
Spec 4,5,6 
Earlier int main made void mainfunc() and autocomplete main is the now new int main()
```

```
For spec-4 Files : jobs.c sig.c fgjobs.c bgjobs.c
```

```
For spec-5 Files : All signals handled in fg.c and mainfunc.c
Assumption : Ctrl-c , ctrl-z wont work after multiple fg jobs call as W_UNTRACED
```

```
For spec-6 Files : main.c
Assumption : For folders , autocomplete works under current directory folders only.
```

<p>Made with <span style="font-size:150%;color:red;">&hearts;</span> by Swayam !</p>
