from secret import flag
from hashlib import md5

if 64 - 64: i11iIiiIii
def OO0o ( arg ) :
 arg = bytearray ( arg , 'ascii' )
 for Oo0Ooo in range ( 0 , len ( arg ) , 4 ) :
  O0O0OO0O0O0 = arg [ Oo0Ooo ]
  iiiii = arg [ Oo0Ooo + 1 ]
  ooo0OO = arg [ Oo0Ooo + 2 ]
  II1 = arg [ Oo0Ooo + 3 ]
  arg [ Oo0Ooo + 2 ] = II1
  arg [ Oo0Ooo + 1 ] = O0O0OO0O0O0
  arg [ Oo0Ooo + 3 ] = iiiii
  arg [ Oo0Ooo ] = ooo0OO
 return arg . decode ( 'ascii' )
 if 64 - 64: Oooo % OOO0O / II1Ii / Ooo
flag += b"0" * ( len ( flag ) % 4 )
if 63 - 63: iI11i11IiIiII + oo00oOOo * Oooo000o % OOo . OOO
for Oo0Ooo in range ( 0 , len ( flag ) , 4 ) :
 print ( OO0o ( md5 ( bytes ( flag [ Oo0Ooo : Oo0Ooo + 4 ] ) ) . hexdigest ( ) ) )
 if 27 - 27: Iii1IIIiiI + iI - Oo / iII11iiIII111 % iiiIIii1I1Ii . O00oOoOoO0o0O
# dd678faae9ac167bc83abf78e5cb2f3f0688d3a3
