#! bin/bash
rm -rf ./minishell_tester/outfiles
rm -rf ./minishell_tester/mini_outfiles
rm -rf ./minishell_tester/bash_outfiles
cd minishell_tester && ./tester 2>&1 tester_output