;ORG		0000H
;MAIN:	MOV 	R0, 	#30H	;DATA BEGIN ADDRESS
		;MOV 	A,	 	#0A0H	;DATA
		;MOV 	R1,		#05H	;TOTAL NUMBER
		
		;;INITIALIZE DATA FROM 30H TO 30+5H
;LOOP1:	MOV 	@R0, 	A
		;INC		R0
		;INC 	A
		;DJNZ	R1, 	LOOP1
		
		;; INITIALIZE DATA FROM 40H TO 40+5H
		;MOV		R0, 	#40H
		;MOV		A, 		#0EAH
		;MOV		R1, 	#05H
		
;LOOP2:	MOV		@R0, 	A
		;INC 	R0
		;INC		A
		;DJNZ	R1, 	LOOP2
		
		;; ADD DATA FROM 30H AND 40H TO 30H WITH LOWER WORD IN 30H
		;;INIT
		;MOV		R0, 	#30H
		;MOV		R1,		#40H
		;MOV		R2, 	#05H
		;CLR 	C
		
;LOOP3:	MOV		A, 		@R0
		;ADDC	A,		@R1
		;MOV		@R0, 	A
		;INC		R0
		;INC		R1
		;DJNZ	R2,		LOOP3
		
		;SJMP	$
		
		
		;ORG		0000H
;MAIN:	MOV		30H, 	#96H
		;MOV		31H,	#39H
		;MOV		A, 		30H
		;ADD		A, 		31H
		;DA		A
		;MOV		30H,	A
		;SJMP	$
		
		;ORG		0000H
;MAIN:	
		;MOV		DPTR, 		#2000H
		;MOV		A, 			#2FH
		;MOVX	@DPTR,		A
		;MOVX	A, 			@DPTR
		;MOV		B, 			#0AH
		;DIV		AB
		;SWAP	A
		;ANL		A, 			#0F0H
		;ADD		A, 			B
		;SJMP	$
		
		;ORG			0000H
		;MOV 		A,			#15H
		;MOV			R0, 		A
		;CLR			C
		;RLC			A
		;CLR			C
		;RLC			A
		;XCH			A, 			R0
		;CLR			C
		;RLC			A
		;ADD			A, 			R0
		;SJMP		$
		
		;ORG		0000H
		;MOV		DPTR, 		#DTABLE
		;MOV		R0, 		#30H	;ADDRESS TO PUT RESULT
		;MOV		R1, 		#00H	;COUNT
		;CLR		C
		;CLR		00H
;LOOP:	MOV		C, 			00H
		;MOV		A,			R1
		;MOVC	A, 			@A+DPTR
		;RLC		A
		;MOV		@R0,		A
		;INC		R0
		;INC		R1
		;MOV		00H, 		C		;SAVE C
		;CJNE	R1, 		#05H, 	LOOP
		;SJMP	$
		
;ORG		1000H
;DTABLE: DB	55H, 55H, 55H, 0AAH, 0AAH ;LOW TO HIGH


		;ORG			0000H
		;MOV			R0, 		#00H
		;MOV			R1, 		#00H
		;MOV			R2, 		#00H
		;MOV			A, 			#30H
		;MOV			30H,		#30H
		;CJNE		A, 			30H, 	NEQUAL	
;EQUAL:	MOV			R0, 		#01H
		;AJMP		EEE
;NEQUAL:	JC			LOWER
		;AJMP		GREATER
;LOWER:	MOV			R1, 		#02H
		;SJMP		EEE
;GREATER:MOV			R2, 		#03H
;EEE:	SJMP		$

		;ORG			0000H
		;DAT			EQU			30H
		;MOV			R0, 		#DAT	;ADDRESS
		;MOV			R1, 		#05H	;COUNTER
		;MOV			A, 			#08H
		
;LOOP:	MOV			@R0, 		A
		;INC			A
		;INC			R0
		;DJNZ		R1, 		LOOP
		
		;SUM			EQU			40H
		;MOV			SUM, 		#00H
		;MOV			R0, 		#DAT
		;MOV			R1, 		#05H
		;CLR			A
		
;LOOP2:	MOV			A, 			@R0
		;ADD			A, 			SUM
		;MOV			SUM, 		A
		;INC			R0
		;DJNZ		R1, 		LOOP2
		
		;SJMP		$
		
		;ORG			0000H
		;CLR		21H		;X
		;CLR			20H		;Y
		;MOV			C, 		21H
		;ANL			C, 		/20H
		;MOV			22H, 	C
		;MOV			C, 		20H
		;ANL			C, 		/21H
		;ORL			C, 		22H
		;MOV			22H, 	C
		;SJMP		$
		
		;ORG			0000H
		;MOV			40H, 		#0AH	;TOTAL NUMBER
		;CLR			A
		;MOV			DPTR, 		#2000H
		;MOV			R2, 		40H		;CONTER
		
