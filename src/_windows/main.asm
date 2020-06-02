bits 32

%include "4klang.asm"

;//=============================================================================================================================
;// defines
;//=============================================================================================================================
%define HIDECURSOR
%define DRAW_TEXT
%define VOLUME_SIZE			256
 
%define SCREEN_WIDTH		1280
%define SCREEN_HEIGHT		720

%define	VK_ESCAPE			1bh

;//=============================================================================================================================
;// imports
;//=============================================================================================================================
extern __imp__CreateWindowExA@48
extern __imp__GetAsyncKeyState@4
extern __imp__ExitProcess@4
%ifdef HIDECURSOR
extern __imp__ShowCursor@4
%endif
extern __imp__PeekMessageA@20
extern __imp__ChangeDisplaySettingsA@8
extern __imp__GetDC@4
extern __imp__ChoosePixelFormat@8
extern __imp__SetPixelFormat@12
extern __imp__CreateThread@24
%ifdef DRAW_TEXT
extern __imp__CreateFontA@56
extern __imp__SelectObject@8
extern __imp__wglUseFontBitmapsA@16
extern __imp__glRasterPos2f@8
extern __imp__glCallLists@12
%endif
extern __imp__wglCreateContext@4
extern __imp__wglMakeCurrent@8
extern __imp__wglGetProcAddress@4
extern __imp__wglSwapLayerBuffers@8
extern __imp__glRects@16
extern __imp__glFinish@0
extern __imp__glBindTexture@8
extern __imp__glTexParameteri@12
extern __imp__glCopyTexImage2D@32
extern __imp__waveOutOpen@24
extern __imp__waveOutPrepareHeader@12
extern __imp__waveOutWrite@12
extern __imp__waveOutGetPosition@12


;//=============================================================================================================================
;// initialized data
;//=============================================================================================================================

section		.mbss1	bss		align=1
hWaveOut		resd	1
lpSoundBuffer 	resd	MAX_SAMPLES*2

;//=============================================================================================================================
;// initialized data
;//=============================================================================================================================
section	.mdat1	data	align=1
;// static const PIXELFORMATDESCRIPTOR pfd = {
;//    sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
;//    32, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
pfd				db	0x28, 0x00, 0x01, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20;//, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				;//db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		
;section	.mdat2	data	align=1		
;//static DEVMODE screenSettings = { {0},
;//    #if _MSC_VER < 1400
;//    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
;//    #else
;//    0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
;//    #endif
;//    #if(WINVER >= 0x0400)
;//    0,0,0,0,0,0,
;//    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
;//    0,0
;//    #endif
;//    #endif
;//    };		
screenSettings	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00
				db	0xD0
MMTime			db	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	          

section	.mdat3	data	align=1
;// str stride = 22+terminating zero = 23
strs			db  "glCreateShaderProgramv", 				0
				db	"glTexStorage3D",0,0,0,0,0,0,0,0,		0
				db	"glCopyTexSubImage3D",0,0,0, 			0
				db	"glUseProgram",0,0,0,0,0,0,0,0,0,0,		0
				db	"glUniform4i",0,0,0,0,0,0,0,0,0,0,0,	0
				db	"glActiveTexture",0,0,0,0,0,0,0,		0
				db	"glGenerateMipmap",0,0,0,0,0,0,			0
%define glCreateShaderProgramv 	0
%define glTexStorage3D 			4
%define glCopyTexSubImage3D 	8
%define glUseProgram 			12
%define glUniform4i 			16
%define glActiveTexture 		20
%define glGenerateMipmap 		24


;//section	.mdat6	data	align=1
;//MMTIME MMTime = 
;//{ 
;//	TIME_SAMPLES,
;//	0
;//};
;//MMTime			db	0x02, 0x00, 0x00, 0x00					;// merged with screenSettings
;MMTimeSamples	dd	0
				
section	.mdat4	data	align=1
;// WAVEFORMATEX WaveFMT = 
;//	{
;// 	WAVE_FORMAT_IEEE_FLOAT,
;//     2, // channels
;//     SAMPLE_RATE, // samples per sec
;//     SAMPLE_RATE*sizeof(SAMPLE_TYPE)*2, // bytes per sec
;//     sizeof(SAMPLE_TYPE)*2, // block alignment;
;//     sizeof(SAMPLE_TYPE)*8, // bits per sample
;//     0 // extension not needed
;// };
WaveFMT			db	0x03, 0x00, 0x02, 0x00
				dd	SAMPLE_RATE
				dd	SAMPLE_RATE*4*2
				db	0x08, 0x00
				db	0x20, 0x00
				dd	0x00000000

section	.mdat5	data	align=1
;//WAVEHDR WaveHDR = 
;//{
;//		(LPSTR)lpSoundBuffer, 
;//		MAX_SAMPLES*sizeof(SAMPLE_TYPE)*2,			// MAX_SAMPLES*sizeof(float)*2(stereo)
;//		0, 
;//		0, 
;//		0, 
;//		0, 
;//		0, 
;//		0
;//};
WaveHDR			dd	lpSoundBuffer
				dd	MAX_SAMPLES*4*2
				dd	0, 0, 0, 0, 0, 0

;// credit text
section	.mdat7	data	align=1
fontname		db	"dotum",0
section	.mdat8	data	align=1
credit1			db	"eos/atz",0
section	.mdat9	data	align=1
credit2			db	"horizon machine",0

