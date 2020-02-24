/*
 * ImageConverter.cpp declares a class for
 *  various image conversion operations.
 *
 *  Author:  Joel Adams, CS112 @ Calvin College.
 *  Created: March 2015
 *  Revised: November 2016
 */

#include "ImageConverter.h"
#include <unistd.h>            // sleep()

//-----------------  Method definitions ------------------------------

/* explicit constructor
 *
 * @param imageFileName, a string.
 * @param width, an int.
 * @param height, an int.
 *
 * Precondition: imageFileName contains the name of a valid image file
 *               && width > 0 && height > 0
 * Postcondition: myImageFileName == imageFileName
 *                && myWidth == width && myHeight = height
 *                && width x height Canvas containing the image
 *                    from imageFileName has been displayed on screen.
 */
ImageConverter::ImageConverter(const std::string& imageFileName, int width, int height)
 : myCanvas1(0, 0, width, height, imageFileName),
   myImageFileName(imageFileName),
   myWidth(width),
   myHeight(height)
{
    myCanvas1.start();
    myCanvas1.drawImage(myImageFileName, 0, 0, width, height);
    sleep(1);
}

/* destructor
 *
 * Precondition: this ImageConverter object is going out of scope.
 * Postcondition: myCanvas1 has disappeared from the screen.
 */
ImageConverter::~ImageConverter() {
    myCanvas1.wait();
    cout << "\nImageConverter terminated normally." << endl;
}

