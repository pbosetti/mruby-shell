# @!method shell(cmd)
# Runs a command in shell and returns the result as a String.
# This method is portable and should work on Mac, Linux, and Windows (but the
# invoked command must be supported by the OS!)
# @example List the current directory (on Max or Linux):
#   shell("ls #{dir}") #=> a String containing the list of files in `dir`
# @example List the current directory (on Windows):
#   shell("dir #{dir}") #=> a String containing the list of files in `dir`
# @param cmd [String] the command to be executed
# @return [String] if input=nil, an Array with the command output and the command exit code, otherwise a Fixnum representing the command exit code
# @author Bosetti

# @!method async(cmd, stdin="", stdout="/dev/null")
# Runs a command in asyncronously in a separate process.
# This method is portable and should work on Mac, Linux, and Windows (but the
# invoked commant must be supported by the OS!)
# @example List the current directory (on Max or Linux):
#   async("ls #{dir}", "", "ls.out") #=> returns process ID and puts into "ls.out" a String containing the list of files in `dir`
# @example List the current directory (on Windows):
#   shell("dir #{dir}", "", "ls.out") #=> returns process ID and puts into "ls.out" a String containing the list of files in `dir`
# @param cmd [String] the command to be executed
# @param stdin [String] default standard input for subcommand
# @param stdout [String] default standard output for subcommand
# @return [Fixnum] ID of subprocess
# @author Bosetti

