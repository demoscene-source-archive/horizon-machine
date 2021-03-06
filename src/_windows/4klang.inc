%macro export_func 1
   global _%1
   _%1:
%endmacro
%define USE_SECTIONS
%define SAMPLE_RATE	44100
%define MAX_INSTRUMENTS	8
%define MAX_VOICES 2
%define HLD 1
%define BPM 32.000000
%define MAX_PATTERNS 20
%define PATTERN_SIZE_SHIFT 2
%define PATTERN_SIZE (1 << PATTERN_SIZE_SHIFT)
%define	MAX_TICKS (MAX_PATTERNS*PATTERN_SIZE)
%define	SAMPLES_PER_TICK 82688
%define DEF_LFO_NORMALIZE 0.0000120937
%define	MAX_SAMPLES	(SAMPLES_PER_TICK*MAX_TICKS)
;%define 	GO4K_USE_16BIT_OUTPUT
;%define 	GO4K_USE_GROOVE_PATTERN
;%define 	GO4K_USE_ENVELOPE_RECORDINGS
;%define 	GO4K_USE_NOTE_RECORDINGS
%define 	GO4K_CLIP_OUTPUT
%define 	GO4K_USE_DST
%define 	GO4K_USE_DLL
%define 	GO4K_USE_PAN
%define 	GO4K_USE_GLOBAL_DLL
%define 	GO4K_USE_FSTG
%define 	GO4K_USE_FLD
;%define 	GO4K_USE_ENV_CHECK
;%define 	GO4K_USE_VCO_CHECK
%define 	GO4K_USE_VCO_MOD_TM
;%define 	GO4K_USE_VCO_MOD_DM
;%define 	GO4K_USE_VCF_CHECK
%define 	GO4K_USE_VCF_MOD_FM
%define 	GO4K_USE_VCF_HIGH
;%define 	GO4K_USE_VCF_BAND
;%define 	GO4K_USE_VCF_PEAK
;%define 	GO4K_USE_DST_CHECK
%define 	GO4K_USE_DST_SH
%define 	GO4K_USE_DST_MOD_SH
%define		GO4K_USE_DLL_NOTE_SYNC
;%define		GO4K_USE_DLL_CHORUS_CLAMP
%define 	GO4K_USE_DLL_DAMP
%define 	GO4K_USE_DLL_DC_FILTER
;%define 	GO4K_USE_FSTG_CHECK
%define 	GO4K_USE_PAN_MOD
%define 	GO4K_USE_OUT_MOD_AM
%define 	GO4K_USE_OUT_MOD_GM
%define		GO4K_USE_WAVESHAPER_CLIP
%define 	GO4K_USE_FLD_MOD_VM
%define 	GO4K_USE_DLL_MOD
%define 	GO4K_USE_DLL_MOD_DM	
%define	MAX_DELAY			65536
%define MAX_UNITS			32
%define	MAX_UNIT_SLOTS	    8
%define GO4K_BEGIN_CMDDEF(def_name)
%define GO4K_END_CMDDEF db 0
%define GO4K_BEGIN_PARAMDEF(def_name)
%define GO4K_END_PARAMDEF
GO4K_ENV_ID		equ		1
%macro	GO4K_ENV 5
	db	%1
	db	%2
	db	%3
	db	%4
	db	%5
%endmacro
%define	ATTAC(val)		val	
%define	DECAY(val)		val	
%define	SUSTAIN(val)	val	
%define	RELEASE(val)	val	
%define	GAIN(val)		val	
struc	go4kENV_val
	.attac		resd	1
	.decay		resd	1
	.sustain	resd	1
	.release	resd	1
	.gain		resd	1
	.size
endstruc
struc	go4kENV_wrk
	.state		resd	1
	.level		resd	1
	.gm			resd	1
	.am			resd	1
	.dm			resd	1
	.sm			resd	1
	.rm			resd	1
	.size
endstruc
%define ENV_STATE_ATTAC		0
%define ENV_STATE_DECAY		1
%define ENV_STATE_SUSTAIN	2
%define ENV_STATE_RELEASE	3
%define ENV_STATE_OFF		4
GO4K_VCO_ID		equ		2
%macro	GO4K_VCO 8
	db	%1
	db	%2
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	db	%3
%endif	
%ifdef GO4K_USE_VCO_GATE	
	db	%4
%endif	
	db	%5
%ifdef GO4K_USE_VCO_SHAPE	
	db	%6
