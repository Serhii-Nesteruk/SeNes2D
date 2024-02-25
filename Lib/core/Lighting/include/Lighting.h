#pragma once

#include "Gl.h"

class Lighting
{
public:
	struct Ambient
	{
	public:
		void setAmbientIntense(GLfloat ambientIntense)
		{
			_ambientIntense = std::clamp(ambientIntense, 0.f, 1.f);
		}
		GLfloat getAmbientIntense() const
		{
			return _ambientIntense;
		}
	private:
		GLfloat _ambientIntense = 0.f;
	} _ambient;
};