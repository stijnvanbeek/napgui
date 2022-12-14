#include "Selector.h"

RTTI_BEGIN_CLASS(nap::gui::Selector)
	RTTI_PROPERTY("Index", &nap::gui::Selector::mIndex, nap::rtti::EPropertyMetaData::Default)
	RTTI_PROPERTY("Content", &nap::gui::Selector::mContent, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

namespace nap
{
	namespace gui
	{

		void Selector::draw()
		{
			if (mIndex < mContent.size())
				mContent[mIndex]->show();
		}

	}
} // namespace nap