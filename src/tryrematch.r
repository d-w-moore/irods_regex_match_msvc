mainrule {
  test
}

#msiregex_match_nocase:  input string * input string * output integer * output integer -> integer
#                             str           pattern           begin           end

test() {
    *icase = "REG_ICASE"; *extended="REG_EXTENDED"; *newline = "REG_NEWLINE"
    writeLine("stdout", "this is a test")
    *string = "hel\nEl\nelo"
    *pattern = "el"
    *b = 0; *e = 0;
    while (*b >= 0) {
      *ofs = *e;
      msimicroservice_rematch ( *string, *pattern, *ofs, *extended ++ *icase , *b, *e )
      writeLine('stdout', 'match: begin [*b] end [*e] ')
    }
}
#INPUT  *string=$'',*pattern=$''
OUTPUT ruleExecOut
