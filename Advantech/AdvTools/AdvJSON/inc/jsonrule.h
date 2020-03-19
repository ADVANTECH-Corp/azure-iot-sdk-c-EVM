/****************************************************************************/
/* Copyright(C) : Advantech Technologies, Inc.								*/
/* Create Date  : 2015/09/25 by Fred Chang									*/
/* Modified Date: 2015/09/25 by Fred Chang									*/
/* Abstract     : Advantech JSON Library    						        */
/* Reference    : None														*/
/****************************************************************************/
#ifndef __JSON_RULE_H__
#define __JSON_RULE_H__

size_t IsString(const char *json);
size_t IsNumber(const char *json);
size_t IsValue(const char *json);
size_t IsObject(const char *json);
size_t IsArray(const char *json);

#endif //__JSON_RULE_H__