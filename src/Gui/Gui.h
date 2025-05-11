#pragma once

#include <Gui/Style.h>
#include <nap/resource.h>
#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{


		/**
		 * Base class for all Gui layout and content classes.
		 * Provides a show() method to be called to apply a Style and display the gui, and a draw method to be overridden by descendants to write the actual ImGui implementation.
		 */
		class NAPAPI Gui : public Resource
		{
			RTTI_ENABLE(Resource)

		public:
			std::string mTitle = ""; 				///< Property: 'Title' Title associated with this Gui. Can be used by descendant classes to display a caption or in some cases to generate an ImGui ID.

			ResourcePtr<StyleDef> mStyle = nullptr; ///< Property: 'Style' Link to a Style resources that contains style deifinitions that will be applied on this Gui. In case the Gui contains other Gui objects as content the style will automatically apply to those as well.

		public:
			Gui() = default;

			/**
			 * Call this to display the Gui.
			 */
			void show();

		private:
			/**
			 * Override this to write the ImGui implementation for descendant classes.
			 */
			virtual void draw();
		};

	} // namespace gui
} // namespace nap