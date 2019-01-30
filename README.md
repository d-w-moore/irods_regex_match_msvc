# irods_regex_msvc

Microservice for multiple matches of a pattern within a string

   - allows searching from a specified offset
   - reports offset and length of next match each time
   - uses libc native calls, ie regcomp and regexec
