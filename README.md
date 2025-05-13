# What is genutils?

Genutils is the attempt to rewrite some of the main GNU core utils.
Commands ends with prefix with "g" to indicate genutils and don't conflict with other commands.

# The goals of genutils

1. Simplicity over complexity
2. Learning CLI tools and improve my understanding of C
3. Focus on the Linux side first

## lsg (list directories and files)

- [x] list objects if path provided
- [x] get the all files and directories in the list by column (-l)
- [x] show hidden files (-a)
- [x] list directories recursively (-R)
- [x] output with colors
- [ ] sort items by default and select certain algorithm if argument is provided (-s)

## cpg (copy files and/or directories)

- [ ] cp directory (-r)
- [ ] add verbose output (-v)
- [ ] print amount of bytes copied

## catg (read the files and print their context)

- [x] line counter (-n, --line-counter)
- [ ] colorful output (-c, --colorful)
- [ ] read from stdin


# Contribution

If you have found bug, please describe it in the issues section or
fork the project, fix an error and create pull request.

# License

The project created for educational purposes and LICENSED under MIT. (See [LICENSE](LICENSE) file)

# References

1. [StackOverflow: Checking if a directory exists in Unix](https://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call)
2. [What is mode_t in C?](https://jameshfisher.com/2017/02/24/what-is-mode_t/)
3. [How to pass function as parameter in C](https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c)
4. [Stat function manual](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html)
5. [Reddit: building cross-platform C programs](https://www.reddit.com/r/C_Programming/comments/132ma0u/how_do_you_build_crossplatform_c_programs/)
6. [Unicode colors](https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a)