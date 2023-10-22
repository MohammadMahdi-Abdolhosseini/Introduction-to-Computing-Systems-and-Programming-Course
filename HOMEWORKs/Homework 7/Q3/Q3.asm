	.ORIG	x3000
	LD	R1,X		; R1 = X
	LD	R2,Y		; R2 = Y
	NOT	R1,R1		; R1 = NOT(X)
	AND	R3,R1,R2	; R3 = NOT(X) AND Y
	NOT	R1,R1		; R1 = X
	NOT	R2,R2		; R2 = NOT(Y)
	AND	R4,R1,R2	; R4 = X AND NOT(Y)
	NOT	R2,R2		; R2 = Y
	NOT	R3,R3		; R3 = NOT[NOT(X) AND Y] = X OR NOT(Y)
	NOT	R4,R4		; R4 = NOT[X AND NOT(Y)] = NOT(X) OR Y
	AND	R3,R3,R4	; R3 = [X OR NOT(Y)] AND [NOT(X) OR Y]
	NOT	R3,R3		; R3 = NOT([X OR NOT(Y)] AND [NOT(X) OR Y])
				; R3 = [NOT(X) AND Y] OR [X AND NOT(Y)] = X XOR Y
				; R3 = X ^ Y
				; R3 = R1 XOR R2 = R1 ^ R2
	AND	R4,R4,#0	; clear R4
	HALT
X	.FILL	x25		; X = 37 (DEC)
Y	.FILL	x3A		; Y = 58 (DEC)
				; X XOR Y : 
				;		0010 0101
				;	XOR 	0011 1010
				;	-----------------
				;		0001 1111  = 31 (DEC)
	.END