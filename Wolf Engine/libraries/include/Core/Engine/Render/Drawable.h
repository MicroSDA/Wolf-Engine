#pragma once

namespace we {

	class Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();
		virtual void Draw() = 0;
	protected:

	};

}

