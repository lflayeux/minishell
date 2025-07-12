# LIST OF STANDART EXIT CODES

> |Exit code|Meaning|
> |---------|-------|
> |0|Success: The command or script executed without errors.|
> |1|General error: A generic error occurred during execution.|
> |2|Misuse of shell builtins: Incorrect usage of a shell built-in command.|
> |126|Command invoked cannot execute: Permission denied or command not executable.|
> |127|Command not found: The command is not recognized or available in the environment’s PATH.|
> |128|Invalid exit argument: An invalid argument was provided to the exit command.|
> |130|Script terminated by Ctrl+C (SIGINT).|
> |137|Script terminated by SIGKILL (e.g., kill -9 or out-of-memory killer).|
> |139|Segmentation fault: Indicates a segmentation fault occurred in the program.|
> |143|Script terminated by SIGTERM (e.g., kill command without -9).|
> |255|Exit status out of range: Typically, this happens when a script or command exits with a number > 255.|






>   ## TODO
>
>   - [] exit built_in 
>   - [] CTRL C error signal code in term and child code 130
>   - [] Signaux here_doc
>   - [] Bloquer Ctrl \ in here_doc
>   - [] Bloquer si env -i
>   - [] close < infile
<!-- >   - [] << ENDcat pb -->



export: ʻ9HOLA=': not a valid identifier
> bash: export: -H: invalid option
> bash: !LA=bonjour: event not found
> bash: jour: command not found
> bash: ls: No such file or directory
> chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
> ls | env ls: write error: Broken pipe

