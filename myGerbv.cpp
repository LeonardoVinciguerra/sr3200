#include "myGerbv.h"
#include <math.h>


void gerbv_render_zoom_to_fit_display_nobound(gerbv_project_t *gerbvProject, gerbv_render_info_t *renderInfo)
{
	gerbv_render_size_t bb;
	double width, height;
	double x_scale, y_scale;

	/* Grab maximal width and height of all layers */
	gerbv_render_get_boundingbox(gerbvProject, &bb);
	width = bb.right - bb.left;
	height = bb.bottom - bb.top;
	/* add in a 5% buffer around the drawing */
	//width *= 1.05;
	//height *=1.05;

	/* if the values aren't sane (probably we have no models loaded), then
	   put in some defaults */
	if (!isnormal(width)||!isnormal(height)||((width < 0.01) && (height < 0.01))) {
		renderInfo->lowerLeftX = 0.0;
		renderInfo->lowerLeftY = 0.0;
		renderInfo->scaleFactorX = 200;
		renderInfo->scaleFactorY = 200;
		return;
	}
	/*
	* Calculate scale for both x axis and y axis
	*/
	x_scale = renderInfo->displayWidth / width;
	y_scale = renderInfo->displayHeight / height;
	/*
	* Take the scale that fits both directions with some extra checks
	*/
	renderInfo->scaleFactorX = MIN(x_scale, y_scale);
	renderInfo->scaleFactorY = renderInfo->scaleFactorX;
	if (renderInfo->scaleFactorX < 1){
	    renderInfo->scaleFactorX = 1;
	    renderInfo->scaleFactorY = 1;
	}
	renderInfo->lowerLeftX = ((bb.left + bb.right) / 2.0) -
		((double) renderInfo->displayWidth / 2.0 / renderInfo->scaleFactorX);
	renderInfo->lowerLeftY = ((bb.top + bb.bottom) / 2.0) -
		((double) renderInfo->displayHeight / 2.0 / renderInfo->scaleFactorY);
}

