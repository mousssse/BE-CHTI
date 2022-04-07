	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
flagCligno dcd 0 ;init var flagCligno
	
; ===============================================================================================
	
	EXPORT flagCligno
	EXPORT timer_callback 	;pour que principal.c sache le trouver
	include DriverJeuLaser.inc 
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


;char FlagCligno;
;void timer_callback(void)
	;if (FlagCligno==1)
		;FlagCligno=0;
		;GPIOB_Set(1);
	;else
		;FlagCligno=1;
		;GPIOB_Clear(1);

timer_callback proc
	mov r0, #1				;1st arg of functions we will call, eg pin 1
	ldr r1, =flagCligno     ;r1 = &flagCligno
	ldr r2, [r1]	  		;r2 = flagCligno
	cmp r2, #0				;compare r2 and 0
	bne cligno1				;if flagCligno != 0 => cligno1
	
	;GPIOB_Set(1); here if no jump <=> if equal 0
	push {r1, lr}
	bl GPIOB_Set
	pop {r1, lr}
	;FlagCligno=1;
	mov r2, #1				;r2 = 1
	str r2, [r1]			;flagCligno = 1
	bx lr
	
	
cligno1	push {r1, lr}
		bl GPIOB_Clear
		pop {r1, lr}
		;FlagCligno=0;
		mov r2, #0				;r2 = 0
		str r2, [r1]			;flagCligno = 0
		bx lr
		
		
	endp

	END	