%endif	
	db	%7
	db	%8
%endmacro
%define	TRANSPOSE(val)	val	
%define	DETUNE(val)		val	
%define	PHASE(val)		val	
%define	GATES(val)		val	
%define	COLOR(val)		val	
%define	SHAPE(val)		val 
%define	FLAGS(val)		val	
%define SINE		0x01
%define TRISAW		0x02
%define PULSE		0x04
%define NOISE		0x08
%define LFO			0x10
%define GATE		0x20
%define	VCO_STEREO	0x40
struc	go4kVCO_val
	.transpose	resd	1
	.detune		resd	1
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	.phaseofs	resd	1
%endif	
%ifdef GO4K_USE_VCO_GATE	
	.gate		resd	1
%endif	
	.color		resd	1
%ifdef GO4K_USE_VCO_SHAPE	
	.shape		resd	1
%endif	
	.gain		resd	1
	.flags		resd	1	
	.size
endstruc
struc	go4kVCO_wrk
	.phase		resd	1
	.tm			resd	1
	.dm			resd	1
	.fm			resd	1
	.pm			resd	1
	.cm			resd	1
	.sm			resd	1
	.gm			resd	1
	.phase2		resd	1
	.size
endstruc
GO4K_VCF_ID		equ		3
%macro	GO4K_VCF 3
	db	%1
	db	%2
	db	%3
%endmacro
%define LOWPASS		0x0
%define HIGHPASS	0x1
%define BANDPASS	0x4
%define	BANDSTOP	0x3
%define ALLPASS		0x7
%define	PEAK		0x8
%define STEREO		0x10
%define	FREQUENCY(val)	val
%define	RESONANCE(val)	val
%define	VCFTYPE(val)	val
struc	go4kVCF_val
	.freq		resd	1
	.res		resd	1
	.type		resd	1
	.size
endstruc
struc	go4kVCF_wrk
	.low		resd	1
	.high		resd	1
	.band		resd	1
	.freq		resd	1
	.fm			resd	1
	.rm			resd	1
	.low2		resd	1
	.high2		resd	1
	.band2		resd	1
	.size
endstruc
GO4K_DST_ID		equ		4
%macro	GO4K_DST 3
	db	%1
%ifdef GO4K_USE_DST_SH
	db	%2
%ifdef GO4K_USE_DST_STEREO
	db	%3
%endif
%else
%ifdef GO4K_USE_DST_STEREO
	db	%3
%endif
%endif
%endmacro
%define	DRIVE(val)		val
%define	SNHFREQ(val)	val
%define	FLAGS(val)		val
struc	go4kDST_val
	.drive		resd	1
%ifdef GO4K_USE_DST_SH	
	.snhfreq	resd	1
%endif	
	.flags		resd	1
	.size
endstruc
struc	go4kDST_wrk
	.out		resd	1
	.snhphase	resd	1
	.dm			resd	1
	.sm			resd	1
	.out2		resd	1
	.size
endstruc
GO4K_DLL_ID		equ		5
%macro	GO4K_DLL 8
	db	%1
	db	%2
	db	%3
%ifdef GO4K_USE_DLL_DAMP	
	db	%4
%endif		
%ifdef GO4K_USE_DLL_CHORUS	
	db	%5
	db	%6
%endif
	db	%7
	db	%8
%endmacro
%define PREGAIN(val)	val
%define	DRY(val)		val
%define	FEEDBACK(val)	val
%define	DEPTH(val)		val
%define DAMP(val)		val
%define	DELAY(val)		val
%define	COUNT(val)		val
struc	go4kDLL_val
	.pregain	resd	1
	.dry		resd	1
	.feedback	resd	1
%ifdef GO4K_USE_DLL_DAMP	
	.damp		resd	1	
%endif
%ifdef GO4K_USE_DLL_CHORUS
	.freq		resd	1
	.depth
%endif
	.delay		resd	1
	.count		resd	1
	.size
endstruc
struc	go4kDLL_wrk
	.index		resd	1
	.store		resd	1
	.dcin		resd	1
	.dcout		resd	1
%ifdef GO4K_USE_DLL_CHORUS
	.phase		resd	1
%endif
	.buffer		resd	MAX_DELAY
	.size
endstruc
struc	go4kDLL_wrk2
 .pm			resd	1
 .fm			resd	1
 .im			resd	1
 .dm			resd	1
 .sm			resd	1
 .am			resd	1
 .size
