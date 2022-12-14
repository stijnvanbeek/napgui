#include "GuiFunctions.h"

#include <imgui/imgui.h>

namespace nap
{

	namespace gui
	{

		void wrapHorizontal(int itemCount, int columnCount, std::function<void(int)> drawItemFunction)
		{
			int fullRowCount = int(itemCount / columnCount);
			int itemOffset = 0;
			for (auto row = 0; row <= fullRowCount; ++row)
			{
				for (auto item = 0; item < (row == fullRowCount ? itemCount % columnCount : columnCount); ++item)
				{
					if (item > 0)
						ImGui::SameLine();
					drawItemFunction(itemOffset + item);
				}
				itemOffset += columnCount;
			}
		}

	}

}