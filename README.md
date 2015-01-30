# lsh
A basic linux shell

## Functionality

### Program and arguments
Unlike most shells, arguments are not split on space, but on ` $`, so the
command `ls -alh --color=auto` in bash is instead written `ls $-alh $--color=auto`. This is to avoid the "space issue" that plagues bash.
It is possible that this will change in later versions.

### Redirect streams
`!infile` works like `<infile` in Bourne shell (redirect stdin)  
`@outfile` works like `>outfile` in Bourne shell (redirect stdout)  
`@#` works like `>&2` in Bourne shell (redirect stdout to stderr)  
`#errfile` works like `2>outfile` in Bourne shell (redirect stderr)  
`#@` works like `2>&1` in Bourne shell (redirect stderr to stdout)  
```
. @outfile $echo $Hello world!
. cat $outfile
Hello world!
```

If you redirect two streams in one command you will need to put a space between them.
```
@/dev/null $#@ $command-without-stdout-and-stderr
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
. path $echo
echo: /bin/echo
```