endstruc
GO4K_FOP_ID	equ			6
%macro	GO4K_FOP 1
	db	%1
%endmacro
%define	OP(val)			val
%define FOP_ADDP		0x1
%define FOP_MULP		0x2
%define FOP_PUSH		0x3
%define FOP_XCH			0x4
%define FOP_ADDP2		0x5
%define FOP_LOADNOTE	0x6
struc	go4kFOP_val
	.flags		resd	1
	.size
endstruc
struc	go4kFOP_wrk
	.size
endstruc
GO4K_FST_ID		equ		7
%macro	GO4K_FST 2
	db	%1
	dw	%2
%endmacro
%define	AMOUNT(val)		val
%define	DEST(val)		val
%define	FST_SET			0x0000
%define	FST_ADD			0x4000
%define	FST_POP			0x8000
struc	go4kFST_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFST_wrk
	.size
endstruc
GO4K_PAN_ID		equ		8
%macro	GO4K_PAN 1
%ifdef GO4K_USE_PAN
	db	%1
%endif
%endmacro
%define	PANNING(val)	val
struc	go4kPAN_val
%ifdef GO4K_USE_PAN
	.panning	resd	1
%endif
	.size
endstruc
struc	go4kPAN_wrk
	.pm			resd	1
	.size
endstruc
GO4K_OUT_ID		equ		9
%macro	GO4K_OUT 2
	db	%1
%ifdef GO4K_USE_GLOBAL_DLL	
	db	%2
%endif	
%endmacro
%define	AUXSEND(val)	val
struc	go4kOUT_val
	.gain		resd	1
%ifdef GO4K_USE_GLOBAL_DLL	
	.auxsend	resd	1
%endif
	.size
endstruc
struc	go4kOUT_wrk
	.am			resd	1
	.gm			resd	1
	.size
endstruc
GO4K_ACC_ID		equ		10
%macro	GO4K_ACC 1
	db	%1
%endmacro
%define OUTPUT			0
%define	AUX				8
%define ACCTYPE(val)	val
struc	go4kACC_val
	.acctype	resd	1
	.size
endstruc
struc	go4kACC_wrk
	.size
endstruc
%ifdef GO4K_USE_FLD
GO4K_FLD_ID	equ		11
%macro	GO4K_FLD 1
	db	%1
%endmacro
%define	VALUE(val)	val
struc	go4kFLD_val
	.value		resd	1
	.size
endstruc
struc	go4kFLD_wrk
	.vm			resd	1
	.size
endstruc
%endif
%ifdef GO4K_USE_FSTG
GO4K_FSTG_ID	equ		12
%macro	GO4K_FSTG 2
	db	%1
	dw	%2
%endmacro
struc	go4kFSTG_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFSTG_wrk
	.size
endstruc
%endif
struc	go4k_instrument
	.release	resd	1
	.note		resd	1
	.workspace	resd	MAX_UNITS*MAX_UNIT_SLOTS
	.dlloutl	resd	1
	.dlloutr	resd	1
	.outl		resd	1
	.outr		resd	1
	.size
endstruc
struc	go4k_synth
	.instruments	resb	go4k_instrument.size * MAX_INSTRUMENTS * MAX_VOICES
	.global			resb	go4k_instrument.size * MAX_VOICES
	.size
endstruc
%ifdef USE_SECTIONS
section .g4kmuc1 data align=1
%else
section .data align=1
%endif
go4k_patterns
	db	0, 0, 0, 0, 
	db	69, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, HLD, 
	db	72, HLD, HLD, HLD, 
	db	70, HLD, HLD, HLD, 
	db	HLD, HLD, HLD, 0, 
	db	74, HLD, HLD, HLD, 
	db	79, HLD, HLD, HLD, 
	db	76, HLD, HLD, HLD, 
	db	74, HLD, HLD, 0, 
	db	77, HLD, HLD, HLD, 
	db	81, HLD, HLD, HLD, 
	db	82, HLD, HLD, HLD, 
	db	38, HLD, HLD, HLD, 
	db	41, HLD, HLD, HLD, 
	db	52, HLD, HLD, HLD, 
	db	55, HLD, HLD, HLD, 
	db	50, HLD, HLD, HLD, 
	db	53, HLD, HLD, HLD, 
	db	64, HLD, HLD, HLD, 
	db	67, HLD, HLD, HLD, 
	db	46, HLD, HLD, HLD, 
	db	62, HLD, HLD, HLD, 
	db	84, HLD, HLD, HLD, 
	db	86, HLD, HLD, HLD, 
	db	26, HLD, HLD, HLD, 
	db	41, HLD, HLD, 89, 
	db	40, HLD, HLD, HLD, 
	db	43, HLD, HLD, 89, 
	db	45, HLD, HLD, 82, 
	db	34, HLD, HLD, HLD, 
	db	38, HLD, 93, HLD, 
	db	57, HLD, HLD, HLD, 
	db	58, HLD, HLD, HLD, 
	db	0, 0, 87, HLD, 
	db	46, HLD, 0, 0, 
