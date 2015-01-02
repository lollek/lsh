# lsh
A basic linux shell

## Functionality

### Redirect streams
`$infile` works like `<infile` in bash (redirect stdin)  
`@outfile` works like `>outfile` in bash (redirect stdout)  
`#errfile` works like `2>outfile` in bash (redirect stderr)
```
. @outfile echo Hello world!
. cat outfile 
Hello world!
```

### Path
path is used like $PATH in Bourne shell. It's a set of locations where the shell looks for programs to execute.  Each folder in path is tried in ascending order until a program is found.  
`path` displays the current path.
```
. path
0: /usr/local/bin
1: /usr/bin
2: /bin
```
If you want to know which program that will be run by a given command, you type `path program`.
```
. path echo
echo: /bin/echo
```
