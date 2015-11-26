#include "ez_bytes.h"

int ez_bytes_index_byte (bytes _s, byte _b, int _slen) {
  int i = 0;
  for (; i < _slen; i ++) {
    if (_s [i] == _b)
      return i;
  }

  return -1;
}

int ez_bytes_equal_sep 
(bytes _s, bytes _sep, int _slen, int _seplen) {
  if (! _s || ! _sep || _slen != _seplen)
    return 0;
  -- _slen;

  for (; _slen >= 0; -- _slen) {
    if (_s [_slen] != _sep [_slen])
      return 0;
  }
  return 1;
}


int ez_bytes_index_sep 
(bytes _s, bytes _sep, int _slen, int _seplen) {
  char c;
  int i; // the index of _s
  bytes ptr = _s;
  if (! _slen || ! _seplen || 
      _slen < _seplen || ! _s || ! _sep)
    return -1;
  
  i = 0;

  for (; i < _slen; i ++) {
    int idx = ez_bytes_index_byte (ptr, _sep, _slen);
    if (idx < _slen - 1 || 
        (idx == _slen - 1 && _seplen == 1)) {
      if (ez_bytes_equal_sep (ptr, _sep, _slen, _seplen))
        return idx;
    }

  }

  // TODO
  
}



