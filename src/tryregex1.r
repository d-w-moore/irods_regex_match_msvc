mainrule {
  test
}

#msiregex_match_nocase:  input string * input string * output integer * output integer -> integer
#                             str           pattern           begin           end

test() {
    writeLine("stdout", "this is a test")
    *string = "hello"
    *pattern = "EL"
    *b = -99; *e = -99;
    # msiregex_match_nocase( *string )
    msimicroservice_rematch( *string, *pattern, *b, *e )
    writeLine('stdout', '[*b] [*e]')
}
OUTPUT ruleExecOut

