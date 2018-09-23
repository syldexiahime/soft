#include "utils/helpers.h"

inline int   parse_int(char * s)   {   int n; sscanf(s, "%d", &n); return n; }
inline int   parse_hex(char * s)   {   int n; sscanf(s, "%x", &n); return n; }
inline int   parse_oct(char * s)   {   int n; sscanf(s, "%o", &n); return n; }
inline float parse_float(char * s) { float n; sscanf(s, "%f", &n); return n; }

inline bool ishex(char c) { return c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || isnumber(c); }
inline bool isoct(char c) { return c != '8' && c != '9' && isnumber(c); }
inline bool isbin(char c) { return c == '0' || c == '1'; }

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
