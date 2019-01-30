// =-=-=-=-=-=-=-
// irods includes
#include "irods_error.hpp"
#include "irods_ms_plugin.hpp"

// =-=-=-=-=-=-=-
// stl includes
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstring>
#include <regex.h>

struct { const char* key; int value;}
    flags_table [] =
{
    {"REG_EXTENDED", REG_EXTENDED },
    {"REG_ICASE", REG_ICASE },
    {"REG_NEWLINE", REG_NEWLINE }
};

int search_flags_table ( const char *lkp ) {
    int cumul_flag = 0;
    for (int i = 0 ; i < sizeof(flags_table)/sizeof(flags_table[0]); i++) {
        if (std::strstr(lkp,flags_table[i].key)) cumul_flag |= flags_table[i].value;
    }
    return cumul_flag;
}

int msimicroservice_match_regex(
    msParam_t*      _string1_param,
    msParam_t*      _string2_param,
    msParam_t*      _offset_in_param,
    msParam_t*      _flags_in_param,
    msParam_t*      _begin_out_param,
    msParam_t*      _end_out_param,
    ruleExecInfo_t* _rei ) {

    const char* str = parseMspForStr(_string1_param);
    const char* ptn = parseMspForStr(_string2_param);
    const char* flg = parseMspForStr(_flags_in_param);
    int ofs = parseMspForPosInt(_offset_in_param);
    int bgn = -1 , end = -1;
    regmatch_t  matches[1];
    regex_t ptnBuf;

    if (0 == regcomp (&ptnBuf, ptn, search_flags_table(flg))) {
        if (0 == regexec (&ptnBuf, str + ofs, 1, matches, 0)) {
            bgn = ofs + matches[0].rm_so;
            end = ofs + matches[0].rm_eo;
        }
    }
    regfree(&ptnBuf);
    fillIntInMsParam( _begin_out_param, bgn);
    fillIntInMsParam( _end_out_param  , end);
    return 0;
}

extern "C"
irods::ms_table_entry* plugin_factory() {
    irods::ms_table_entry* msvc = new irods::ms_table_entry(6);
    msvc->add_operation<
        msParam_t*,
        msParam_t*,
        msParam_t*,
        msParam_t*,
        msParam_t*,
        msParam_t*,
        ruleExecInfo_t*>("msimicroservice_match_regex",
                         std::function<int(
                             msParam_t*,
                             msParam_t*,
                             msParam_t*,
                             msParam_t*,
                             msParam_t*,
                             msParam_t*,
                             ruleExecInfo_t*)>(msimicroservice_match_regex));
    return msvc;
}

