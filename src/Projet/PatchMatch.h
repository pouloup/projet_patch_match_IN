#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <climits>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "PatchMatch.h"
#include "MSE.h"
#include "brent.h"
#include "BITMAP.h"
#include "knn.h"
#include "displayKNNField.h"

#ifndef MAX
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#endif

/* Match image a to image b, returning the nearest neighbor field mapping a => b coords, stored in an RGB 24-bit image as (by<<12)|bx. */
void patchmatch(BITMAP * a, BITMAP * b, BITMAP * ann, BITMAP * annd);
void patchmatch(cv::Mat * a, cv::Mat * b, cv::Mat * ann, cv::Mat * annd);
void patchmatch_brent(cv::Mat * a, cv::Mat * b, cv::Mat * ann, cv::Mat * annd);
void patchmatch(cv::Mat * a, cv::Mat * b, cv::Mat * ann, cv::Mat * annd,
		cv::Mat * knn, cv::Mat * knnd);