;//-----------------------------------------------------------------------
;// shader source
;//-----------------------------------------------------------------------
section	.mdat10	data	align=1
fragment_glsl:
db	"#version 430",0x0a
db	"#define H vec3",0x0a
db	"#define I float",0x0a
db	"#define J length",0x0a
db	"#define K gl_FragCoord",0x0a
db	"layout(binding=1)uniform sampler2D l;layout(binding=0)uniform sampler3D m;layout(location=4)uniform ivec4 v;I z=(v.x*73856093^int(K.x)*19349663^int(K.y)*83492791)%38069,y=6.283,i=.1,a=v.y/44100.,x=v.z/44100.;I s(){return fract(sin(z++)*43758.5);}I s(I v,I l){return(abs(mod(l-v,.1818)-.0909)+v+l)/2;}I h(H l,H z){return J(max(abs(l)-z,0));}I h(H v){I l=min(min(1-s(J(v.xz),abs(v.y)),s(J(v.xz),v.y)+.2),J(v-H(normalize(v.xz)*.45,0).xzy)-.02);v=abs(v);if(v.z>v.x)v.xz=v.zx;return min(min(l,J(v-H(normalize(v.xy)*.45,0))-.02),a>120?J(v)-.4:100.);}I s(H v){I l=min(v.y+.2,-(abs(J(v.xz)-1.85)-1.65-clamp(v.y-1,-1,0)));l=min(l,max(v.y-.15,2.5-J(v.xz)));v.xz=vec2(J(v.xz)-2,mod(atan(v.z,v.x)/y*9,1)-.5);return min(l,min(min(min(h(v-H(0,.05,0),H(.135,.025,.15)),h(v-H(-.13,.3,0),H(.025,.15,.15)))-.01,max(v.y,J(v.xz)-.02)+min(v.y+.1,0)),h(v-H(-.15,.2,0),H(.025,.15,.05))));}I n(H v){return v.z-=.8,min(min(min(max(min(min(max(s(J(v.xz)-1,.3+.1*cos(v.y*4)),-s(J(v.xz)-.95,.3+.1*cos(v.y*14))),s(J(v.xz)-.35,.1+.15*cos(v.y*2.2))),max(s(J(v.xz)-.4,.1+.15*cos(v.y*20.2)),-(J(v.xz)-.4))),v.z-.375),-(J(v.xz)-1.4)),J(v.xz-vec2(.5,.9))-.1),J(v.xz-vec2(-.3,.9))-.1);}I f(H v){v.xz*=mat2(.5,-.87,-.87,-.5);I l=min(s(J(v.xy)-.25,s(h(v,H(.2))-.5,abs(s(J(v.xz)-1,.6)))),h(v-H(0,(a-56)/5.+7,4.7),H(1,8,.8)));v.z-=1;return min(min(l-.2,1-s(J(v.xzy)-1,s(J(v.xy)-1,.6+.2*cos(v.z*3+v.y)))),v.y+.6+cos(v.z*80)/1000);}I t(H v){return a<43?s(v):a<78?f(v):a<103?n(v):h(v);}H e(I v){return a<43?H(-1.7+v/30,1.2,5.1)/2:a<78?H(.2-1.5*fract((v-43)/70),-.4,1.2):a<103?H(0,v/30+1.5,2):H(0,-.3+(v-120)/60,1.4);}H g=e(a),w=e(x),r=(H(s(),s(),s())-.5)/256.;H e(H v,H z){return v-=z,H(-v.xy/v.z*vec2(.28125,.5)+.5,J(v)*256./8);}I p(vec2 v){a-=120;v*=exp(-a/7)/(.05+J(v))*4;for(int z=0;z<15;++z)v+=vec2(cos(v.y*8),sin(v.x*4+v.x*9)-a/8+1)/7.,v=abs(v);return exp(-J(v));}H e(H v,H z,I y){H i=H(0);I f=1.;for(int l=0;l<120&&f>.01;++l){H a=e(v+=z*.03,g);vec4 d=textureLod(m,r+H(a.xy,a.z/256.),log2(l*y/7));i+=d.xyz*f;f*=1.-d.w;}return i;}void main(){vec4 z=vec4(0);vec2 x=vec2(mod(I(v.x),2.)/2.,mod(v.x/2.,2.)/2.);H f=g,n=normalize(H((K.xy+x)/360+vec2(s()-.5,s()-.5)/30*(1.-min(texelFetch(l,ivec2(K.xy),0).w/.1,1.))-vec2(1.77778,1),-1));if(v.w<1){for(int r=0;r++<120&&abs(i=t(f+=n*i*.8))>.0001;);H d=H(.001,0,0),r=normalize(H(t(f+d.xyy),t(f+d.yxy),t(f+d.yyx))-i);if(a<43||a>=78&&a<103)r=normalize(r+H(0,sin(clamp((mod(f.y+.12,.05)/.05-.8)/.2*y,0.,y)),0));H c=f,h=normalize(reflect(n,r)),o=normalize(cross(r.xyz,r.zxy)),b=cross(r.xyz,o),u=H(.9);z.w=J(f-g)*256./8/255.;I F=1+8*step(.5,fract(atan(f.z-.8,f.x)/y*32));if(a<43){if(J(f.xz)>1.&&abs(f.y-1.)<.1)z.xyz=H(1.,.4,.2);I C=atan(f.z,f.x)/y*40;if(abs(J(f.xz)-2.8)<.1&&fract(C)>.03&&cos(floor(C)*9)+2<a/13.)z.xyz=H(.7);if(J(f.xz)<.35)z.xyz=H(1,.1,.02);F=2;}else if(a<78){H C=f;C.xz*=mat2(.5,-.87,-.87,-.5);if(abs(C.z)>3.7||(C.z>3.&&(a>50&&abs(J(C.xy)-1.)<.02)||abs(J(C.xy)-1.4)<.02))z.xyz=H(1,.8,.6);if(f.y<-.599&&(abs(C.x)<.2||abs(C.z)<.02))z.xyz=H(1.,.4,.2)/4;F=2;u/=1.3;}else if(a<103){if(J(f.xz-vec2(0,.8))<.125)z.xyz=H(1,.8,.6);if(abs(f.x)>1.3)z.xyz=H(1.,.4,.2);u/=1.4;}else{if(r.y<-.999)z.xyz=H(1.,.4,.2)/(2-step(f.y,0));if(J(f)<.44&&a>120)z.xyz=H(1);}f+=r*.05;z.xyz+=e(f,h,F)*.75*pow(clamp(1.-dot(-n,r),0.,1.),1.);for(int C=0;C<4;++C){I q=y*s(),L=s();z.xyz+=e(f,(o*cos(q)+b*sin(q))*sqrt(L)+r*sqrt(1.-L),7)/4*u*sqrt(1.-L);}f=w;i=.1;for(int C=0;C++<120&&abs(i=t(f+=normalize(H((K.xy+vec2(mod(v.x-1.,2.)/2.,mod((v.x-1.)/2.,2.)/2.))/360-vec2(1.77778,1),-1))*i*.8))>.0001;);z.xyz=mix(clamp(z.xyz,0.,1.),texture(l,e(c,w).xy-x/vec2(1280,720)).xyz,J(f-c)<.05?.85:.65);}else if(v.w<2){int r=8-int(log2(511-K.x));if(r==0){f=g+normalize(H((K.x/256.*2-1)*1280./720.,K.y/256.*2.-1.,-1.))*v.x*8./256.;i=t(f);if(i<-.1)z.w=smoothstep(.1,.2,-i);else{for(int C=-3;C<4;++C)for(int c=-3;c<4;++c){vec4 d=texelFetch(l,ivec2(c,C)+ivec2(e(f,w).xy*vec2(1280,720)),0);if(abs(v.x-d.w*255.)<2)z.xyz+=d.xyz,z.w+=1;}if(z.w>0.)z/=z.w;}}else for(int C=0;C<2;++C)for(int c=0;c<2;++c)for(int d=0;d<2;++d)z+=texelFetch(m,ivec3(K.xy-vec2(511.-(exp2(9-r)-1),0),v.x)*2+ivec3(d,c,C),r-1)/8;}else{vec2 C=abs(K.xy/vec2(1280,720)*2-1);z=textureLod(l,K.xy/vec2(1280,720)+.02,6.5);z=(z*z+texelFetch(l,ivec2(K.xy),0))*(2.3-(pow(C.x,8.)+pow(C.y,8.)))*smoothstep(0.,4.,min(a,min(min(abs(a-43),abs(a-78)),abs(a-103))));z=z/(z+1)*2.3+p(C);}gl_FragColor=z;}"

