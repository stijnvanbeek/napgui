#pragma once

#include <Gui/Gui.h>
#include <nap/resourceptr.h>

namespace nap
{
	namespace gui
	{


		/**
		 * Lays out a series of content Guis in horizontal columns.
		 */
		class NAPAPI HorizontalLayout : public Gui
		{
			RTTI_ENABLE(Gui)
		public:
			std::vector<float> mColumnWidths; ///< Property: 'ColumnWidhts' The width of each column. This property can be left empty to fill up all available space with equal sized columns. The sizes are normalized to fill up the entire available region if mRelativeSizes is true.

			bool mBorders = true; ///< Property: 'Borders' True if borders should be drawn between the columns.
			bool mResizable = true; ///< Property: 'Resizable' True if user can drag the column sizes
			bool mRelativeSizes = true; ///< Property: 'RelativeSizes' Set to true to normalize mColumnWidths
			float mSplitterSize = 7.f; ///< Property: 'SplitterSize' Size of the splitter between columns
			std::vector<ResourcePtr<Gui>> mContent; ///< Property: 'Content' An embedded Gui to be displayed in each column. The size of this vector equals the number of columns.

		public:
			HorizontalLayout() = default;

			bool init(utility::ErrorState &errorState) override;

		private:
			void draw() override;
		};

	} // namespace gui
} // namespace nap