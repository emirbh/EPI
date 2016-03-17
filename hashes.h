#ifndef __HASHES_H__
#define __HASHES_H__

/*******************************************************************************
 *  getStringKey()
 */
int getStringKey(const string &str, const int modulus) {
  const int MULT = 997;
  int key = 0;
  for(const char &ch : str) {
    key = (key * MULT + ch) % modulus;
  }
  return key;
}

#endif /* __HASHES_H__ */
