/**
    [UNIQUE] and [DYNAMIC] DINI Database Management System

    - [UNIQUE], so it is one of its kind
    - [DYNAMIC], because it is a great marketing term


    Studies show that this code is 100% halal.
    With some extra changes, that percentage has been increased to 159.2%.
*/

#define UDDDBMS_RESULT_FILE_NAME    "./udddbms/result.ini"

#include <Dini>

#define UDDDBMS_exists(%0) dini_Exists(%0)
#define udddbms_exists UDDDBMS_exists

#define UDDDBMS_remove(%0) dini_Remove(%0)
#define uddbms_remove UDDDBMS_remove

#define UDDDBMS_create(%0) dini_Create(%0)
#define udddbms_create UDDDBMS_create

#define UDDDBMS_set(%0,%1,%2) dini_Set(%0,%1,%2)
#define udddbms_set UDDDBMS_set

#define UDDDBMS_insert(%0,%1,%2) UDDDBMS_query(%0,"insert",%1,%2)
#define udddbms_insert UDDDBMS_insert

#define UDDDBMS_delete(%0,%1) UDDDBMS_delete(%0,"delete",%1)
#define udddbms_delete UDDDBMS_delete

static stock UDDDBMS_query(fileName[], query[], key[], value[])
{
    // Using a quite large array for a way smaller string
    // Increased it some more just uncase of your extra large files :DDD
    new query_file_name[4096];
    format(query_file_name, "./udddbms/%s.ini", query);
    if (UDDDBMS_exists(query_file_name))
    {
        UDDDBMS_remove(query_file_name);
    }
    UDDDBMS_create(query_file_name);
    UDDDBMS_set(query_file_name, "fileName", fileName);
    UDDDBMS_set(query_file_name, "key", key);
    if (strlen(value) > 0)
    {
        UDDDBMS_set(query_file_name, "value", value);
    }
    return CallRemoteFunction("UDDDBMS_receive", "s", query);
}

stock UDDDBMS_select(fileName[], key[], value[], value_size = sizeof value)
{
    new ret[DINI_MAX_STRING];
    if (UDDDBMS_query(fileName, "select", key, ""))
    {
        if (UDDDBMS_exists(UDDDBMS_RESULT_FILE_NAME))
        {
            // Returning arrays from PAWN functions is one of the best ideas
            ret = dini_Get(UDDDBMS_RESULT_FILE_NAME, "value");
        }
    }
    // Returning arrays from PAWN functions is one of the best ideas
    return ret;
}
