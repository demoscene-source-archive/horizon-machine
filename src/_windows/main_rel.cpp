
#pragma warning( disable : 4730 )
#pragma warning( disable : 4799 )

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include "../config.h"
#include <GL/gl.h>
#include "../glext.h"
#include "../shader_code.h"
#include "../4klang.h"

#define DRAW_TEXT 0
#define HOT_RELOAD 0
#define MUSIC 1

#define ERRORBOX(x) MessageBoxA(hWnd,"there was a bad when " x,"bad",MB_OK); CloseHandle(hFile); ExitProcess(-1);

// MAX_SAMPLES gives you the number of samples for the whole song. we always produce stereo samples, so times 2 for the buffer
SAMPLE_TYPE	lpSoundBuffer[MAX_SAMPLES*2];  

#pragma data_seg(".wavefmt")
WAVEFORMATEX WaveFMT =
{
#ifdef FLOAT_32BIT	
	WAVE_FORMAT_IEEE_FLOAT,
#else
	WAVE_FORMAT_PCM,
#endif		
    2, // channels
    SAMPLE_RATE, // samples per sec
    SAMPLE_RATE*sizeof(SAMPLE_TYPE)*2, // bytes per sec
    sizeof(SAMPLE_TYPE)*2, // block alignment;
    sizeof(SAMPLE_TYPE)*8, // bits per sample
    0 // extension not needed
};

#pragma data_seg(".wavehdr")
WAVEHDR WaveHDR = 
{
	(LPSTR)lpSoundBuffer, 
	MAX_SAMPLES*sizeof(SAMPLE_TYPE)*2,			// MAX_SAMPLES*sizeof(float)*2(stereo)
	0, 
	0, 
	0, 
	0, 
	0, 
	0
};

MMTIME MMTime = 
{ 
	TIME_SAMPLES,
	0
};



static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
    32, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

static DEVMODE screenSettings = { {0},
    #if _MSC_VER < 1400
    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
    #else
    0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
    #endif
    #if(WINVER >= 0x0400)
    0,0,0,0,0,0,
    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    0,0
    #endif
    #endif
    };

#ifdef __cplusplus
extern "C" 
{
#endif
int  _fltused = 1;
#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------

static const char *const strs[] = {
	"glCreateShaderProgramv",
	"glTexStorage3D",
	"glCopyTexSubImage3D",
	"glUseProgram",
	//"glGetUniformLocation",
	"glUniform4i",
	"glActiveTexture",
	"glGenerateMipmap",
    };

#define NUMFUNCIONES (sizeof(strs)/sizeof(strs[0]))

#define oglCreateShaderProgramv	      ((PFNGLCREATESHADERPROGRAMVPROC)myglfunc[0])
#define oglTexStorage3D								((PFNGLTEXSTORAGE3DPROC)myglfunc[1])
#define oglCopyTexSubImage3D		      ((PFNGLCOPYTEXSUBIMAGE3DPROC)myglfunc[2])
#define oglUseProgram									((PFNGLUSEPROGRAMPROC)myglfunc[3])
//#define oglGetUniformLocation					((PFNGLGETUNIFORMLOCATIONPROC)myglfunc[4])
#define oglUniform4i									((PFNGLUNIFORM4IPROC)myglfunc[4])
#define oglActiveTexture							((PFNGLACTIVETEXTUREPROC)myglfunc[5])
#define oglGenerateMipmap							((PFNGLGENERATEMIPMAPPROC)myglfunc[6])

#define USE_SOUND_THREAD


#define VOLUME_SIZE 256

#if HOT_RELOAD
DWORD g_BytesTransferred = 0;
VOID CALLBACK FileIOCompletionRoutine(
  __in  DWORD dwErrorCode,
  __in  DWORD dwNumberOfBytesTransfered,
  __in  LPOVERLAPPED lpOverlapped
);

VOID CALLBACK FileIOCompletionRoutine(
  __in  DWORD dwErrorCode,
  __in  DWORD dwNumberOfBytesTransfered,
  __in  LPOVERLAPPED lpOverlapped )
 {
g_BytesTransferred = dwNumberOfBytesTransfered;
 }
#endif

/*
VOID hurrrdurr(
    _In_    DWORD dwErrorCode,
    _In_    DWORD dwNumberOfBytesTransfered,
    _Inout_ LPOVERLAPPED lpOverlapped
    )
{
}
*/

void entrypoint( void )
{
    // full screen
    //if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return;
    ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN);
    ShowCursor( 0 );
    // create window
//    HWND hWnd = CreateWindow( "edit",0,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
//    HWND hWnd = CreateWindow( "", (LPCSTR)0x0C018,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
    HWND hWnd = CreateWindow((LPCSTR)0x0C018, 0, WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
//    if( !hWnd ) return;
    HDC hDC = GetDC(hWnd);
    // initalize opengl
    SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd);
    //if( !SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd) ) return;
    wglMakeCurrent(hDC,wglCreateContext(hDC));

	void *myglfunc[NUMFUNCIONES];

    for( int i=0; i<NUMFUNCIONES; i++ )
    {
        #ifdef WIN32
        myglfunc[i] = wglGetProcAddress( strs[i] );
        #endif
        #ifdef LINUX
        myglfunc[i] = glXGetProcAddress( (const unsigned char *)strs[i] );
        #endif
    }

	const char* fragment_source = fragment_glsl;

	int fragprog = oglCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragment_source);

	oglUseProgram(fragprog);


	glBindTexture(GL_TEXTURE_3D, 1);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	oglTexStorage3D(GL_TEXTURE_3D, 9, GL_RGBA8, VOLUME_SIZE, VOLUME_SIZE, VOLUME_SIZE);

