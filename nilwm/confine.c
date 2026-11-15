#include <X11/extensions/Xfixes.h>

static PointerBarrier confinebarriers[4];
static int confined = 0;

void
toggleconfine(const Arg *arg)
{
	int i, x1, y1, x2, y2;

	if (confined) {
		for (i = 0; i < 4; i++)
			XFixesDestroyPointerBarrier(dpy, confinebarriers[i]);
		confined = 0;
		return;
	}

	x1 = selmon->mx;
	y1 = selmon->my;
	x2 = x1 + selmon->mw;
	y2 = y1 + selmon->mh;

	/* the direction flag is the direction still allowed through,
	 * so the pointer can enter the monitor but not leave it */
	confinebarriers[0] = XFixesCreatePointerBarrier(dpy, root, x1, y1, x1, y2, BarrierPositiveX, 0, NULL); /* left   */
	confinebarriers[1] = XFixesCreatePointerBarrier(dpy, root, x2, y1, x2, y2, BarrierNegativeX, 0, NULL); /* right  */
	confinebarriers[2] = XFixesCreatePointerBarrier(dpy, root, x1, y1, x2, y1, BarrierPositiveY, 0, NULL); /* top    */
	confinebarriers[3] = XFixesCreatePointerBarrier(dpy, root, x1, y2, x2, y2, BarrierNegativeY, 0, NULL); /* bottom */
	confined = 1;
}
