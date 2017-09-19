#pragma once
#include "Vec3f.h"
#include "color.h"
namespace Tracer
{
	typedef unsigned char SCR_UC;
	typedef int SCR_INT;
	typedef void SCR_VOI;

	class STBI_PIX;
	class STBI_SCREEN;

	class STBI_PIX
	{
		friend STBI_SCREEN;
	private:
		SCR_UC r;
		SCR_UC g;
		SCR_UC b;
		SCR_UC a;
		SCR_INT comp;
	public:
		STBI_PIX() {}
		STBI_PIX(SCR_INT _comp) { comp = _comp; }
		STBI_PIX(SCR_UC _r, SCR_UC _g, SCR_UC _b, SCR_UC _a = 0) :r(_r), g(_g), b(_b), a(_a) {}
		STBI_PIX(SCR_UC* Pix_Ptr, SCR_INT _comp);
		STBI_PIX(const STBI_PIX & other);
		const STBI_PIX operator = (const Tracer::Vec3f& _color);
		SCR_VOI STBI_PIX_ENVALUE(SCR_UC* Pix_Ptr, SCR_INT _comp);
		SCR_VOI STBI_PIX_ENVALUE(SCR_UC _r, SCR_UC _g, SCR_UC _b, SCR_INT _comp, SCR_UC _a = 0);
		SCR_VOI STBI_PIX_ENVALUE(const Tracer::Vec3f& color);
		SCR_VOI STBI_PIX_OUTPUT(SCR_UC* Pix_Ptr, SCR_INT _comp);
	};

	class STBI_SCREEN
	{
	private:
		STBI_PIX** data;
		SCR_INT w;
		SCR_INT h;
		SCR_INT comp;
		Vec3f origin;
		Vec3f dir1;
		Vec3f dir2;
		Vec3f* spotpos;
		Vec3f BackGround;
	public:
		STBI_SCREEN() { data = NULL; spotpos = NULL; BackGround.r = 128; BackGround.g = 128; BackGround.b = 128; };
		~STBI_SCREEN();
		STBI_SCREEN(SCR_INT _w, SCR_INT _h, SCR_INT _comp);
		STBI_SCREEN(SCR_INT _w, SCR_INT _h, SCR_INT _comp, SCR_UC* image);
		const STBI_SCREEN operator = (const STBI_SCREEN & other);
		//Basic Function
		//-----------------

		SCR_VOI STBI_SCREEN_SET_FROM_BUFFER(SCR_INT _w, SCR_INT _h, SCR_INT _comp, SCR_UC* image);
		SCR_VOI STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, const STBI_PIX& _pix);
		SCR_VOI STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, const Tracer::Vec3f & _color);
		SCR_VOI STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, SCR_UC r, SCR_UC g, SCR_UC b);
		SCR_VOI STBI_SCREEN_SET_LINE(SCR_INT _line, SCR_INT Left_Bound, SCR_INT Right_Bound, const STBI_PIX& _pix);
		SCR_VOI	STBI_SCREEN_SET_COL(SCR_INT _col, SCR_INT Up_Bound, SCR_INT Down_Bound, const STBI_PIX& _pix);
		SCR_VOI STBI_SCREEN_SET_POS(Vec3f& _origin, Vec3f& _dir1, Vec3f& _dir2);
		SCR_VOI STBI_SCREEN_COPY_BG(const STBI_SCREEN& other);
		//Set Function
		//-----------------

		//Operate Function
		//-----------------
		SCR_VOI STBI_SCREEN_OUTPUT(SCR_UC* image);
		SCR_VOI STBI_SCREEN_SHOW(SCR_INT index);
		//Output Function
		//-----------------

		
	};


}