HWAVEOUT	hWaveOut;

//	InitSound();
{
#if !MUSIC
// SILENCE
for(int i=0;i<MAX_SAMPLES*2;++i)
lpSoundBuffer[i]=0;
#else
#ifdef USE_SOUND_THREAD
	// thx to xTr1m/blu-flame for providing a smarter and smaller way to create the thread :)
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_4klang_render, lpSoundBuffer, 0, 0);
#else
	_4klang_render(lpSoundBuffer);
#endif
#endif


	waveOutOpen			( &hWaveOut, WAVE_MAPPER, &WaveFMT, NULL, 0, CALLBACK_NULL );
	waveOutPrepareHeader( hWaveOut, &WaveHDR, sizeof(WaveHDR) );
	waveOutWrite		( hWaveOut, &WaveHDR, sizeof(WaveHDR) );	
}

/*
{
    HANDLE hFile; 
    DWORD  dwBytesRead = 0;

    hFile = CreateFile("..\\src\\location.txt",               // file to open
                       GENERIC_WRITE,          // open for reading
                       FILE_SHARE_READ|FILE_SHARE_WRITE,       // share for reading
                       NULL,                  // default security
                       CREATE_ALWAYS,         // existing file only
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);                 // no attr. template

			OVERLAPPED ol = {0};

			int buffer[] = { 			((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(fragprog,"v"), ChoosePixelFormat(hDC,&pfd)			 };
			if( FALSE == WriteFileEx(hFile, buffer, sizeof(buffer), &ol, hurrrdurr) )
			{
				ERRORBOX("writing to the file");
			}
}
*/


#if DRAW_TEXT
	// http://web.archive.org/web/20010208190716/http://nehe.gamedev.net/tutorials/lesson13.asp
//	HFONT font = CreateFont(-30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
//	HFONT font = CreateFont(-40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Georgia");

