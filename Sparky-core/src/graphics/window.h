#pragma once

namespace sparky { namespace graphics {

		class Window
		{
		private:
			const char *name;
			int width, height;

		public:
			Window(const char *name, int width, int height);
			~Window();
		};
	}
}