;LOOP1:	MOVX		@DPTR,		A
		;INC			DPTR
		;INC			A
		;DJNZ		R2,			LOOP1
		
		;MOV			30H, 		#00H		;SL
		;MOV			31H, 		#20H		;SH
		;MOV			32H, 		#00H		;DL
		;MOV			33H, 		#40H		;DH
		;MOV			R0, 		40H
		
		;;GET DATA FROM 2000+R0
;LOOP2:	MOV			DPL, 		30H
		;MOV			DPH,		31H
		;MOVX		A, 			@DPTR
		;INC			DPTR
		;MOV			30H, 		DPL
		;MOV			31H, 		DPH
		;;SAVE DATA TO 3000H
		;MOV			DPL, 		32H
		;MOV			DPH, 		33H
		;MOVX		@DPTR, 		A
		;INC			DPTR
		;MOV			32H, 		DPL
		;MOV			33H, 		DPH
		;DJNZ		R0, 		LOOP2
		
		
		;SJMP		$
		;ORG			0000H
		;MOV			50H, 		#3FH
		;MOV			51H, 		#3FH
		
		;LCALL		JUDGE
		;AJMP		$
			
;JUDGE:	MOV			A, 			50H
		;CJNE		A, 			51H, 		NEQUAL
		;SJMP		EQUAL
;NEQUAL:	JC			LESS
		;SJMP		GREATER
		
;EQUAL:	MOV			60H, 		A
		;SJMP		NEXT
;LESS:	MOV			60H, 		A
		;SJMP		NEXT
;GREATER:MOV			60H, 		51H
;NEXT:
		;RET
		;ORG			0000H
		;MOV			43H, 		#22H
		;MOV			42H, 		#54H
		;MOV			41H, 		#97H
		;MOV			40H,		#03H
		;MOV			53H,		#14H
		;MOV			52H, 		#34H
		;MOV			51H, 		#35H
		;MOV			50H, 		#08H
		
		;MOV			R0,			#40H	;ADDER1 ADDRESS
		;MOV			R1, 		#50H	;ADDER2 ADDRESS
		;MOV			R2, 		#04H	;TOTAL NUMBER
		
		;LCALL		CAUCULATE_SUM
		;SJMP		$

;CAUCULATE_SUM:
		;CLR			C

;LOOP:	MOV			A, 			@R0
		;ADDC		A, 			@R1
		;;DA			A
		;MOV			@R0, 		A
		;INC			R0
		;INC			R1
		;DJNZ		R2, 		LOOP
		;RET
		
		;ORG			0000H
		;MOV			7CH, 		#25H
		;MOV			R0, 		#7CH
		;CLR			A
		;XCHD		A, 			@R0
		;MOV			R5, 		A
		;MOV			A, 			@R0
		;SWAP		A
		;MOV			R6, 		A
		;SJMP		$
		;ORG			0000H
		;MOV			R0, 		#50H
		;MOV			DPTR,		#2000H
		;MOV			A, 			#20H
		
;LOOP1:	MOVX		@DPTR,		A
		;INC			A
		;INC			DPTR
		;DJNZ		R0, 		LOOP1
		
		;MOV			R0, 		#50H
		;MOV			R1, 		#20H
		;MOV			DPTR, 		#2000H
		;;BEGIN TO MOVE
;LOOP2:	MOVX		A, 			@DPTR
		;MOV			@R1, 		A
		;INC			DPTR
		;INC			R1
		;DJNZ		R0,			LOOP2
		
		;SJMP		$
		
		;ORG			0000H
		;MOV			A, 			#0C9H
		;MOV			b, 			#8DH
		;SETB		C
		;SUBB		A, 			B
		;SJMP		$
		
		;ORG			0000H
		;MOV			A, 		#83H
		;MOV			R0, 	#17H
		;MOV			17H, 	#31H
		
		;ANL			A, 		#17H
		;ORL			17H, 	A
		;XRL			A, 		@R0
		;CPL			A
		;SJMP		$
		
		;ORG			0000H
		;MOV			R2, 		#20
		;MOV			R0, 		#30H
		;MOV			A, 			#0F2H
		;;INITIAL
;LOOP1:	MOV			@R0, 		A
		;INC			A
		;INC			R0
		;DJNZ		R2, 		LOOP1
		
		;; BEGIN ALGORITHM
		;;INITIAL
		;MOV			R2, 		#20
		;MOV			R0, 		#30H	;ORIGINE ADDRESS
		;MOV			R1, 		#51H	;DESTINATE ADDRESS
		;MOV			R3,			#71H	;NEGETIVE ADDRESS
		;MOV			50H, 		#00H	;POSTIVE COUNTER
		;MOV			70H, 		#00H	;NEGETIVE COUNTER