#if 0
	HFONT font = CreateFont(-40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Dotum");

//WINGDIAPI HFONT   WINAPI CreateFontA( _In_ int cHeight, _In_ int cWidth, _In_ int cEscapement, _In_ int cOrientation, _In_ int cWeight, _In_ DWORD bItalic,
//                             _In_ DWORD bUnderline, _In_ DWORD bStrikeOut, _In_ DWORD iCharSet, _In_ DWORD iOutPrecision, _In_ DWORD iClipPrecision,
//                             _In_ DWORD iQuality, _In_ DWORD iPitchAndFamily, _In_opt_ LPCSTR pszFaceName);

#else
	static  const LOGFONT logfont = {
			-40,	//LONG  lfHeight;
			0,	//LONG  lfWidth;
			0,	//LONG  lfEscapement;
			0,	//LONG  lfOrientation;
			FW_NORMAL,	//LONG  lfWeight;
			FALSE,	//BYTE  lfItalic;
			FALSE,	//BYTE  lfUnderline;
			FALSE,	//BYTE  lfStrikeOut;
			ANSI_CHARSET,	//BYTE  lfCharSet;
			OUT_TT_PRECIS,	//BYTE  lfOutPrecision;
			CLIP_DEFAULT_PRECIS,	//BYTE  lfClipPrecision;
			ANTIALIASED_QUALITY,	//BYTE  lfQuality;
			FF_DONTCARE|DEFAULT_PITCH,	//BYTE  lfPitchAndFamily;
			"Dotum",	//TCHAR lfFaceName[LF_FACESIZE];
	};

	HFONT font = CreateFontIndirect(&logfont);
#endif

	SelectObject (hDC, font);
//	SelectObject (hDC, GetStockObject (SYSTEM_FONT)); 
	wglUseFontBitmaps(hDC, 0, 256, 0); 
#endif

		long int prev_t=0;
		long int frame=0;

#if HOT_RELOAD

    HANDLE hFile; 
    DWORD  dwBytesRead = 0;
    FILETIME ftCreatePrev, ftAccessPrev, ftWritePrev;
    FILETIME ftCreate, ftAccess, ftWrite;

    hFile = CreateFile("..\\src\\fragment.glsl",               // file to open
                       GENERIC_READ,          // open for reading
                       FILE_SHARE_READ|FILE_SHARE_WRITE,       // share for reading
                       NULL,                  // default security
                       OPEN_EXISTING,         // existing file only
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);                 // no attr. template

    if (hFile == INVALID_HANDLE_VALUE) 
    {
			ERRORBOX("opening file");
		}

    if (!GetFileTime(hFile, &ftCreatePrev, &ftAccessPrev, &ftWritePrev))
		{
			ERRORBOX("GetFileTime");
		}
#endif

    do 
    {

#if HOT_RELOAD
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
		{
			ERRORBOX("GetFileTime");
		}
		if(ftWrite.dwLowDateTime != ftWritePrev.dwLowDateTime || ftWrite.dwHighDateTime != ftWritePrev.dwHighDateTime || frame == 0)
		{
			static char buffer[32768] = {0};

			buffer[0]=0;

			LARGE_INTEGER dis;
			dis.QuadPart = 0;
			if( FALSE == SetFilePointerEx(hFile, dis, NULL, FILE_BEGIN) )
			{
				ERRORBOX("setting the file pointer");
			}

			OVERLAPPED ol = {0};
			if( FALSE == ReadFileEx(hFile, buffer, sizeof(buffer)-1, &ol, FileIOCompletionRoutine) )
			{
				ERRORBOX("reading the file");
			}
/*
			if(g_BytesTransferred==0)
			{
				ERRORBOX("zero bytes");
			}
*/
			const char* fragment_source = buffer;

			((PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram"))(fragprog);

			fragprog = oglCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragment_source);

			oglUseProgram(fragprog);

			GLubyte col[4]={0,0,0,0};
			((PFNGLCLEARTEXIMAGEPROC)wglGetProcAddress("glClearTexImage"))(2,0,GL_RGBA,GL_UNSIGNED_BYTE,col);			
			for(int mip=0;mip<9;++mip)
				((PFNGLCLEARTEXIMAGEPROC)wglGetProcAddress("glClearTexImage"))(1,mip,GL_RGBA,GL_UNSIGNED_BYTE,col);			
		}
		ftCreatePrev=ftCreate;
		ftAccessPrev=ftAccess;
		ftWritePrev=ftWrite;
#endif

		waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));

		long int t = MMTime.u.sample;
		//long int t = (long int)(((MMTime.u.sample) * 1000) / SAMPLE_RATE);

		oglActiveTexture(GL_TEXTURE0);

		for(int i = frame&7; i < VOLUME_SIZE; i+=8)
		{
			oglUniform4i(2, i, t, prev_t, 1);
			glRects(-1,-1,+1,+1);

			int xcoord=0;
			for(int mip=0;mip<9;++mip)
			{
				oglCopyTexSubImage3D(GL_TEXTURE_3D, mip, 0, 0, i, xcoord, 0, VOLUME_SIZE >> mip, VOLUME_SIZE >> mip);
				xcoord+=VOLUME_SIZE >> mip;
			}			
		}

		if(frame==0)
			oglGenerateMipmap(GL_TEXTURE_3D);

		oglUniform4i(2, frame, t, prev_t, 0);
		glRects(-1,-1,+1,+1);

		oglActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		oglGenerateMipmap(GL_TEXTURE_2D);

		oglUniform4i(2, frame, t, prev_t, 2);
		glRects(-1,-1,+1,+1);

#if DRAW_TEXT
		oglUniform4i(2, 0, 0, 0, 2);
		glRasterPos2s(0,0);
		glCallLists(14, GL_UNSIGNED_BYTE, "Eos & Alcatraz");
		//glRasterPos2f(-.55f,-.1f);
		//glCallLists(15, GL_UNSIGNED_BYTE, "Horizon Machine");
#endif

		glFinish();

		prev_t=t;

	++frame;

     wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );

		PeekMessageA(0, 0, 0, 0, PM_REMOVE); // <-- "fake" message handling.

#if HOT_RELOAD
//	} while (MMTime.u.sample < MAX_SAMPLES && !GetAsyncKeyState(VK_ESCAPE));
	} while (!GetAsyncKeyState(VK_ESCAPE));
#else
	} while (MMTime.u.sample < MAX_SAMPLES && !GetAsyncKeyState(VK_ESCAPE));
#endif

    #ifdef CLEANDESTROY
    sndPlaySound(0,0);
    ChangeDisplaySettings( 0, 0 );
    ShowCursor(1);
    #endif

#if HOT_RELOAD
CloseHandle(hFile);
#endif

    ExitProcess(0);
}
