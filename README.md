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
. 
```