/* invertImage() inverts the image from myImageFileName using the #pragma omp parallel for directive
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */
void ImageConverter::invertImage() {
	// record the starting time
	double startTime = omp_get_wtime();

	Canvas canvas2(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted");
	canvas2.start();

#pragma omp parallel for
	// loop through the image rows
	for (int row = 0; row < myHeight; row++) {
		// slow the processing to simulate a very large image
		canvas2.sleep();
		// loop through the image columns
		for (int col = 0; col < myWidth; col++) {
			// read the pixel at canvas1[row][col]
			ColorInt pixelColor = myCanvas1.getPixel(row, col);
			// compute its inverse
			int invertedR = 255 - pixelColor.R;
			int invertedG = 255 - pixelColor.G;
			int invertedB = 255 - pixelColor.B;
			// draw the inverse at the same spot in canvas2
			canvas2.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
		} // inner for
	} // outer for

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nImage inversion took "
			<< totalTime << " seconds.\n" << endl;

	// save converted image
	canvas2.takeScreenShot();

	// wait a second for the other thread to catch up
	canvas2.wait();
} // invertImage


/* invertImage() inverts the image from myImageFileName using the "chunk-size 1" approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */
void ImageConverter::invertImage2() {

	Canvas canvas3(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted, Chunk-Size 1");
	canvas3.start();

	// launch additional threads
#pragma omp parallel
	{
		// how many workers do we have?
		unsigned numThreads = omp_get_num_threads();
		// which one am I?
		unsigned id = omp_get_thread_num();

		// loop through the image rows
		for (int row = id; row < myHeight; row += numThreads) {
			// slow the processing to simulate a very large image
			canvas3.sleep();
			// loop through the image columns
			for (int col = 0; col < myWidth; col++) {
				// read the pixel at canvas1[row][col]
				ColorInt pixelColor = myCanvas1.getPixel(row, col);
				// compute its inverse
				int invertedR = 255 - pixelColor.R;
				int invertedG = 255 - pixelColor.G;
				int invertedB = 255 - pixelColor.B;
				// draw the inverse at the same spot in canvas2
				canvas3.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
			} // inner for
		} // outer for
	} // #pragma omp parallel

	canvas3.wait();
} // invertImage2

/* invertImage() inverts the image from myImageFileName using the "equal-sized chunks" approach
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the inverse of the image from myCanvas1
 *                 (which contains the image from myImageFileName).
 */
void ImageConverter::invertImage3() {

	Canvas canvas4(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted, Equal-Sized Chunks ");
	canvas4.start();

	// launch additional threads
#pragma omp parallel
	{
		// how many workers do we have?
		unsigned numThreads = omp_get_num_threads();
		// which one am I?
		unsigned id = omp_get_thread_num();

		// compute size of chunks (iterations % numThreads may != 0)
		double iterations = myHeight;
		unsigned chunkSize = (unsigned)ceil(iterations / numThreads);

		// compute starting and stopping index values
		int start = id * chunkSize;
		int stop = 0;
		if (id < numThreads-1) {
			stop = start + chunkSize;
		} else {
			stop = myHeight;
		}

		// loop through image rows in equal-sized chunks
		for (int row = start; row < stop; row++) {
			// slow the processing to simulate a very large image
			canvas4.sleep();
			// loop through the image columns
			for (int col = 0; col < myWidth; col++) {
				// read the pixel at canvas1[row][col]
				ColorInt pixelColor = myCanvas1.getPixel(row, col);
				// compute its inverse
				int invertedR = 255 - pixelColor.R;
				int invertedG = 255 - pixelColor.G;
				int invertedB = 255 - pixelColor.B;
				// draw the inverse at the same spot in canvas2
				canvas4.drawPixel(row, col, ColorInt(invertedR,invertedG,invertedB) );
			} // inner for
		} // outer for
	} // #pragma omp parallel

	canvas4.wait();
} // invertImage3


/* mirrorVertical() mirrors myImageFileName based on the left side
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the mirror of the image from myCanvas1
 *                 (which contains the image from myImageFileName)
 *                 && a file containing the converted image will be saved.
 *
 * @author: Duncan Van Keulen (project)
 */
void ImageConverter::mirrorVertical() {
	// record the starting time
	double startTime = omp_get_wtime();

	Canvas canvas5(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Mirrored");
	canvas5.start();

	int MIRROR_POINT = myWidth/2;

#pragma omp parallel for
	// loop through the image rows
	for (int row = 0; row < myHeight; row++) {
		// slow the processing to simulate a very large image
		canvas5.sleep();
		// loop through the image columns
		for (int col = 0; col < myWidth/2; col++) {
			// get the "anchor pixel" to the left of the MIRROR_POINT
			ColorInt defaultPixel = myCanvas1.getPixel(row, col);
			// get the same pixel in reverse order to be copied (flipped) to the other side
			ColorInt leftPixel = myCanvas1.getPixel(row, MIRROR_POINT - col);

			// re-draw the "anchor pixel"
			canvas5.drawPixel(row, col, ColorInt(defaultPixel.R, defaultPixel.G, defaultPixel.B) );
			// draw that pixel mirrored over the MIRROR_POINT
			canvas5.drawPixel(row, col+MIRROR_POINT, ColorInt(leftPixel.R, leftPixel.G, leftPixel.B) );
		} // inner for
	} // outer for

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nImage inversion took "
			<< totalTime << " seconds.\n" << endl;

	// save converted image
	canvas5.takeScreenShot();

	// wait a second for the other thread to catch up
	canvas5.wait();
} // mirrorImage

/* changeBrightness() offsets the color of each pixel according to the...
 * @param const int& offset: the amount to offset each RGB value by
 * 						     (negative for darker, positive for brighter)
 *
 * Precondition: myCanvas1 contains a TSGL Image that is to be inverted
 *               && myWidth contains the number of columns in which to display the image
 *               && myHeight contains the number of rows in which to display the image.
 *
 * Postcondition: a myWidth x myHeight Canvas has been displayed
 *                 containing the image from myCanvas1 with a brightness change
 *                 (which contains the image from myImageFileName)
 *                 && a file containing the converted image will be saved.
 *
 * @author: Duncan Van Keulen (project)
 */
void ImageConverter::changeBrightness(const int& offset) {
	// record the starting time
	double startTime = omp_get_wtime();

	Canvas canvas6(myWidth+50, 0, myWidth, myHeight, myImageFileName + " Inverted");
	canvas6.start();

#pragma omp parallel for
	// loop through the image rows
	for (int row = 0; row < myHeight; row++) {
		// slow the processing to simulate a very large image
		canvas6.sleep();
		// loop through the image columns
		for (int col = 0; col < myWidth; col++) {
			// read the pixel at canvas1[row][col]
			ColorInt pixelColor = myCanvas1.getPixel(row, col);
			// compute the offsetted RGB values
			int brightnessChangeR = pixelColor.R + offset;
			int brightnessChangeG = pixelColor.G + offset;
			int brightnessChangeB = pixelColor.B + offset;

			// draw the new pixel values to the new canvas
			canvas6.drawPixel(row, col, ColorInt(brightnessChangeR, brightnessChangeG, brightnessChangeB) );
		} // inner for
	} // outer for

	// compute and display the time difference
	double totalTime = omp_get_wtime() - startTime;
	cout << "\n\nImage inversion took "
			<< totalTime << " seconds.\n" << endl;

	// save converted image
	canvas6.takeScreenShot();

	// wait a second for the other thread to catch up
	canvas6.wait();
} // invertImage
