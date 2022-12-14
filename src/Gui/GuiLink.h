#pragma once

#include <Gui/Gui.h>

namespace nap
{
	namespace gui
	{

		/**
		 * Gui layout resources mostly contain other Gui resources that represent their content.
		 * Normally these content Gui resources are embedded within their owners.
		 * In some cases it can be desirable to instead of embedding the content link to other Gui resources owned by the ResourceManager.
		 * In that case you can embed a GuiLink resource and use it to link to another non-embedded Gui resource.
		 */
		class NAPAPI GuiLink : public Gui
		{
			RTTI_ENABLE(Gui)
		public:
			ResourcePtr<Gui> mLink = nullptr; ///< Property: 'Link' The non-embedded resource to point to.

		public:
			GuiLink() = default;

		private:
			void draw() override { mLink->show(); }
		};

	} // namespace gui
} // namespace nap