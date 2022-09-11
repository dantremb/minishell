# minishell

- Show a prompt waiting for a new command.
- History management.
- Single quote avoid all the special characters.
- Double quote avoid all the special characters except `$`.
- Launch executable with their absolute or relative path.
- "<" redirect input.
- ">" redirect output.
- "<<" open here document.
- ">>" redirect output with append mode.
- "|" implement pipe.
- "$" implement environment variable.
- "$?" implement the last return code.
- ctrl-C show new prompt.
- ctrl-D exit minishell.
- ctrl-\ do nothing.
- echo with -n
- cd only with a relative or absolute path.
- pwd with no options.
- export with no options.
- unset with no options.
- env with no options.
- exit  with no options.

# Test to do

<<end cat
<< end cat
<infile cat
< infile cat
echo test > outfile
echo test >outfile
echo test >> outfile
echo test >>outfile

<<end cat | << end cat | <infile cat | < infile cat | echo test > outfile | echo test >outfile | echo test >> outfile | echo test >>outfile