;db	"uniform sampler2D l;uniform sampler3D m;uniform ivec4 v;float z=(v.x*73856093^int(gl_FragCoord.x)*19349663^int(gl_FragCoord.y)*83492791)%38069,y=6.283,i=.1,a=v.y/44100.,x=v.z/44100.;float s(){return fract(sin(z++)*43758.5);}float s(float v,float l){return(abs(mod(l-v,.1818)-.0909)+v+l)/2;}float h(vec3 l,vec3 z){return length(max(abs(l)-z,0));}float h(vec3 v){float l=min(min(1-s(length(v.xz),abs(v.y)),s(length(v.xz),v.y)+.2),length(v-vec3(normalize(v.xz)*.45,0).xzy)-.02);v=abs(v);if(v.z>v.x)v.xz=v.zx;return min(min(l,length(v-vec3(normalize(v.xy)*.45,0))-.02),a>120?length(v)-.4:100.);}float s(vec3 v){float l=min(v.y+.2,-(abs(length(v.xz)-1.85)-1.65-clamp(v.y-1,-1,0)));l=min(l,max(v.y-.15,2.5-length(v.xz)));v.xz=vec2(length(v.xz)-2,mod(atan(v.z,v.x)/y*9,1)-.5);return min(l,min(min(min(h(v-vec3(0,.05,0),vec3(.135,.025,.15)),h(v-vec3(-.13,.3,0),vec3(.025,.15,.15)))-.01,max(v.y,length(v.xz)-.02)+min(v.y+.1,0)),h(v-vec3(-.15,.2,0),vec3(.025,.15,.05))));}float n(vec3 v){return v.z-=.8,min(min(min(max(min(min(max(s(length(v.xz)-1,.3+.1*cos(v.y*4)),-s(length(v.xz)-.95,.3+.1*cos(v.y*14))),s(length(v.xz)-.35,.1+.15*cos(v.y*2.2))),max(s(length(v.xz)-.4,.1+.15*cos(v.y*20.2)),-(length(v.xz)-.4))),v.z-.375),-(length(v.xz)-1.4)),length(v.xz-vec2(.5,.9))-.1),length(v.xz-vec2(-.3,.9))-.1);}float f(vec3 v){v.xz*=mat2(.5,-.87,-.87,-.5);float l=min(s(length(v.xy)-.25,s(h(v,vec3(.2))-.5,abs(s(length(v.xz)-1,.6)))),h(v-vec3(0,(a-56)/5.+7,4.7),vec3(1,8,.8)));v.z-=1;return min(min(l-.2,1-s(length(v.xzy)-1,s(length(v.xy)-1,.6+.2*cos(v.z*3+v.y)))),v.y+.6+cos(v.z*80)/1000);}float t(vec3 v){return a<43?s(v):a<78?f(v):a<103?n(v):h(v);}vec3 e(float v){return a<43?vec3(-1.7+v/30,1.2,5.1)/2:a<78?vec3(.2-1.5*fract((v-43)/70),-.4,1.2):a<103?vec3(0,v/30+1.5,2):vec3(0,-.3+(v-120)/60,1.4);}vec3 g=e(a),w=e(x),r=(vec3(s(),s(),s())-.5)/256.;vec3 e(vec3 v,vec3 z){return v-=z,vec3(-v.xy/v.z*vec2(.28125,.5)+.5,length(v)*256./8);}float p(vec2 v){a-=120;v*=exp(-a/7)/(.05+length(v))*4;for(int z=0;z<15;++z)v+=vec2(cos(v.y*8),sin(v.x*4+v.x*9)-a/8+1)/7.,v=abs(v);return exp(-length(v));}vec3 e(vec3 v,vec3 z,float y){vec3 i=vec3(0);float f=1.;for(int l=0;l<120&&f>.01;++l){vec3 a=e(v+=z*.03,g);vec4 d=textureLod(m,r+vec3(a.xy,a.z/256.),log2(l*y/7));i+=d.xyz*f;f*=1.-d.w;}return i;}void main(){vec4 z=vec4(0);vec2 x=vec2(mod(float(v.x),2.)/2.,mod(v.x/2.,2.)/2.);vec3 f=g,n=normalize(vec3((gl_FragCoord.xy+x)/360+vec2(s()-.5,s()-.5)/30*(1.-min(texelFetch(l,ivec2(gl_FragCoord.xy),0).w/.1,1.))-vec2(1.77778,1),-1));if(v.w<1){for(int r=0;r++<120&&abs(i=t(f+=n*i*.8))>.0001;);vec3 d=vec3(.001,0,0),r=normalize(vec3(t(f+d.xyy),t(f+d.yxy),t(f+d.yyx))-i);if(a<43||a>=78&&a<103)r=normalize(r+vec3(0,sin(clamp((mod(f.y+.12,.05)/.05-.8)/.2*y,0.,y)),0));vec3 c=f,h=normalize(reflect(n,r)),o=normalize(cross(r.xyz,r.zxy)),b=cross(r.xyz,o),u=vec3(.9);z.w=length(f-g)*256./8/255.;float F=1+8*step(.5,fract(atan(f.z-.8,f.x)/y*32));if(a<43){if(length(f.xz)>1.&&abs(f.y-1.)<.1)z.xyz=vec3(1.,.4,.2);float C=atan(f.z,f.x)/y*40;if(abs(length(f.xz)-2.8)<.1&&fract(C)>.03&&cos(floor(C)*9)+2<a/13.)z.xyz=vec3(.7);if(length(f.xz)<.35)z.xyz=vec3(1,.1,.02);F=2;}else if(a<78){vec3 C=f;C.xz*=mat2(.5,-.87,-.87,-.5);if(abs(C.z)>3.7||(C.z>3.&&(a>50&&abs(length(C.xy)-1.)<.02)||abs(length(C.xy)-1.4)<.02))z.xyz=vec3(1,.8,.6);if(f.y<-.599&&(abs(C.x)<.2||abs(C.z)<.02))z.xyz=vec3(1.,.4,.2)/4;F=2;u/=1.3;}else if(a<103){if(length(f.xz-vec2(0,.8))<.125)z.xyz=vec3(1,.8,.6);if(abs(f.x)>1.3)z.xyz=vec3(1.,.4,.2);u/=1.4;}else{if(r.y<-.999)z.xyz=vec3(1.,.4,.2)/(2-step(f.y,0));if(length(f)<.44&&a>120)z.xyz=vec3(1);}f+=r*.05;z.xyz+=e(f,h,F)*.75*pow(clamp(1.-dot(-n,r),0.,1.),1.);for(int C=0;C<4;++C){float q=y*s(),L=s();z.xyz+=e(f,(o*cos(q)+b*sin(q))*sqrt(L)+r*sqrt(1.-L),7)/4*u*sqrt(1.-L);}f=w;i=.1;for(int C=0;C++<120&&abs(i=t(f+=normalize(vec3((gl_FragCoord.xy+vec2(mod(v.x-1.,2.)/2.,mod((v.x-1.)/2.,2.)/2.))/360-vec2(1.77778,1),-1))*i*.8))>.0001;);z.xyz=mix(clamp(z.xyz,0.,1.),texture(l,e(c,w).xy-x/vec2(1280,720)).xyz,length(f-c)<.05?.85:.65);}else if(v.w<2){int r=8-int(log2(511-gl_FragCoord.x));if(r==0){f=g+normalize(vec3((gl_FragCoord.x/256.*2-1)*1280./720.,gl_FragCoord.y/256.*2.-1.,-1.))*v.x*8./256.;i=t(f);if(i<-.1)z.w=smoothstep(.1,.2,-i);else{for(int C=-3;C<4;++C)for(int c=-3;c<4;++c){vec4 d=texelFetch(l,ivec2(c,C)+ivec2(e(f,w).xy*vec2(1280,720)),0);if(abs(v.x-d.w*255.)<2)z.xyz+=d.xyz,z.w+=1;}if(z.w>0.)z/=z.w;}}else for(int C=0;C<2;++C)for(int c=0;c<2;++c)for(int d=0;d<2;++d)z+=texelFetch(m,ivec3(gl_FragCoord.xy-vec2(511.-(exp2(9-r)-1),0),v.x)*2+ivec3(d,c,C),r-1)/8;}else{vec2 C=abs(gl_FragCoord.xy/vec2(1280,720)*2-1);z=textureLod(l,gl_FragCoord.xy/vec2(1280,720)+.02,6.5);z=(z*z+texelFetch(l,ivec2(gl_FragCoord.xy),0))*(2.3-(pow(C.x,8.)+pow(C.y,8.)))*smoothstep(0.,4.,min(a,min(min(abs(a-43),abs(a-78)),abs(a-103))));z=z/(z+1)*2.3+p(C);}gl_FragColor=z;}"