;LOOP2:	MOV			A, 			@R0
		;JB			ACC.7,		NEGETIVE
		;MOV			@R1, 		A
		;INC			R1
		;INC			50H
		;INC			R0
		;SJMP		NEXT
;NEGETIVE:
		;MOV			08H, 		R1		;SAVE
		;MOV			09H, 		R3
		;MOV			R1, 		09H
		;MOV			@R1, 		A		
		;MOV			R1, 		08H		;RELOAD
		;INC			R3
		;INC			70H
		;INC			R0

;NEXT:	DJNZ		R2, 		LOOP2
		;SJMP		$
		
		;ORG			0000H
		;;INITIAL
		;MOV			R2, 		#10
		;MOV			R0, 		#40H
		;MOV			A, 			#70H
;LOOP1:	MOV			@R0,		A
		;DEC			A
		;INC			R0
		;DJNZ		R2, 		LOOP1
		
		;;BEGIN
		;MOV			R2, 		#10
		;MOV			R0, 		#40H		;ADDRESS
		;MOV			30H, 		#0FFH
;LOOP2:	MOV			A, 			@R0
		;CLR			C
		;SUBB		A, 			30H
		;JC			NEW_MIN
		;LJMP		SKIP
;NEW_MIN:MOV			30H, 		@R0
;SKIP:	INC			R0
		;DJNZ		R2, 		LOOP2
		;SJMP		$
		
		;ORG			0000H
		;;INITIAL
		;MOV			40H, 		#03H
		;MOV			41H, 		#50H
		;MOV			A, 			40H
		;ADD			A, 			41H
		;MOV			42H,		A
		;SJMP		$
		
		;ORG			0000H
		;MOV			R2, 		#04H
		;BLOCK1		EQU			1000H
		;BLOCK2		EQU			30H
		;MOV			DPTR, 		#BLOCK1
		
		;;INITIAL
		;MOV			A,			#01H
;LOOP1:	MOVX		@DPTR, 		A
		;INC			DPTR
		;INC			A
		;DJNZ		R2, 		LOOP1
		
		;;BEGIN
		;MOV			R2,			#04H
		;MOV			DPTR, 		#BLOCK1		;EXTERN DATA ADDRESS
		;MOV			R0, 		#BLOCK2		;INTERNAL DATA ADDRESS
;LOOP2:	MOVX		A, 			@DPTR
		;MOV			@R0, 		A
		;INC			R0
		;INC			DPTR
		;DJNZ		R2, 		LOOP2
		;SJMP		$
		
		;ORG			0000H
		;MOV			A, 		#3DH
		;SETB		C
		;MOV			R0,		#39H
		;MOV			P1, 	#0C5H
		;MOV			@R0,	P1
		;MOV			P2, 	A
		;ADDC		A, 		@R0
		;MOV			@R0, 	A
		;ANL			A, 		#07H
		;SETB		ACC.7
		;SJMP		$
		
		;ORG			0000H
		;MOV			30H, 		#59H
		;MOV			31H, 		#82H
		;MOV			40H, 		#21H
		
		;LCALL		ADD_BCD
		;SJMP		$
			
;ADD_BCD:
		;CLR			C
		;MOV			A, 			30H
		;ADDC		A,			40H
		;DA			A
		;MOV			50H,		A
		;MOV			A, 			31H
		;ADDC		A, 			00H
		;DA			A
		;MOV			51H, 		A
		;RET
		
		;ORG			0000H
		;MOV			C, 		P1.0
		;ANL			C,		/P1.4
		;MOV			00H, 	C
		
		;MOV			C, 		P1.0
		;ANL			C, 		TF1
		;ORL			C, 		00H
		;MOV			00H, 	C
		
		;MOV			C, 		22H.0
		;ANL			C, 		/22H.3
		;ANL			C,		IE1
		
		;ORL			C, 		00H
		;MOV			P1.5, 	C
		;SJMP		$
		;ORG			0000H
		;LJMP		MAIN
		;ORG			0023H
		;LJMP		S_HANDEL
		
;MAIN:	MOV			TMOD, 		#20H
		;MOV			TH1, 		#0F3H
		;MOV			TL1, 		#0F3H
		;SETB		TR1
		;CLR			ET1
		
		;SETB		EA
		;SETB		ES
		;MOV			PCON, 		#00H
		;MOV			SCON,		#40H
		;CLR			A
		;MOV			SBUF,		A
		;SJMP		$
		
;S_HANDEL:	
		;INC			A
		;CLR			TI
		;MOV			SBUF,		A
		;RETI
		
		ORG			0000H
		MOV			A, 			#05
		ADD			A, 			#02
		MOVC		A, 			@A+PC
		SJMP		NEXT
		DB	00, 01, 04, 09, 16, 25
NEXT:	SJMP		$
		
			