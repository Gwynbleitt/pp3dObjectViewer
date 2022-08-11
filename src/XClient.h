#include <X11/Xlib.h>
#include <X11/Xutil.h>


namespace XFunctions
{

class XClient{
    public:
    
    /* X Varibles */

    Display* dpy;
    int screen;
    Window win, root;
    Colormap colormap;
    XWindowAttributes xattr;
    GC gc;

    /* main methods */

    void Connect();
    void Close();
    void setcm(int c_class); /*set colormap based on visual*/

    /* misc */

    unsigned long RGBtoPixel_24(int R, int G, int B); 
};

}