;db	"layout(binding=1)uniform sampler2D l;layout(binding=0)uniform sampler3D m;layout(location=4)uniform ivec4 v;float z=(v.x*73856093^int(gl_FragCoord.x)*19349663^int(gl_FragCoord.y)*83492791)%38069,y=6.283,i=.1,a=v.y/44100.,x=v.z/44100.;float s(){return fract(sin(z++)*43758.5);}float s(float v,float l){return(abs(mod(l-v,.1818)-.0909)+v+l)/2;}float h(vec3 l,vec3 z){return length(max(abs(l)-z,0));}float h(vec3 v){float l=min(min(1-s(length(v.xz),abs(v.y)),s(length(v.xz),v.y)+.2),length(v-vec3(normalize(v.xz)*.45,0).xzy)-.02);v=abs(v);if(v.z>v.x)v.xz=v.zx;return min(min(l,length(v-vec3(normalize(v.xy)*.45,0))-.02),a>120?length(v)-.4:100.);}float s(vec3 v){float l=min(v.y+.2,-(abs(length(v.xz)-1.85)-1.65-clamp(v.y-1,-1,0)));l=min(l,max(v.y-.15,2.5-length(v.xz)));v.xz=vec2(length(v.xz)-2,mod(atan(v.z,v.x)/y*9,1)-.5);return min(l,min(min(min(h(v-vec3(0,.05,0),vec3(.135,.025,.15)),h(v-vec3(-.13,.3,0),vec3(.025,.15,.15)))-.01,max(v.y,length(v.xz)-.02)+min(v.y+.1,0)),h(v-vec3(-.15,.2,0),vec3(.025,.15,.05))));}float n(vec3 v){return v.z-=.8,min(min(min(max(min(min(max(s(length(v.xz)-1,.3+.1*cos(v.y*4)),-s(length(v.xz)-.95,.3+.1*cos(v.y*14))),s(length(v.xz)-.35,.1+.15*cos(v.y*2.2))),max(s(length(v.xz)-.4,.1+.15*cos(v.y*20.2)),-(length(v.xz)-.4))),v.z-.375),-(length(v.xz)-1.4)),length(v.xz-vec2(.5,.9))-.1),length(v.xz-vec2(-.3,.9))-.1);}float f(vec3 v){v.xz*=mat2(.5,-.87,-.87,-.5);float l=min(s(length(v.xy)-.25,s(h(v,vec3(.2))-.5,abs(s(length(v.xz)-1,.6)))),h(v-vec3(0,(a-56)/5.+7,4.7),vec3(1,8,.8)));v.z-=1;return min(min(l-.2,1-s(length(v.xzy)-1,s(length(v.xy)-1,.6+.2*cos(v.z*3+v.y)))),v.y+.6+cos(v.z*80)/1000);}float t(vec3 v){return a<43?s(v):a<78?f(v):a<103?n(v):h(v);}vec3 e(float v){return a<43?vec3(-1.7+v/30,1.2,5.1)/2:a<78?vec3(.2-1.5*fract((v-43)/70),-.4,1.2):a<103?vec3(0,v/30+1.5,2):vec3(0,-.3+(v-120)/60,1.4);}vec3 g=e(a),w=e(x),r=(vec3(s(),s(),s())-.5)/256.;vec3 e(vec3 v,vec3 z){return v-=z,vec3(-v.xy/v.z*vec2(.28125,.5)+.5,length(v)*256./8);}float p(vec2 v){a-=120;v*=exp(-a/7)/(.05+length(v))*4;for(int z=0;z<15;++z)v+=vec2(cos(v.y*8),sin(v.x*4+v.x*9)-a/8+1)/7.,v=abs(v);return exp(-length(v));}vec3 e(vec3 v,vec3 z,float y){vec3 i=vec3(0);float f=1.;for(int l=0;l<120&&f>.01;++l){vec3 a=e(v+=z*.03,g);vec4 d=textureLod(m,r+vec3(a.xy,a.z/256.),log2(l*y/7));i+=d.xyz*f;f*=1.-d.w;}return i;}void main(){vec4 z=vec4(0);vec2 x=vec2(mod(float(v.x),2.)/2.,mod(v.x/2.,2.)/2.);vec3 f=g,n=normalize(vec3((gl_FragCoord.xy+x)/360+vec2(s()-.5,s()-.5)/30*(1.-min(texelFetch(l,ivec2(gl_FragCoord.xy),0).w/.1,1.))-vec2(1.77778,1),-1));if(v.w<1){for(int r=0;r++<120&&abs(i=t(f+=n*i*.8))>.0001;);vec3 d=vec3(.001,0,0),r=normalize(vec3(t(f+d.xyy),t(f+d.yxy),t(f+d.yyx))-i);if(a<43||a>=78&&a<103)r=normalize(r+vec3(0,sin(clamp((mod(f.y+.12,.05)/.05-.8)/.2*y,0.,y)),0));vec3 c=f,h=normalize(reflect(n,r)),o=normalize(cross(r.xyz,r.zxy)),b=cross(r.xyz,o),u=vec3(.9);z.w=length(f-g)*256./8/255.;float F=1+8*step(.5,fract(atan(f.z-.8,f.x)/y*32));if(a<43){if(length(f.xz)>1.&&abs(f.y-1.)<.1)z.xyz=vec3(1.,.4,.2);float C=atan(f.z,f.x)/y*40;if(abs(length(f.xz)-2.8)<.1&&fract(C)>.03&&cos(floor(C)*9)+2<a/13.)z.xyz=vec3(.7);if(length(f.xz)<.35)z.xyz=vec3(1,.1,.02);F=2;}else if(a<78){vec3 C=f;C.xz*=mat2(.5,-.87,-.87,-.5);if(abs(C.z)>3.7||(C.z>3.&&(a>50&&abs(length(C.xy)-1.)<.02)||abs(length(C.xy)-1.4)<.02))z.xyz=vec3(1,.8,.6);if(f.y<-.599&&(abs(C.x)<.2||abs(C.z)<.02))z.xyz=vec3(1.,.4,.2)/4;F=2;u/=1.3;}else if(a<103){if(length(f.xz-vec2(0,.8))<.125)z.xyz=vec3(1,.8,.6);if(abs(f.x)>1.3)z.xyz=vec3(1.,.4,.2);u/=1.4;}else{if(r.y<-.999)z.xyz=vec3(1.,.4,.2)/(2-step(f.y,0));if(length(f)<.44&&a>120)z.xyz=vec3(1);}f+=r*.05;z.xyz+=e(f,h,F)*.75*pow(clamp(1.-dot(-n,r),0.,1.),1.);for(int C=0;C<4;++C){float q=y*s(),L=s();z.xyz+=e(f,(o*cos(q)+b*sin(q))*sqrt(L)+r*sqrt(1.-L),7)/4*u*sqrt(1.-L);}f=w;i=.1;for(int C=0;C++<120&&abs(i=t(f+=normalize(vec3((gl_FragCoord.xy+vec2(mod(v.x-1.,2.)/2.,mod((v.x-1.)/2.,2.)/2.))/360-vec2(1.77778,1),-1))*i*.8))>.0001;);z.xyz=mix(clamp(z.xyz,0.,1.),texture(l,e(c,w).xy-x/vec2(1280,720)).xyz,length(f-c)<.05?.85:.65);}else if(v.w<2){int r=8-int(log2(511-gl_FragCoord.x));if(r==0){f=g+normalize(vec3((gl_FragCoord.x/256.*2-1)*1280./720.,gl_FragCoord.y/256.*2.-1.,-1.))*v.x*8./256.;i=t(f);if(i<-.1)z.w=smoothstep(.1,.2,-i);else{for(int C=-3;C<4;++C)for(int c=-3;c<4;++c){vec4 d=texelFetch(l,ivec2(c,C)+ivec2(e(f,w).xy*vec2(1280,720)),0);if(abs(v.x-d.w*255.)<2)z.xyz+=d.xyz,z.w+=1;}if(z.w>0.)z/=z.w;}}else for(int C=0;C<2;++C)for(int c=0;c<2;++c)for(int d=0;d<2;++d)z+=texelFetch(m,ivec3(gl_FragCoord.xy-vec2(511.-(exp2(9-r)-1),0),v.x)*2+ivec3(d,c,C),r-1)/8;}else{vec2 C=abs(gl_FragCoord.xy/vec2(1280,720)*2-1);z=textureLod(l,gl_FragCoord.xy/vec2(1280,720)+.02,6.5);z=(z*z+texelFetch(l,ivec2(gl_FragCoord.xy),0))*(2.3-(pow(C.x,8.)+pow(C.y,8.)))*smoothstep(0.,4.,min(a,min(min(abs(a-43),abs(a-78)),abs(a-103))));z=z/(z+1)*2.3+p(C);}gl_FragColor=z;}"

