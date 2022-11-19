 .include "p33fj32mc202.inc"
 .global _main ;cuerpo de nuestro programa
 
 _main:
    
    .byte 74;, 0112, 0b01001010, 0x4A, 0x4a, ?J?;All the same value
    .ascii "A stringRing the bell\7"; constant
    .float 3.1415926535897932384626433832795028841971;.693993751E-40
    nop
    nop
    ;instrucciones de movimiento
    mov #34,W4
    mov  W4,TRISB
    
    mov #30,W1
    mov W4,T1CON
    
    nop
  bucle:
    
    goto bucle

  .end
    