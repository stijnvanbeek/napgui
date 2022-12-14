#pragma once

#include <functional>
#include <utility/dllexport.h>

namespace nap
{

	namespace gui
	{

		/**
		 * Utility function that can be used to repeat an ImGui widget call, display it in columns and wrap it horizontally around the number of columns.
		 * @param itemCount Number of times the widget should be drawn
		 * @param columnCount Number of times the widget should be displayed per line, or in how many columns
		 * @param drawItemFunction You can pass a lambda function that displays the actual widget. The int argument represents the index of the widget that should be drawn.
		 */
		void NAPAPI wrapHorizontal(int itemCount, int columnCount, std::function<void(int)> drawItemFunction);

	}

}