db	0

;//-----------------------------------------------------------------------
;// music
;//-----------------------------------------------------------------------

;//=============================================================================================================================
;// code
;//=============================================================================================================================
section		.mcod1	code	align=1

global _WinMainCRTStartup
_WinMainCRTStartup:
	;// for show cursor
%ifdef HIDECURSOR	
	push        0
%endif
	;// for CreateWindowExA(0, (LPCSTR)0x0C018, 0, WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);	
	push        0
	push        0
	push        0
	push        0
	push        SCREEN_HEIGHT    
	push        SCREEN_WIDTH    
	push        0  
	push        0  	
	push        90000000h    ;WS_POPUP|WS_VISIBLE
	push        0  
	push        0c018h 	
	push		0
;// ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN);
	push		4
	push		screenSettings
	call		dword [__imp__ChangeDisplaySettingsA@8]		
;//	CreateWindowExA(0, (LPCSTR)0x0C018, 0, WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);	
	call        dword [__imp__CreateWindowExA@48]	
;// GetDC(hWnd);
	push		eax
	call		dword [__imp__GetDC@4]	
	mov			ebp, eax	;ebp = hDC	
;// SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd);
	push		pfd
	push		eax
	call		dword [__imp__ChoosePixelFormat@8]
	push		pfd
	push		eax
	push		ebp
	call		dword [__imp__SetPixelFormat@12]
