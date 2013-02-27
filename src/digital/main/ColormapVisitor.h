#ifndef DIGITAL_COLORMAPVISITOR_H
#define DIGITAL_COLORMAPVISITOR_H

namespace digital
{
	class Colormap;

	/************************************************************************
	   ColormapVisitor: simple visitor class for special color maps
	************************************************************************/
	class ColormapVisitor
	{
	public:
		virtual void visit(Colormap&) = 0;
	};
	
	/************************************************************************
	   ColormapBlue
	************************************************************************/
	class ColormapBlue
		: public ColormapVisitor
	{
	public:
		void visit(Colormap&);
	};
	
	/************************************************************************
	   ColormapFldigi: sorry, this is not Fldigi's default, it's CuteSDR's
	************************************************************************/
	class ColormapFldigi
		: public ColormapVisitor
	{
	public:
		void visit(Colormap&);
	};
}

#endif // DIGITAL_COLORMAPVISITOR_H