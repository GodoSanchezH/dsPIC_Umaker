;    File   lowpassexample.s
                .equ lowpassexampleNumTaps, 22
; Allocate and initialize filter taps
;               .section .xdata                 ;<-Syntax supported in MPLAB C30                              ;v1.20 and before
                .section .xdata, data, xmemory  ;<-Syntax supported in MPLAB C30                                               ;v1.30 and later
                .align 256

lowpassexampleTaps:
.hword      0x0043,0x007d,0x010d,0x0218,0x03aa,0x05b0,0x07f8
.hword	    0x0a3c,0x0c29,0x0d74,0x0de9,0x0d74,0x0c29,0x0a3c
.hword	    0x07f8,0x05b0,0x03aa,0x0218,0x010d,0x007d,0x0043


    


   
    
    
; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

;               .section .ybss,  "b"            ;<-Syntax supported in MPLAB C30
                                                ;v1.20 and before
                .section .ydata, data, ymemory  ;<-Syntax supported in MPLAB C30
                                                ;v1.30 and later
                .align 256

lowpassexampleDelay:
                .space lowpassexampleNumTaps*2

; ..............................................................................
; Allocate and intialize filter structure

                .section .data
                .global _lowpassexampleFilter

_lowpassexampleFilter:
.hword lowpassexampleNumTaps
.hword lowpassexampleTaps
.hword lowpassexampleTaps+lowpassexampleNumTaps*2-1
.hword 0xff00
.hword lowpassexampleDelay
.hword lowpassexampleDelay+lowpassexampleNumTaps*2-1
.hword lowpassexampleDelay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;               .extern _FIRFilterInit
;               .extern _BlockFIRFilter
;               .extern _lowpassexampleFilter
;
;               .section        .bss
;
;        The input and output buffers can be made any desired size
;          the value 40 is just an example - however, one must ensure
;          that the output buffer is at least as long as the number of samples
;          to be filtered (parameter 4)
;input:         .space  40
;output:        .space  40
;               .text
;
;
;  This code can be copied and pasted as needed into a program
;
;
; Set up pointers to access input samples, filter taps, delay line and
; output samples.
;               mov     #_lowpassexampleFilter, W0      ; Initalize W0 to filter structure
;               call    _FIRFilterInit  ; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _BlockFIRFilter
;               mov     #_lowpassexampleFilter, W0      ; Initalize W0 to filter structure
;               mov     #input, W1      ; Initalize W1 to input buffer
;               mov     #output, W2     ; Initalize W2 to output buffer
;               mov     #20, W3 ; Initialize W3 with number of required output samples
;               call    _BlockFIRFilter ; call as many times as needed