;// wglMakeCurrent(hDC,wglCreateContext(hDC));
	push		ebp
	call		dword [__imp__wglCreateContext@4]
	push		eax
	push		ebp
	call		dword [__imp__wglMakeCurrent@8]	
;// wglGetProcAddress for all needed functions 
	mov			edi, strs
	mov			ebx, edi
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
	add			ebx, 23
	push		ebx
	call		dword [__imp__wglGetProcAddress@4]
	stosd
;// oglCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragment_source);
	push		fragment_glsl
	push		esp
	push		1
	push		8B30h
	call		dword [strs+glCreateShaderProgramv]
	push		eax
	call		dword [strs+glUseProgram]	
	pop			eax		;// clear the fragment_glsl push	
;// glBindTexture(GL_TEXTURE_3D, 1);
	push		1
	push		806Fh	
	call		dword [__imp__glBindTexture@8]
;// glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	push		2703h
	push		2801h
	push		806Fh
	call		dword [__imp__glTexParameteri@12]
;// oglTexStorage3D(GL_TEXTURE_3D, 9, GL_RGBA8, VOLUME_SIZE, VOLUME_SIZE, VOLUME_SIZE);	
	push		VOLUME_SIZE
	push		VOLUME_SIZE
	push		VOLUME_SIZE
	push		8058h
	push		9	
	push		806Fh
	call		dword [strs+glTexStorage3D]
