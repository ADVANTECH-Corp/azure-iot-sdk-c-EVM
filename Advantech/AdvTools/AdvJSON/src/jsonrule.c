#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jsontool.h"
#include "jsonrule.h"


size_t IsString(const char *json) {
	//int len = 0;
	char *s;
	char *e;
	char *b = NULL;
	char *p = (char *)json;
	char *pp;
	p = skip(p);
	if(*p != '\"') return 0;
	s = p; //string start;
	p++;
	pp = p;
	p = strchr(p,'\"');
	if(p == NULL) return selen(pp,s);
	else {
		b = p-1;
		while(*b == '\\') {
			p++;
			pp = p;
			p = strchr(p,'\"');
			if(p == NULL) return selen(pp, s);
			b = p-1;
		}
	}
	e = p; //string end;
	p++;
	p = skip(p);
	if(*p == ':' || *p == ',' || *p == '}' || *p == ']') {
		return selen(e, s) + 1;
	} else return selen(p, s);
}

size_t IsNumber(const char *json) {
	size_t len = 0;
	char *p = (char *)json;
	p = skip(p);
	if(*p != '-' && !isdigit(*p)) return 0;
	len = strspn(p,"+-01234567890.eE");
	p+=len;
	p = skip(p);
	if(*p == ',' || *p == '}' || *p == ']') {
		return len;
	} else return 0;
}

size_t IsObject(const char *json) {
	int len = 0;
	size_t eleLen = 0;
	char *s;
	char *e;
	char *p = (char *)json;
	p = skip(p);
	if(*p != '{') return 0;
	s = p; //object start
	p++;
	p = skip(p);
	if(*p == '}') {
		e = p; //object end
		p++;
		p = skip(p);
		if(*p == ',' || *p == '}' || *p == ']' || *p == '\0') {
			return selen(e, s)+1;
		} else return selen(p, s);
	}
	eleLen = IsString(p);
	if(eleLen == 0) return 0;
	p += eleLen;
	p = skip(p);
	if(*p != ':') return selen(p, s);
	p++;
	p = skip(p);
	eleLen = IsValue(p);
	if(eleLen == 0) return 0;
	p += eleLen;
	p = skip(p);
	
	while(*p == ',') {
		p++;
		p = skip(p);
		eleLen = IsString(p);
		if(eleLen == 0) return 0;
		p += eleLen;
		p = skip(p);
		if(*p != ':') return selen(p, s);
		p++;
		p = skip(p);
		eleLen = IsValue(p);
		if(eleLen == 0) return 0;
		p += eleLen;
		p = skip(p);
	}
	
	if(*p == '}') {
		e = p; //object end
		p++;
		p = skip(p);
		if(*p == ',' || *p == '}' || *p == ']' || *p == '\0') {
			return selen(e, s)+1;
		} else return selen(p, s);
	} else return selen(p, s);
	
	
}

size_t IsArray(const char *json) {
	int len = 0;
	size_t eleLen = 0;
	char *s;
	char *e;
	char *p = (char *)json;
	p = skip(p);
	if(*p != '[') return 0;
	s = p; //array start
	p++;
	p = skip(p);
	if(*p == ']') {
		e = p; //array end
		p++;
		p = skip(p);
		if(*p == ',' || *p == '}' || *p == ']') {
			return selen(e, s)+1;
		} else return selen(p, s);
	}
	eleLen = IsValue(p);
	if(eleLen == 0) return selen(p, s);
	p += eleLen;
	p = skip(p);
	
	while(*p == ',') {
		p++;
		p = skip(p);
		eleLen = IsValue(p);
		if(eleLen == 0) return selen(p, s);
		p += eleLen;
		p = skip(p);
	}
	
	if(*p == ']') {
		e = p; //array end
		p++;
		p = skip(p);
		if(*p == ',' || *p == '}' || *p == ']') {
			return selen(e, s)+1;
		} else return selen(p, s);
	} else return selen(p, s);
	
}

size_t IsValue(const char *json) {
	size_t len = 0;
	char *p = (char *)json;
	p = skip(p);

	switch(*p) {
		case 't':
			if(strlen(p) >= 4 && strncmp(p,"true",4) == 0) {
				p+=4;
				p = skip(p);
				if(*p == ',' || *p == '}' || *p == ']') {
					return 4;
				} else return 0;
			} else return 0;
		case 'f':
			if(strlen(p) >= 5 && strncmp(p,"false",5) == 0) {
				p+=5;
				p = skip(p);
				if(*p == ',' || *p == '}' || *p == ']') {
					return 5;
				} else return 0;
			} else return 0;
		break;
		case 'n':
			if(strlen(p) >= 4 && strncmp(p,"null",4) == 0) {
				p+=4;
				p = skip(p);
				if(*p == ',' || *p == '}' || *p == ']') {
					return 4;
				} else return 0;
			} else return 0;
		default:
			len += IsString(p);
			if(len != 0) return len;
			len += IsObject(p);
			if(len != 0) return len;
			len += IsArray(p);
			if(len != 0) return len;
			len += IsNumber(p);
			if(len != 0) return len;
			break;
	}

	return len;
}


