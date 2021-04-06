/*-------------------------------------------------------------------------
 *  *
 *   * int.c
 *    *        Functions for the built-in integer types (except int8).
 *     *
 *      * Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
 *       * Portions Copyright (c) 1994, Regents of the University of California
 *        *
 *         *
 *          * IDENTIFICATION
 *           *        src/backend/utils/adt/int.c
 *            *
 *             *-------------------------------------------------------------------------
 *              */
/*
 *  * OLD COMMENTS
 *   *              I/O routines:
 *    *               int2in, int2out, int2recv, int2send
 *     *               int4in, int4out, int4recv, int4send
 *      *               int2vectorin, int2vectorout, int2vectorrecv, int2vectorsend
 *       *              Boolean operators:
 *        *               inteq, intne, intlt, intle, intgt, intge
 *         *              Arithmetic operators:
 *          *               intpl, intmi, int4mul, intdiv
 *           *
 *            *              Arithmetic operators:
 *             *               intmod
 *              */
#include "postgres.h"

#include <ctype.h>
#include <limits.h>

#include "catalog/pg_type.h"
#include "funcapi.h"
#include "libpq/pqformat.h"
#include "utils/array.h"
#include "utils/builtins.h"
/*
 *  *              int4in                  - converts "num" to int4
 *   */
Datum
yearin(PG_FUNCTION_ARGS)
{
        char       *num = PG_GETARG_CSTRING(0);

        PG_RETURN_INT32(pg_atoi(num, sizeof(int32), '\0'));
}

/*
 *  *              int4out                 - converts int4 to "num"
 *   */
Datum
yearout(PG_FUNCTION_ARGS)
{
        int32           arg1 = PG_GETARG_INT32(0);
        char       *result = (char *) palloc(12);       /* sign, 10 digits, '\0' */

        pg_ltoa(arg1, result);
        PG_RETURN_CSTRING(result);
}

/*
 *  *              int4recv                        - converts external binary format to int4
 *   */
Datum
yearrecv(PG_FUNCTION_ARGS)
{
        StringInfo      buf = (StringInfo) PG_GETARG_POINTER(0);

        PG_RETURN_INT32((int32) pq_getmsgint(buf, sizeof(int32)));
}

/*
 *  *              int4send                        - converts int4 to binary format
 *   */
Datum
yearsend(PG_FUNCTION_ARGS)
{
        int32           arg1 = PG_GETARG_INT32(0);
        StringInfoData buf;

        pq_begintypsend(&buf);
        pq_sendint(&buf, arg1, sizeof(int32));
        PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}

