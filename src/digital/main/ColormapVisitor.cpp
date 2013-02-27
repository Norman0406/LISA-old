#include "ColormapVisitor.h"
#include "Colormap.h"

namespace digital
{	
	/************************************************************************
	   ColormapBlue
	************************************************************************/
	void ColormapBlue::visit(Colormap& map)
	{
		int range = map.getRange();
		map.addColor(0, QColor(0, 0, 30));
		map.addColor((int)(range / 3.0), QColor(0, 0, 83));
		map.addColor(range - 1, QColor(255, 255, 255));
	}

	/************************************************************************
	   ColormapFldigi
	************************************************************************/
	void ColormapFldigi::visit(Colormap& map)
	{
		int range = map.getRange();
		map.addColor(0, QColor(0, 0, 0));
		map.addColor((int)((43 / 255.0) * range), QColor(0, 0, 255));
		map.addColor((int)((87 / 255.0) * range), QColor(0, 255, 255));
		map.addColor((int)((120 / 255.0) * range), QColor(0, 255, 0));
		map.addColor((int)((154 / 255.0) * range), QColor(255, 255, 0));
		map.addColor((int)((217 / 255.0) * range), QColor(255, 0, 0));
		map.addColor(range - 1, QColor(255, 0, 128));
	}
}