#pragma once

#include "ofEvents.h"
#include "ofAppBaseWindow.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

namespace ofxImGui
{
	class BaseEngine
	{
	public:
		BaseEngine()
			: isSetup(false)
		{}

		virtual ~BaseEngine()
		{}

		virtual void setup(bool autoDraw) = 0;
		virtual void exit() = 0;

		virtual void newFrame() = 0;
        virtual void render() = 0;

        virtual bool updateFontsTexture() = 0;

		// This is here to keep a compatibility layer with old codebases.
		// Not recommended to use, Upload with OF and use the GL_TEXTURE_2D's textureID directly.
		virtual GLuint loadTextureImage2D(unsigned char * pixels, int width, int height);

	protected:
		bool isSetup;
	};
}