go4k_patterns_end
%ifdef USE_SECTIONS
section .g4kmuc2 data align=1
%else
section .data
%endif
go4k_pattern_lists
Instrument0List		db	0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 3, 4, 1, 5, 6, 2, 2, 2, 0, 0, 
Instrument1List		db	0, 0, 6, 3, 7, 6, 2, 3, 7, 6, 7, 6, 8, 9, 7, 2, 2, 2, 0, 0, 
Instrument2List		db	0, 0, 10, 2, 10, 2, 2, 2, 10, 2, 10, 2, 10, 5, 11, 12, 11, 2, 0, 0, 
Instrument3List		db	0, 0, 13, 14, 15, 16, 17, 18, 19, 16, 20, 21, 22, 5, 23, 24, 23, 2, 0, 0, 
Instrument4List		db	25, 13, 2, 0, 0, 0, 13, 26, 27, 28, 29, 30, 13, 13, 17, 2, 31, 13, 0, 0, 
Instrument5List		db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 33, 22, 17, 2, 2, 22, 2, 0, 0, 
Instrument6List		db	0, 0, 0, 0, 0, 0, 34, 0, 0, 34, 0, 35, 34, 0, 0, 0, 10, 0, 0, 0, 
Instrument7List		db	0, 0, 0, 0, 0, 0, 17, 2, 2, 2, 22, 2, 2, 5, 0, 0, 6, 2, 2, 0, 
go4k_pattern_lists_end
%ifdef USE_SECTIONS
section .g4kmuc3 data align=1
%else
section .data
%endif
go4k_synth_instructions
GO4K_BEGIN_CMDDEF(Instrument0)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_DLL_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument1)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_DLL_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument2)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_DLL_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument3)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_DLL_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument4)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_DST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_FST_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument5)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_DST_ID
	db GO4K_DLL_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_DST_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
	db GO4K_ENV_ID
	db GO4K_FST_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument6)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FLD_ID
	db GO4K_FOP_ID
	db GO4K_DST_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_FST_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
	db GO4K_ENV_ID
	db GO4K_FST_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument7)
	db GO4K_ENV_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_VCF_ID
	db GO4K_DST_ID
	db GO4K_FOP_ID
	db GO4K_FST_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FST_ID
	db GO4K_FSTG_ID
	db GO4K_FSTG_ID
	db GO4K_FSTG_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Global)
	db GO4K_ACC_ID
	db GO4K_VCF_ID
	db GO4K_DLL_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_DLL_ID
	db GO4K_DLL_ID
	db GO4K_ACC_ID
	db GO4K_FOP_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
