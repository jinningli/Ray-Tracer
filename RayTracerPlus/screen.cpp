#include <stdio.h>
#include "Vec3f.h"
#include <math.h>
#include "Screen.h"


namespace Tracer
{
	//--------------------------------------------------
	//	STBI_PIX Realization
	//--------------------------------------------------

	STBI_PIX::STBI_PIX(SCR_UC* Pix_Ptr, SCR_INT _comp)
	{
		r = Pix_Ptr[0]; g = Pix_Ptr[1]; b = Pix_Ptr[2];
		if (_comp == 4) a = Pix_Ptr[3];
		comp = _comp;
	}

	STBI_PIX::STBI_PIX(const STBI_PIX & other)
	{
		r = other.r; g = other.g;
		b = other.b; a = other.a;
		comp = other.comp;
	}
	const STBI_PIX STBI_PIX::operator = (const Tracer::Vec3f& _color)
	{
		r = _color.r; g = _color.g;
		b = _color.b; comp = 3;
		return *this;
	}
	SCR_VOI STBI_PIX::STBI_PIX_ENVALUE(SCR_UC* Pix_Ptr, SCR_INT _comp)
	{
		r = Pix_Ptr[0]; g = Pix_Ptr[1]; b = Pix_Ptr[2];
		if (_comp == 4) a = Pix_Ptr[3];
		comp = _comp;
	}
	SCR_VOI STBI_PIX::STBI_PIX_ENVALUE(SCR_UC _r, SCR_UC _g, SCR_UC _b, SCR_INT _comp, SCR_UC _a)
	{
		r = _r; g = _g;
		b = _b; a = _a;
		comp = _comp;
	}
	SCR_VOI STBI_PIX::STBI_PIX_ENVALUE(const Tracer::Vec3f& color)
	{
		r = color.r; g = color.g;
		b = color.b; comp = 3;
	}
	SCR_VOI STBI_PIX::STBI_PIX_OUTPUT(SCR_UC* Pix_Ptr, SCR_INT _comp)
	{
		Pix_Ptr[0] = r; Pix_Ptr[1] = g; Pix_Ptr[2] = b;
		if (_comp == 4) Pix_Ptr[3] = a;
	}

	//--------------------------------------------------
	//	STBI_SCREEN Realization
	//--------------------------------------------------

	STBI_SCREEN::STBI_SCREEN(SCR_INT _w, SCR_INT _h, SCR_INT _comp)
	{
		BackGround.r = 255; BackGround.g = 255; BackGround.b = 255;
		w = _w;
		h = _h;
		data = new STBI_PIX*[_h];
		for (int i = 0; i < h; i++) data[i] = new STBI_PIX[w];
		comp = _comp;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data[i][j].r = 30;
				data[i][j].g = 144;
				data[i][j].b = 255;
			}
		}
	}
	STBI_SCREEN::~STBI_SCREEN()
	{
		for (int i = 0; i < h; i++)
		{
			delete[] data[i];
		}
	}
	STBI_SCREEN::STBI_SCREEN(SCR_INT _w, SCR_INT _h, SCR_INT _comp, SCR_UC* image)
	{
		w = _w;
		h = _h;
		comp = _comp;
		data = new STBI_PIX*[_h];
		for (int i = 0; i < h; i++) data[i] = new STBI_PIX[w];
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data[i][j].STBI_PIX_ENVALUE(image + _comp *(i * w + j), _comp);
			}
		}
	}

	const STBI_SCREEN STBI_SCREEN::operator = (const STBI_SCREEN & other)
	{
		w = other.w;
		h = other.h;
		comp = other.comp;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data[i][j] = other.data[i][j];
			}
		}
		return *this;
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_FROM_BUFFER(SCR_INT _w, SCR_INT _h, SCR_INT _comp, SCR_UC* image)
	{
		w = _w;
		h = _h;
		comp = _comp;
		if (data == NULL)
		{
			data = new STBI_PIX*[_h];
			for (int i = 0; i < h; i++) data[i] = new STBI_PIX[w];
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data[i][j].STBI_PIX_ENVALUE(image + _comp *(i * w + j), _comp);
			}
		}
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, const STBI_PIX& _pix)
	{
		data[_x][_y] = _pix;
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, const Tracer::Vec3f & _color)
	{
		data[_x][_y] = _color;
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_PIX(SCR_INT _x, SCR_INT _y, SCR_UC r, SCR_UC g, SCR_UC b)
	{
		data[_x][_y].STBI_PIX_ENVALUE(r, g, b, 3);
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_LINE(SCR_INT _line, SCR_INT Left_Bound, SCR_INT Right_Bound, const STBI_PIX& _pix)
	{
		for (int j = Left_Bound; j <= Right_Bound; j++)
		{
			data[_line][j] = _pix;
		}
	}

	SCR_VOI	STBI_SCREEN::STBI_SCREEN_SET_COL(SCR_INT _col, SCR_INT Up_Bound, SCR_INT Down_Bound, const STBI_PIX& _pix)
	{
		for (int i = Up_Bound; i <= Down_Bound; i++)
		{
			data[i][_col] = _pix;
		}
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SET_POS(Vec3f& _origin, Vec3f& _dir1, Vec3f& _dir2)
	{
		origin = _origin; dir1 = _dir1; dir2 = _dir2;
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_OUTPUT(SCR_UC* image)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				data[i][j].STBI_PIX_OUTPUT(image + comp * (i * w + j), comp);
			}
		}
	}

	SCR_VOI STBI_SCREEN::STBI_SCREEN_SHOW(SCR_INT index)
	{
		char Fill[] = { '@', '#', '*', '0', '+', '.' };
		int size_of_fill = 6;
		int MAXRGB = 4404240;
		//std::cin >> MAXRGB;
		assert(data != NULL);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w;j++)
			{
				if (index == 1)
				{
					if (comp == 3)
						printf("(%d,%d,%d)", data[i][j].r, data[i][j].g, data[i][j].b);
					else if (comp == 4)
						printf("(%d,%d,%d,%d)", data[i][j].r, data[i][j].g, data[i][j].b, data[i][j].a);
				}
				else if (index == 2)
				{
					if (comp == 3)
						printf("%c", data[i][j].r == 255 && data[i][j].g == 255 && data[i][j].b == 255 ? '0' : '*');
					else printf("%c", data[i][j].r == 255 && data[i][j].g == 255 && data[i][j].b == 255 && data[i][j].a == 255 ? '0' : '*');
					printf(" ");
				}
				else if (index == 3)
				{
					int RGB = 256 * 256 * data[i][j].r + 256 * data[i][j].g + 256 * data[i][j].b;
					int ind = ((double)RGB / (MAXRGB + 1) * size_of_fill);
					while (ind > size_of_fill - 1) ind--;
					ind = 5 - ind;
					printf("%c ", Fill[ind]);
				}

			}
			printf("\n");
		}
	}

}