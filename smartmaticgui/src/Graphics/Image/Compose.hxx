
#ifndef __COMPOSE_HXX__
#define __COMPOSE_HXX__

#include <gtkmm.h>

namespace Smartmatic
{
    namespace Graphics
    {
        namespace Image
        {
            class PixbufComposer
            {




            private:
            	PixbufComposer();

            public:

            	enum ComposePosition
            	            	{
            	            		TOP_LEFT,
            	            		TOP_CENTER,
            	            		TOP_RIGHT,
            	            		MIDDLE_LEFT,
            	            		MIDDLE_CENTER,
            	            		MIDDLE_RIGHT,
            	            		BOTTOM_LEFT,
            	            		BOTTOM_CENTER,
            	            		BOTTOM_RIGHT,
            	            		RANDOM
            	            	};
                static Glib::RefPtr<Gdk::Pixbuf> compose(
                        Glib::RefPtr<Gdk::Pixbuf> background,
                        Glib::RefPtr<Gdk::Pixbuf> front,ComposePosition position = MIDDLE_CENTER);

            };
        }
    }
}

#endif