go4k_synth_instructions_end
%ifdef USE_SECTIONS
section .g4kmuc4 data align=1
%else
section .data
%endif
go4k_synth_parameter_values
GO4K_BEGIN_PARAMDEF(Instrument0)
	GO4K_ENV	ATTAC(92),DECAY(0),SUSTAIN(128),RELEASE(92),GAIN(128)
	GO4K_FST	AMOUNT(128),DEST(13*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_FST	AMOUNT(96),DEST(13*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_FST	AMOUNT(48),DEST(7*MAX_UNIT_SLOTS+3+FST_SET+FST_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(52),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(32),DEST(10*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(128),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCO	TRANSPOSE(64),DETUNE(56),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(72),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_PAN	PANNING(32)
	GO4K_OUT	GAIN(0), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument1)
	GO4K_ENV	ATTAC(92),DECAY(0),SUSTAIN(128),RELEASE(92),GAIN(128)
	GO4K_FST	AMOUNT(128),DEST(13*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_FST	AMOUNT(96),DEST(13*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_FST	AMOUNT(48),DEST(7*MAX_UNIT_SLOTS+3+FST_SET+FST_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(52),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(32),DEST(10*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(122),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCO	TRANSPOSE(64),DETUNE(56),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(72),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_PAN	PANNING(96)
	GO4K_OUT	GAIN(0), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument2)
	GO4K_ENV	ATTAC(92),DECAY(0),SUSTAIN(128),RELEASE(92),GAIN(128)
	GO4K_FST	AMOUNT(128),DEST(13*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_FST	AMOUNT(96),DEST(13*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_FST	AMOUNT(48),DEST(7*MAX_UNIT_SLOTS+3+FST_SET+FST_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(52),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(32),DEST(10*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(118),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCO	TRANSPOSE(64),DETUNE(56),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(72),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_PAN	PANNING(48)
	GO4K_OUT	GAIN(0), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument3)
	GO4K_ENV	ATTAC(92),DECAY(0),SUSTAIN(128),RELEASE(92),GAIN(128)
	GO4K_FST	AMOUNT(128),DEST(14*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_FST	AMOUNT(96),DEST(14*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_FST	AMOUNT(48),DEST(7*MAX_UNIT_SLOTS+3+FST_SET+FST_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(52),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(32),DEST(10*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(128),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCO	TRANSPOSE(76),DETUNE(56),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(72),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_VCF	FREQUENCY(64),RESONANCE(64),VCFTYPE(LOWPASS)
	GO4K_PAN	PANNING(80)
	GO4K_OUT	GAIN(0), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument4)
	GO4K_ENV	ATTAC(70),DECAY(0),SUSTAIN(128),RELEASE(88),GAIN(128)
	GO4K_FST	AMOUNT(128),DEST(14*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_FST	AMOUNT(43),DEST(14*MAX_UNIT_SLOTS+0+FST_SET+FST_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(80),FLAGS(NOISE)
	GO4K_VCF	FREQUENCY(45),RESONANCE(12),VCFTYPE(LOWPASS)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(128),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_DST	DRIVE(24), SNHFREQ(32), FLAGS(0)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_VCF	FREQUENCY(8),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(75),DEST(5*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(0), AUXSEND(0)
	GO4K_ENV	ATTAC(86),DECAY(86),SUSTAIN(0),RELEASE(90),GAIN(128)
	GO4K_FST	AMOUNT(31),DEST(7*MAX_UNIT_SLOTS+3+FST_SET+FST_POP)
	GO4K_FOP	OP(FOP_LOADNOTE)
	GO4K_FST	AMOUNT(128),DEST(11*MAX_UNIT_SLOTS+4+FST_SET+FST_POP)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument5)
	GO4K_ENV	ATTAC(0),DECAY(100),SUSTAIN(8),RELEASE(67),GAIN(128)
	GO4K_FST	AMOUNT(94),DEST(21*MAX_UNIT_SLOTS+1+FST_SET)
	GO4K_VCO	TRANSPOSE(52),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(TRISAW)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_DST	DRIVE(126), SNHFREQ(28), FLAGS(0)
	GO4K_DLL	PREGAIN(60),DRY(0),FEEDBACK(118),DAMP(0),FREQUENCY(0),DEPTH(0),DELAY(9),COUNT(8)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCO	TRANSPOSE(40),DETUNE(72),PHASE(0),GATES(0),COLOR(128),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_DST	DRIVE(126), SNHFREQ(128), FLAGS(0)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FOP	OP(FOP_PUSH)
	GO4K_VCF	FREQUENCY(48),RESONANCE(24),VCFTYPE(LOWPASS)
	GO4K_ENV	ATTAC(0),DECAY(64),SUSTAIN(0),RELEASE(102),GAIN(102)
	GO4K_FST	AMOUNT(94),DEST(8*MAX_UNIT_SLOTS+1+FST_SET+FST_POP)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_FST	AMOUNT(58),DEST(20*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_VCO	TRANSPOSE(83),DETUNE(64),PHASE(0),GATES(0),COLOR(124),SHAPE(64),GAIN(72),FLAGS(PULSE)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_VCF	FREQUENCY(128),RESONANCE(24),VCFTYPE(LOWPASS)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(0), AUXSEND(10)
	GO4K_ENV	ATTAC(96),DECAY(0),SUSTAIN(128),RELEASE(92),GAIN(128)
	GO4K_FST	AMOUNT(26),DEST(19*MAX_UNIT_SLOTS+4+FST_SET+FST_POP)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument6)
	GO4K_ENV	ATTAC(76),DECAY(0),SUSTAIN(128),RELEASE(80),GAIN(128)
	GO4K_VCO	TRANSPOSE(128),DETUNE(64),PHASE(0),GATES(0),COLOR(0),SHAPE(64),GAIN(64),FLAGS(TRISAW|LFO)
	GO4K_FLD	VALUE(108)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(56),RESONANCE(128),VCFTYPE(HIGHPASS)
	GO4K_FLD	VALUE(64)
	GO4K_FOP	OP(FOP_ADDP)
	GO4K_DST	DRIVE(41), SNHFREQ(128), FLAGS(0)
	GO4K_DLL	PREGAIN(112),DRY(128),FEEDBACK(0),DAMP(0),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(98),RESONANCE(72),VCFTYPE(LOWPASS)
	GO4K_FST	AMOUNT(111),DEST(7*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_PAN	PANNING(48)
	GO4K_OUT	GAIN(112), AUXSEND(101)
	GO4K_ENV	ATTAC(92),DECAY(0),SUSTAIN(128),RELEASE(90),GAIN(128)
	GO4K_FST	AMOUNT(25),DEST(1*MAX_UNIT_SLOTS+1+FST_SET+FST_POP)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument7)
	GO4K_ENV	ATTAC(0),DECAY(0),SUSTAIN(128),RELEASE(76),GAIN(128)
	GO4K_FOP	OP(FOP_PUSH)
	GO4K_VCO	TRANSPOSE(88),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(PULSE|LFO)
	GO4K_VCF	FREQUENCY(26),RESONANCE(1),VCFTYPE(HIGHPASS)
	GO4K_DST	DRIVE(8), SNHFREQ(36), FLAGS(0)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_FST	AMOUNT(56),DEST(4*MAX_UNIT_SLOTS+3+FST_SET)
	GO4K_PAN	PANNING(0)
	GO4K_OUT	GAIN(92), AUXSEND(72)
	GO4K_VCO	TRANSPOSE(76),DETUNE(64),PHASE(0),GATES(0),COLOR(0),SHAPE(64),GAIN(128),FLAGS(TRISAW|LFO)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_FST	AMOUNT(128),DEST(7*MAX_UNIT_SLOTS+0+FST_SET)
	GO4K_FSTG	AMOUNT(80),DEST((0*go4k_instrument.size*MAX_VOICES/4)+(5*MAX_UNIT_SLOTS+4)+(go4k_instrument.workspace/4)+FST_SET)
	GO4K_FSTG	AMOUNT(76),DEST((1*go4k_instrument.size*MAX_VOICES/4)+(5*MAX_UNIT_SLOTS+4)+(go4k_instrument.workspace/4)+FST_SET)
	GO4K_FSTG	AMOUNT(48),DEST((2*go4k_instrument.size*MAX_VOICES/4)+(5*MAX_UNIT_SLOTS+4)+(go4k_instrument.workspace/4)+FST_SET+FST_POP)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Global)
	GO4K_ACC	ACCTYPE(AUX)
	GO4K_VCF	FREQUENCY(16),RESONANCE(128),VCFTYPE(HIGHPASS)
	GO4K_DLL	PREGAIN(84),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_DLL	PREGAIN(40),DRY(0),FEEDBACK(125),DAMP(48),FREQUENCY(0),DEPTH(0),DELAY(1),COUNT(8)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_VCF	FREQUENCY(16),RESONANCE(128),VCFTYPE(HIGHPASS)
	GO4K_DLL	PREGAIN(84),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(18),COUNT(1)
	GO4K_DLL	PREGAIN(40),DRY(0),FEEDBACK(125),DAMP(48),FREQUENCY(0),DEPTH(0),DELAY(9),COUNT(8)
	GO4K_ACC	ACCTYPE(OUTPUT)
	GO4K_FOP	OP(FOP_ADDP2)
	GO4K_OUT	GAIN(32), AUXSEND(0)
GO4K_END_PARAMDEF
go4k_synth_parameter_values_end
%ifdef USE_SECTIONS
section .g4kmuc5 data align=1
%else
section .data
%endif
%ifdef GO4K_USE_DLL
global _go4k_delay_times
_go4k_delay_times
	dw 0
	dw 1116
	dw 1188
	dw 1276
	dw 1356
	dw 1422
	dw 1492
	dw 1556
	dw 1618
	dw 1140
	dw 1212
	dw 1300
	dw 1380
	dw 1446
	dw 1516
	dw 1580
	dw 1642
	dw 65535
	dw 55125
%endif
