#include "ez_bytes.h"

/*
 * author : ez
 * date : 2015/11/26
 * describe : algorithm for bytes sequence.
*/

int ez_bytes_index_byte (bytes _s, byte _b, int _slen) {
  int i = 0;
  for (; i < _slen; i ++) {
    if (_s [i] == _b)
      return i;
  }
  return -1;
}

bool ez_bytes_equal_sep 
(bytes _s, bytes _sep, int _slen, int _seplen) {
  if (! _s || ! _sep || _slen != _seplen)
    return false;
  -- _slen;

  for (; _slen >= 0; -- _slen) {
    if (_s [_slen] != _sep [_slen])
      return false;
  }
  return true;
}


int ez_bytes_index_sep 
(bytes _s, bytes _sep, int _slen, int _seplen) {
  int i; // the index of _s
	char c;
  bytes ptr = _s;
  if (! _slen || ! _seplen || 
      _slen < _seplen || ! _s || ! _sep)
    return -1;
  
  i = 0;
	c = *_sep;

  for (; i < _slen; i ++) {
    int idx = ez_bytes_index_byte (ptr, c, _slen);
    if (idx < _slen - 1 || 
        (idx == _slen - 1 && _seplen == 1)) {
      if (ez_bytes_equal_sep (ptr, _sep, _seplen, _seplen))
        return idx;
    }
  }
	return -1;
}


int ez_bytes_count_bytes 
(bytes _s, bytes _sep, int _slen, int _seplen) {
  // int i = 0, // the index of _s
	int num = 0; 
	unsigned char c;
  bytes ptr = _s;
  if (! _slen || ! _seplen || 
      _slen < _seplen || ! _s || ! _sep)
    return -1;
	c = *_sep;

	while (ptr - _s < _slen) {
		int idx = ez_bytes_index_byte (ptr, c, _slen);
		if (idx < _slen - 1 ||
				(idx == _slen - 1 && _seplen == 1))
			if (ez_bytes_equal_sep (ptr, _sep, _seplen, _seplen)) {
				++ num;
				ptr += _seplen;
			} else 
				ptr += 1;
	}

	return num;
}


bool ez_bytes_hasprefix 
(bytes _s, bytes _sep, int _slen, int _seplen) {
	return _seplen <= _slen && 
		ez_bytes_equal_sep (_s, _sep, _seplen, _seplen);
}


bool ez_bytes_hassuffix 
(bytes _s, bytes _sep, int _slen, int _seplen) {
	return _seplen <= _slen && 
		ez_bytes_equal_sep (_s + _slen - _seplen, _sep, _seplen, _seplen);
}


// convert from unsigned long long to string.
// return the string lengh. if @1 is not allocated.
// return 0. the string length cannot include NULL
// terminal.
int ez_bytes_ull2string (bytes _buf, unsigned long long _val) {
	bytes ptr = _buf, tmp = _buf;
	int len = 0;
	if (! ptr) return 0;
	do {
		*ptr ++ = '0' + (_val % 10);
		_val /= 10;
	} while (_val);

	len = ptr - _buf;
	*ptr = '\0';
	ptr --;

	while (ptr > tmp) {
		*tmp ^= *ptr;
		*ptr ^= *tmp;
		*tmp ^= *ptr;
		ptr --;
		tmp ++;
	}
	return len;
}


// convert from long long to string.
// return the string lengh. if @1 is not allocated.
// return 0. the string length cannot include NULL
// terminal.
int ez_bytes_ll2string (bytes _buf, long long _val) {
	bytes ptr = _buf, tmp = _buf;
	long long val = _val;
	int len = 0;
	if (! ptr) return 0;
	if (val < 0) val = - val;

	do {
		*ptr ++ = '0' + (val % 10);
		val /= 10;
	} while (val);

	if (_val < 0) *ptr ++ = '-';
	len = ptr - _buf;
	*ptr = '\0';
	ptr --;

	while (ptr > tmp) {
		*tmp ^= *ptr;
		*ptr ^= *tmp;
		*tmp ^= *ptr;
		ptr --;
		tmp ++;
	}
	return len;
}

