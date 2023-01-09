#include <iostream>
#include "app.h"

int main(int argc, char* argv[])
{
	draw_app app;
	wxImage::CleanUpHandlers();
	return app.run(argc, argv);
}