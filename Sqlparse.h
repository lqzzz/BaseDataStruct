#ifndef _TOKENIZER_H
#define _TOKENIZER_H
#include<stdint.h>
#include "Listhead.h"
#include "str.h"
#include "dict.h"
#include "Vector.h"
#include "Pair.h"
#include "DB.h"
#include "Scanner.h"
#include "Parse_Select.h"

int sql_parse(DBnode *dbnode, Srcstream* stream);
#endif // !_TOKENIZER_H
 