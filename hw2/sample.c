/* 
 * Two Sample bit puzzles.
 * 
 */

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 1
 */
int negate(int x) {
  return ~x+1;
}   

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int m8 = 0xAA;
  int m16 = m8 | m8 << 8;
  int m32 = m16 | m16 <<16;
  int fillx = x | m32;
  return !~fillx;
}

