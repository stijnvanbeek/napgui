#include "Gui.h"

#include <imgui/imgui.h>

RTTI_BEGIN_CLASS(nap::gui::Gui)
	RTTI_PROPERTY("Title", &nap::gui::Gui::mTitle, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Style", &nap::gui::Gui::mStyle, nap::rtti::EPropertyMetaData::Default)
	RTTI_FUNCTION("show", &nap::gui::Gui::show)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

		void Gui::show()
		{
			if (mStyle != nullptr)
			{
				mStyle->push();
				draw();
				mStyle->pop();
			}
			else
				draw();
		}


		void Gui::draw()
		{
			ImGui::Text(mID.c_str());
		}

	}
} // namespace nap