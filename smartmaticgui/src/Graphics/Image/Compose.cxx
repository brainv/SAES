
#include "Graphics/Image/Compose.hxx"



using namespace Smartmatic::Graphics::Image;


PixbufComposer::PixbufComposer()
{

}

Glib::RefPtr<Gdk::Pixbuf> PixbufComposer::compose(
        Glib::RefPtr<Gdk::Pixbuf> background,
        Glib::RefPtr<Gdk::Pixbuf> front, ComposePosition position )
{
    int bkgWidth = background->get_width ();
    int bkgHeight = background->get_height ();
    int frgWidth = front->get_width ();
    int frgHeight = front->get_height ();

    if(frgWidth > bkgWidth || frgHeight > bkgHeight)
    	return front;

    int xPos = 0;
    int yPos = 0;

    switch(position)
    {

    case TOP_LEFT:
    	xPos = 0;
    	yPos = 0;
    	break;
    case TOP_CENTER:
    	yPos = 0;
    	xPos = (bkgWidth - frgWidth)/2;
    	break;
    case TOP_RIGHT:
    	yPos = 0;
    	xPos = bkgWidth - frgWidth;
    	break;
    case MIDDLE_LEFT:
    	xPos = 0;
    	yPos =(bkgHeight - frgHeight)/2;
    	break;
    case MIDDLE_CENTER:
    	yPos =(bkgHeight - frgHeight)/2;
    	xPos = (bkgWidth - frgWidth)/2;
    	break;
    case MIDDLE_RIGHT:
    	yPos =(bkgHeight - frgHeight)/2;
    	xPos = bkgWidth - frgWidth;
    	break;
    case BOTTOM_LEFT:
    	xPos = 0;
    	yPos = bkgHeight - frgHeight;
    	break;
    case BOTTOM_CENTER:
    	yPos = bkgHeight - frgHeight;
    	xPos = (bkgWidth - frgWidth)/2;
    	break;
    case BOTTOM_RIGHT:
    	yPos = bkgHeight - frgHeight;
    	xPos = bkgWidth - frgWidth;
    	break;
    case RANDOM:
    	int maxX = bkgWidth - frgWidth;
    	int maxY = bkgHeight - frgHeight;

    	yPos = rand() % maxY;
    	xPos = rand() % maxX;
    	break;
    }

    front->copy_area(0,0,frgWidth,frgHeight, background, xPos,yPos);

    return background;
}