;//	ShowCursor(false)
%ifdef HIDECURSOR		
	call        dword [__imp__ShowCursor@4] 
%endif
%ifdef DRAW_TEXT
;// HFONT font = CreateFontA(-40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Dotum");
	push		fontname
	push		0
	push		4
	push		0
	push		4
	push		0
	push		0
	push		0
	push		0	
	push		400
	push		0	
	push		0	
	push		0	
	push		-40
	call		dword [__imp__CreateFontA@56]
;// SelectObject (hDC, font);
	push		eax
	push		ebp
	call		dword [__imp__SelectObject@8]
;// wglUseFontBitmapsA(hDC, 0, 256, 0); 
	push		0
	push		256
	push		0
	push		ebp
	call		dword [__imp__wglUseFontBitmapsA@16]
%endif
;// CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_4klang_render, lpSoundBuffer, 0, 0);
	push		0
	push		0
	push		lpSoundBuffer
	push		__4klang_render@4
	push		0
	push		0
	call		dword [__imp__CreateThread@24]	
;// waveOutOpen			( &hWaveOut, WAVE_MAPPER, &WaveFMT, NULL, 0, CALLBACK_NULL );	
	push		0
	push		0
	push		0
	push		WaveFMT
	push		-1
	push		hWaveOut
	call		dword [__imp__waveOutOpen@24]	
;// waveOutPrepareHeader( hWaveOut, &WaveHDR, sizeof(WaveHDR) );	
	push		20h
	push		WaveHDR
	push		dword [hWaveOut]
	call		dword [__imp__waveOutPrepareHeader@12]
;// waveOutWrite		( hWaveOut, &WaveHDR, sizeof(WaveHDR) );	
	push		20h
	push		WaveHDR	
	push		dword [hWaveOut]
	call		dword [__imp__waveOutWrite@12]	
	
	xor			esi, esi		;// esi = prev_t in samples
	xor			ebx, ebx		;// ebx = frame	
	
;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
;// INTRO MAIN LOOP
;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopIntro:	  	
	
;// waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));	
	push		12
	push		MMTime
	push		dword [hWaveOut]
	call		dword [__imp__waveOutGetPosition@12]
	mov			edi, dword [MMTime+4] 	;// edi = t in samples
	cmp			edi, MAX_SAMPLES
	jae			ExitLoop	
