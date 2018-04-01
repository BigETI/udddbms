/**
    [UNIQUE] and [DYNAMIC] DINI Database Management System

    - [UNIQUE], so it is one of its kind
    - [DYNAMIC], because it is a great marketing term


    Studies show that this code is 100% halal.
*/

#define UDDDBMS_RESULT_FILE_NAME    "./udddbms/result.ini"

#include <Dini>

stock UDDDBMS_exists(fileName[])
{
    return dini_Exists(fileName);
}

stock UDDDBMS_remove(fileName[])
{
	return dini_Remove(fileName);
}

stock UDDDBMS_create(fileName[])
{
	return dini_Create(fileName);
}

static stock UDDDBMS_query(fileName[], query[], key[], value[])
{
    // Using a quite large array for a way smaller string
    new query_file_name[2048];
    format(query_file_name, "./udddbms/%s.ini", query);
    if (UDDDBMS_exists(query_file_name))
    {
        UDDDBMS_remove(query_file_name);
    }
    UDDDBMS_create(query_file_name);
    dini_Set(query_file_name, "fileName", fileName);
    dini_Set(query_file_name, "key", key);
    if (strlen(value) > 0)
    {
        diniSet(query_file_name, "value", value);
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

stock UDDDBMS_insert(fileName[], key[], value[])
{
    UDDDBMS_query(fileName, "insert", key, value);
}

stock UDDDBMS_delete(const fileName[], const key[])
{
    UDDDBMS_query(fileName, "delete", key, value);
}
