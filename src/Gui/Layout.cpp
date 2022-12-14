#include "Layout.h"

#include <imgui/imgui.h>

RTTI_BEGIN_CLASS(nap::gui::Layout)
	RTTI_PROPERTY("Separators", &nap::gui::Layout::mSeparators, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::Layout::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

		void Layout::draw()
		{
			for (auto& gui : mContent)
			{
				gui->show();
				if (mSeparators && gui != mContent.back())
					ImGui::Separator();
			}
		}

	}
} // namespace nap