;// oglActiveTexture(GL_TEXTURE0);
	push		84C0h
	call		dword [strs+glActiveTexture]		
;// for(int i = frame&7; i < VOLUME_SIZE; i+=8)
;// {	
	mov			ecx, ebx
	and			ecx, 7
PropagationLoop:
;// 	oglUniform4i(4, i, t, prev_t, 1);		
		push		1
		push		esi
		push		edi
		push		ecx
		push		4	
		call		dword [strs+glUniform4i]
;// 	glRects(-1,-1,+1,+1);		
		push        1
		push        1
		push        -1
		push        -1
		call		dword [__imp__glRects@16]
		push		ecx
;// 	int xcoord=0;
		xor			edx,edx
;// 	for(int mip=0;mip<9;++mip)
;// 	{		
		xor			ecx, ecx
SliceLoop:	
			mov			eax, VOLUME_SIZE
			shr			eax, cl
			pushad		
;// 		oglCopyTexSubImage3D(GL_TEXTURE_3D, mip, 0, 0, i, xcoord, 0, VOLUME_SIZE >> mip, VOLUME_SIZE >> mip);				
			push		eax
			push		eax
			push		0
			push		edx
			push		dword [esp]
			push		0
			push		0
			push		ecx
			push		806Fh		
			call		dword [strs+glCopyTexSubImage3D]
;// 		xcoord+=VOLUME_SIZE >> mip;
			popad
			add			edx, eax
			cmp			ecx, 8
			jle			SliceLoop	
		pop			ecx
		add			ecx, 8
		cmp			ecx, VOLUME_SIZE
		jl			PropagationLoop		
;// if(frame==0)
;// 	oglGenerateMipmap(GL_TEXTURE_3D);
	and			ebx, ebx
	jnz			NoMipGen
		push		806Fh
		call		dword [strs+glGenerateMipmap]
NoMipGen:	
;// oglUniform4i(4, frame, t, prev_t, 0);
	push		0
	push		esi
	push		edi
	push		ebx
	push		4
	call		dword [strs+glUniform4i]
;// glRects(-1,-1,+1,+1);
	push        1
    push        1
    push        -1
    push        -1
	call		dword [__imp__glRects@16]		
;// oglActiveTexture(GL_TEXTURE1);
	push		84C1h
	call		dword [strs+glActiveTexture]	
;// glBindTexture(GL_TEXTURE_2D, 2);
	push		2
	push		0DE1h
	call		dword [__imp__glBindTexture@8]
;// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	push		2703h
	push		2801h
	push		0DE1h
	call		dword [__imp__glTexParameteri@12]
;// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	push		812Dh
	push		2802h
	push		0DE1h
	call		dword [__imp__glTexParameteri@12]
;// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	push		812Dh
	push		2803h
	push		0DE1h
	call		dword [__imp__glTexParameteri@12]
;// glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
	push		0
	push		VOLUME_SIZE
	push		VOLUME_SIZE
	push		0
	push		0
	push		8058h
	push		0
	push		0DE1h
	call		dword [__imp__glCopyTexImage2D@32]
;// oglGenerateMipmap(GL_TEXTURE_2D);
	push		0DE1h
	call		dword [strs+glGenerateMipmap]
;// oglUniform4i(4, frame, t, prev_t, 2);		
	push		2
	push		esi
	push		edi
	push		ebx
	push		4
	call		dword [strs+glUniform4i]
;// glRects(-1,-1,+1,+1);
	push        1
    push        1
    push        -1
    push        -1
	call		dword [__imp__glRects@16]	
%ifdef DRAW_TEXT
;// oglUniform4i(4, 0, 0, 0, 4);
	push		4
	push		0
	push		0
	push		0
	push		4
	call		dword [strs+glUniform4i]
;// glRasterPos2f(-.55f,0.f);
	push		0
	push		0bf0ccccch	
	call		dword [__imp__glRasterPos2f@8]
;// glCallLists(14, GL_UNSIGNED_BYTE, "Eos & Alcatraz  ");
	push		credit1
	push		1401h
	push		7
	call		dword [__imp__glCallLists@12]
;// glRasterPos2f(-.55f,-.1f);
	push		4a23f560h
	push		0bf0ccccch	
	call		dword [__imp__glRasterPos2f@8]
;// glCallLists(15, GL_UNSIGNED_BYTE, "Horizon Machine ");
	push		credit2
	push		1401h
	push		15
	call		dword [__imp__glCallLists@12]	
%endif				
;// glFinish();
	call		dword [__imp__glFinish@0]	
;// wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );	
	push		1
	push		ebp
	call		dword [__imp__wglSwapLayerBuffers@8]	
;// dummy message loop when mousecursor should be hidden
%ifdef HIDECURSOR
	push		1
	push		0
	push		0
	push		0
	push		0
	call		dword [__imp__PeekMessageA@20]
%endif	
;// prev_t=t;
	mov			esi, edi
	inc 		ebx	
;//	__imp__GetAsyncKeyState@4(VK_ESCAPE)
	push        VK_ESCAPE  
	call        dword [__imp__GetAsyncKeyState@4] 
	sahf             
	jns         LoopIntro
ExitLoop:
;//	__imp__ExitProcess@4(x) where x is the current timestamp
	push		0		;// TODO: can be skipped
	call		dword [__imp__ExitProcess@4]