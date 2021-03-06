// OpenGL ES 3.0 Cookcook code

#include "NativeTemplate.h"
#ifdef __IPHONE_4_0
	#include "renderer.h"
#else
	#include "../Scene/renderer.h"
#endif
#include <time.h>
static clock_t clickTimeDiff;
bool GraphicsInit()
{
	Renderer::Instance().initializeRenderer();
}

bool GraphicsResize( int width, int height )
{
	Renderer::Instance().resize(width, height);
}

bool GraphicsRender()
{
	Renderer::Instance().setUpProjection();
	Renderer::Instance().render();
}

void TouchEventDown( float x, float y )
{
    if(abs(clickTimeDiff - clock())<100000){ //1000 milli second
        Renderer::Instance().TouchEventDoubleClick( x, y );
    }
    else{
        Renderer::Instance().TouchEventDown( x, y );
    }
    
    clickTimeDiff = clock();
}

void TouchEventMove( float x, float y )
{
	Renderer::Instance().TouchEventMove( x, y );
}

void TouchEventRelease( float x, float y )
{
	Renderer::Instance().TouchEventRelease( x, y );
}


#ifdef __ANDROID__

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_init( JNIEnv *env, jobject obj, jstring FilePath )
{
	setenv( "FILESYSTEM", env->GetStringUTFChars( FilePath, NULL ), 1 );
	GraphicsInit();
}

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_resize( JNIEnv *env, jobject obj, jint width, jint height)
{
	GraphicsResize( width, height );
}

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_step(JNIEnv * env, jobject obj)
{
	GraphicsRender();
    //renderFrame();
}

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_TouchEventStart(JNIEnv * env, jobject obj, float x, float y )
{
	TouchEventDown(x ,y);
}

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_TouchEventMove(JNIEnv * env, jobject obj, float x, float y )
{
	TouchEventMove(x ,y);
}

JNIEXPORT void JNICALL Java_cookbook_gles_GLESNativeLib_TouchEventRelease(JNIEnv * env, jobject obj, float x, float y )
{
	TouchEventRelease(x ,y);
}

#endif
