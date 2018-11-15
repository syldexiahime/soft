#include "utils/helpers.h"

inline int    parse_int(char * s)    {    int n; sscanf(s, "%d",  &n); return n; }
inline int    parse_hex(char * s)    {    int n; sscanf(s, "%x",  &n); return n; }
inline int    parse_oct(char * s)    {    int n; sscanf(s, "%o",  &n); return n; }
inline float  parse_float(char * s)  {  float n; sscanf(s, "%f",  &n); return n; }
inline double parse_double(char * s) { double n; sscanf(s, "%lf", &n); return n; }

inline char * int_to_str(int i)       { char * b = smalloc(snprintf(NULL, 0, "%d", i)); sprintf(b, "%d", i);     return b; }
inline char * float_to_str(float f)   { char * b = smalloc(snprintf(NULL, 0, "%f", f)); sprintf(b, "%f", f); return b; }
inline char * double_to_str(double d) { char * b = smalloc(snprintf(NULL, 0, "%f", d)); sprintf(b, "%f", d); return b; }

inline bool ishex(char c) { return c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || isnumber(c); }
inline bool isoct(char c) { return c != '8' && c != '9' && isnumber(c); }
inline bool isbin(char c) { return c == '0' || c == '1'; }

bool str_is_double(char * str)
{
	for (size_t i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.')    return true;
		if (!isnumber(str[i])) return false;
	}

	return false;
}

char * str_replace_at(char * dst, char * src, size_t pos, size_t rlen)
{
	assert(pos  > 0);
	assert(rlen > 0);

	size_t dstlen = strlen(dst);
	size_t srclen = strlen(src);
	size_t nlen = dstlen + srclen;

	size_t npos;
	size_t endreplpos = pos + rlen;
	for (size_t i = 0; i < dstlen - pos; i++) {
		npos = dstlen - i;
		dst[npos + srclen - rlen] = dst[npos];
	}
	for (size_t i = 0; i < srclen; i++) {
		npos = pos + i;
		dst[npos] = src[i];
	}

	return dst;
}
